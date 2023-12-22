/**
 * PROJECT:         Zero Engine
 * FILE:            engine/ze_types.h
 * DESCRIPTION:     Zero Engine-related types and macros definitions
 * COPYRIGHT:       LGPL-3.0-only
 * DEVELOPERS:      Jozef Nagy <schkwve@gmail.com>
 */

#pragma once

#include <stdlib.h>

#define ZE_ASSERT(cond)                                                                                                \
    if (cond)                                                                                                          \
    {                                                                                                                  \
        FATAL("Assertion failed at %s:%s, aborting!", __FILE__, __LINE__);                                             \
        abort();                                                                                                       \
    }

typedef int bool;
#define true 1
#define false 0