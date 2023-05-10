/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */
#pragma once

#include <smithy/Smithy_EXPORTS.h>
#include <smithy/tracing/TraceEventType.h>
#include <smithy/tracing/TraceEventLevel.h>
#include <smithy/tracing/TraceEventDataBase.h>
#include <aws/core/utils/memory/stl/AWSString.h>
#include <aws/crt/Optional.h>
#include <thread>

namespace smithy {
    namespace components {
        namespace tracing {
            SMITHY_API struct TraceEvent {
                TraceEventType eventType;
                TraceEventLevel eventLevel;
                Aws::String eventId;
                Aws::String spanId;
                Aws::Crt::Optional<Aws::String> parentSpanId;
                Aws::String emitingComponentId;
                std::chrono::time_point<std::chrono::system_clock> timeEmitted;
                std::thread::id threadId;
                Aws::String eventName;
                std::unique_ptr<TraceEventDataBase> event;

            private:
                TraceEvent(Aws::String &&eventName, const Aws::String &spanId, const Aws::String &emittingComponent);

                friend class TraceSpan;
            };
        }
    }
}
