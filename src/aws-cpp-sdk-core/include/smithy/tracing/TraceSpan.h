/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */
#pragma once

#include <smithy/tracing/TraceProbe.h>
#include <smithy/tracing/TraceStatType.h>
#include <aws/core/utils/memory/stl/AWSString.h>
#include <memory>
#include <chrono>

namespace smithy {
    namespace components {
        namespace tracing {
            SMITHY_API class TraceSpan : public std::enable_shared_from_this<TraceSpan> {
            public:
                TraceSpan(std::shared_ptr<TraceProbe> probe);

                TraceSpan(std::shared_ptr<TraceSpan> parentSpan);

                TraceSpan(const TraceSpan &) = delete;

                TraceSpan &operator=(const TraceSpan &) = delete;

                TraceSpan(TraceSpan &&) = delete;

                TraceSpan &operator=(TraceSpan &&) = delete;

                ~TraceSpan();

                TraceEvent newCountEvent(Aws::String &&eventName,
                    const Aws::String &componentId,
                    TraceEventLevel level,
                    uint64_t count) const;

                TraceEvent newTimerEvent(Aws::String &&eventName,
                    const Aws::String &componentId,
                    TraceEventLevel level,
                    std::chrono::milliseconds timeTaken) const;

                TraceEvent newStatEvent(Aws::String &&eventName,
                    const Aws::String &componentId,
                    TraceEventLevel level,
                    TraceStatType statType,
                    double value) const;

                TraceEvent newMessageEvent(Aws::String &&eventName,
                    const Aws::String &componentId,
                    TraceEventLevel level,
                    Aws::String &&message) const;

                std::shared_ptr<TraceSpan> newChildSpan();

                void emitTraceEvent(TraceEvent &&event);

                void emitTraceEvents(std::vector<TraceEvent> &&events);

                void flushEvents() noexcept;

            private:
                Aws::Vector<TraceEvent> spanEvents;
                std::shared_ptr<TraceProbe> probe;
                std::shared_ptr<TraceSpan> parentSpan;
                Aws::String spanId;
                std::mutex eventsLock;
            };
        }
    }
}
