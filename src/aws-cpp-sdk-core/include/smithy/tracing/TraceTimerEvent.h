/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */
#pragma once

#include <smithy/Smithy_EXPORTS.h>
#include <smithy/tracing/TraceEventDataBase.h>
#include <chrono>

namespace smithy {
    namespace components {
        namespace tracing {
            SMITHY_API struct TraceTimerEvent : public TraceEventDataBase {
                std::chrono::milliseconds timeTaken;
            };
        }
    }
}
