/**
 * PROJECT:         Zero Engine
 * FILE:            engine/ze_engine.h
 * DESCRIPTION:     Zero Engine entry/shutdown points
 * COPYRIGHT:       See LICENSE.md in the top level directory
 * DEVELOPERS:      Jozef Nagy <schkwve@gmail.com>
 */

#pragma once

#include <ze_types.h>

void engine_initialize(const char *app_name);
void engine_run();
void engine_shutdown();
