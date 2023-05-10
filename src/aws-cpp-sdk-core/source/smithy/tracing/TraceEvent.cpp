/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */
#pragma once

#include <smithy/tracing/TraceEvent.h>
#include <aws/core/utils/UUID.h>

using namespace smithy::components::tracing;
using namespace Aws::Utils;

TraceEvent::TraceEvent(std::string &&eventName, const std::string &spanId, const std::string &emittingComponent) :
    eventLevel(TraceEventLevel::Info),
    spanId(spanId),
    emitingComponentId(emittingComponent),
    eventName(std::move(eventName))
{
    eventId = UUID::PseudoRandomUUID();
    timeEmitted = std::chrono::system_clock::now();
    threadId = std::this_thread::get_id();
}