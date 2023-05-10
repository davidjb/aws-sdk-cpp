/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */
#pragma once

#include <smithy/tracing/TraceSpan.h>
#include <smithy/tracing/TraceCountEvent.h>
#include <smithy/tracing/TraceMessageEvent.h>
#include <smithy/tracing/TraceStatEvent.h>
#include <smithy/tracing/TraceTimerEvent.h>
#include <aws/core/utils/UUID.h>
#include <aws/core/utils/memory/stl/AWSVector.h>

using namespace smithy::components::tracing;

static const char *ALLOC_TAG = "TraceSpan";

TraceSpan::TraceSpan(std::shared_ptr<TraceProbe> probe) : probe(std::move(probe)) {
    spanId = Aws::String(UUID::PseudoRandomUUID());
}

TraceSpan::TraceSpan(std::shared_ptr<TraceSpan> parentSpan) : parentSpan(std::move(parentSpan)) {
    spanId = Aws::String(UUID::PseudoRandomUUID());
}

TraceSpan::~TraceSpan() {
    flushEvents();
}

std::shared_ptr<TraceSpan> TraceSpan::newChildSpan() {
    return std::make_shared<TraceSpan>(this->shared_from_this());
}

void TraceSpan::emitTraceEvent(TraceEvent &&event) {
    if (parentSpan) {
        parentSpan->emitTraceEvent(std::move(event));
    } else {
        std::lock_guard<std::mutex> lockGuard(eventsLock);
        spanEvents.push_back(std::move(event));
    }
}

void TraceSpan::emitTraceEvents(std::vector<TraceEvent> &&events) {
    if (parentSpan) {
        parentSpan->emitTraceEvents(std::move(events));
    } else {
        {
            std::lock_guard<std::mutex> lockGuard(eventsLock);
            std::move(events.begin(), events.end(), std::back_inserter(spanEvents));
        }
    }
}

void TraceSpan::flushEvents() {
    if (probe) {
        Aws::Vector<TraceEvent> eventsMove;
        {
            std::lock_guard<std::mutex> lockGuard(eventsLock);
            eventsMove = std::move(spanEvents);
            spanEvents = Aws::Vector<TraceEvent>();
        }

        // let's not make the dispatch call if we don't have any events.
        if (!eventsMove.empty()) {
            probe->dispatchEvents(eventsMove);
        }
    }
}

TraceEvent TraceSpan::newCountEvent(Aws::String &&eventName,
    const Aws::String &componentId,
    TraceEventLevel level,
    uint64_t count) const {

    TraceEvent event(std::move(eventName), spanId, componentId);

    auto countEvent = Aws::MakeUnique<TraceCountEvent>(ALLOC_TAG);
    countEvent->count = count;
    countEvent->eventType = TraceEventType::Count;

    event.event = std::move(countEvent);
    event.eventType = TraceEventType::Count;
    event.eventLevel = level;

    if (parentSpan) {
        event.parentSpanId = parentSpan->spanId;
    }

    return event;
}

TraceEvent TraceSpan::newTimerEvent(Aws::String &&eventName,
    const Aws::String &componentId,
    TraceEventLevel level,
    std::chrono::milliseconds timeTaken) const {

    TraceEvent event(std::move(eventName), spanId, componentId);

    auto timerEvent = Aws::MakeUnique<TraceTimerEvent>(ALLOC_TAG);
    timerEvent->timeTaken = timeTaken;
    timerEvent->eventType = TraceEventType::Timer;

    event.event = timerEvent;
    event.eventType = TraceEventType::Timer;
    event.eventLevel = level;

    if (parentSpan) {
        event.parentSpanId = parentSpan->spanId;
    }

    return event;
}

TraceEvent TraceSpan::newStatEvent(Aws::String &&eventName,
    const Aws::String &componentId,
    TraceEventLevel level,
    TraceStatType statType,
    double value) const {

    TraceEvent event(std::move(eventName), spanId, componentId);

    auto statEvent = Aws::MakeUnique<TraceStatEvent>(ALLOC_TAG);
    statEvent->value = value;
    statEvent->statType = statType;
    statEvent->eventType = TraceEventType::Stat;

    event.event = statEvent;
    event.eventType = TraceEventType::Stat;
    event.eventLevel = level;

    if (parentSpan) {
        event.parentSpanId = parentSpan->spanId;
    }

    return event;
}

TraceEvent TraceSpan::newMessageEvent(Aws::String &&eventName,
    const Aws::String &componentId,
    TraceEventLevel level,
    Aws::String &&message) const {

    TraceEvent event(std::move(eventName), spanId, componentId);

    auto messageEvent = Aws::MakeUnique<TraceMessageEvent>(ALLOC_TAG, std::move(message));
    event.event = messageEvent;
    event.eventType = TraceEventType::Msg;
    event.eventLevel = level;

    if (parentSpan) {
        event.parentSpanId = parentSpan->spanId;
    }

    return event;
}