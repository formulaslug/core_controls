// Copyright (c) Formula Slug 2016. All Rights Reserved.

#include "InterruptMutex.h"

#include "core/wiring.h"

void InterruptMutex::lock() { cli(); }

void InterruptMutex::unlock() { sei(); }
