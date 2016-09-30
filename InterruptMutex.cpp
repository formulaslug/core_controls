#include "InterruptMutex.h"

#include "core/wiring.h"

void InterruptMutex::lock() {
  cli();
}

void InterruptMutex::unlock() {
  sei();
}
