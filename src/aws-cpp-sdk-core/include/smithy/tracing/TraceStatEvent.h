/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */
#pragma once

#include <smithy/Smithy_EXPORTS.h>
#include <smithy/tracing/TraceStatType.h>
#include <smithy/tracing/TraceEventDataBase.h>

namespace smithy {
    namespace components {
        namespace tracing {
            SMITHY_API struct TraceStatEvent : public TraceEventDataBase {
                TraceStatType statType;
                double value;
            };
        }
    }
}
