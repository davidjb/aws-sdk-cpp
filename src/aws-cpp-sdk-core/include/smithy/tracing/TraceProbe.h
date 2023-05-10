/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */
#pragma once

#include <smithy/Smithy_EXPORTS.h>
#include <smithy/tracing/TraceEvent.h>
#include <aws/core/utils/memory/stl/AWSVector.h>

namespace smithy {
    namespace components {
        namespace tracing {
            SMITHY_API class TraceProbe {
            public:
                virtual ~TraceProbe() = default;

                virtual void dispatchEvents(const Aws::Vector<TraceEvent> &events) = 0;
            };
        }
    }
}