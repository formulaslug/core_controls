// Copyright (c) 2016-2017 Formula Slug. All Rights Reserved.

#ifndef BUTTON_TRACKER_H
#define BUTTON_TRACKER_H

#include <stdint.h>

/* @tparam debounceCount Number of samples used when determining state change.
 *                       Should be between 1 and 8 inclusive.
 */
template <uint8_t DebounceCount>
class ButtonTracker {
  static_assert(DebounceCount >= 1 && DebounceCount <= 8,
                "Debounce count out of range");

 public:
  /* @param logicLow If true, considers DIO high signal as pressed. Otherwise,
   *                 low signal is considered pressed.
   */
  ButtonTracker(uint32_t pin, bool logicHigh);

  // Gets new button statuses
  void update();

  // @ret 'true' if button wasn't pressed but is now
  bool pressed() const;

  // @ret 'true' if button was pressed but isn't now
  bool released() const;

  // @ret 'true' if button was pressed and is now
  bool held() const;

 private:
  uint32_t m_pin;
  uint8_t m_debounceCount;
  bool m_logicHigh;

  uint8_t m_stateBuf = 0;
  bool m_wasPressed = false;
  bool m_isPressed = false;
};

#include "ButtonTracker.inl"

#endif  // BUTTON_TRACKER_H
