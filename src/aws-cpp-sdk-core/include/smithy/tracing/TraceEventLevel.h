/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */
#pragma once

#include <smithy/Smithy_EXPORTS.h>

namespace smithy {
    namespace components {
        namespace tracing {
            SMITHY_API enum class TraceEventLevel {
                Fatal,
                Error,
                Warn,
                Info,
                Debug,
                Trace,
            };
        }
    }
}