// Copyright (c) 2016-2017 Formula Slug. All Rights Reserved.

#include <Arduino.h>

namespace std {
void __throw_bad_alloc() { Serial.println("Unable to allocate memory"); }

void __throw_length_error(const char* e) {
  Serial.print("Length Error :");
  Serial.println(e);
}
}
