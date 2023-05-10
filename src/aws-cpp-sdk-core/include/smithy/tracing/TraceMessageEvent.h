/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */
#pragma once

#include <smithy/Smithy_EXPORTS.h>
#include <smithy/tracing/TraceEventDataBase.h>
#include <aws/core/utils/memory/stl/AWSString.h>

namespace smithy {
    namespace components {
        namespace tracing {
            SMITHY_API struct TraceMessageEvent: public TraceEventDataBase {
                Aws::String message;
            };
        }
    }
}