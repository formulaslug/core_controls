// Copyright (c) Formula Slug 2016. All Rights Reserved.

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
