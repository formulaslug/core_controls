// Copyright (c) 2016-2017 Formula Slug. All Rights Reserved.

#include "InterruptMutex.h"

#include "core/wiring.h"

void InterruptMutex::lock() { cli(); }

void InterruptMutex::unlock() { sei(); }
