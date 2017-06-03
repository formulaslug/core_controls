// Copyright (c) 2016-2017 Formula Slug. All Rights Reserved.

#ifndef INTERRUPT_MUTEX_H
#define INTERRUPT_MUTEX_H

// mutex is included here so std::lock_guard is available
#include <mutex>

class InterruptMutex {
 public:
  void lock();
  void unlock();
};

#endif  // INTERRUPT_MUTEX_H
