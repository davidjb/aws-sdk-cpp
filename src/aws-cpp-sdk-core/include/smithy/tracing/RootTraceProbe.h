/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */
#pragma once

#include <smithy/Smithy_EXPORTS.h>
#include <smithy/tracing/TraceEvent.h>
#include <smithy/tracing/TraceProbe.h>
#include <aws/core/utils/memory/stl/AWSVector.h>

namespace smithy {
    namespace components {
        namespace tracing {
            SMITHY_API class RootTraceProbe : public TraceProbe {
            public:
                void dispatchEvents(const Aws::Vector<TraceEvent> &events) override;

                // Call this to register a probe that you'd like to handle events. You can register as many as you'd like.
                void registerProbe(std::shared_ptr<TraceProbe> probe);

            private:
                Aws::Vector<std::shared_ptr<TraceProbe>> traceProbes;
            };
        }
    }
}