// Copyright (c) 2016-2017 Formula Slug. All Rights Reserved.

#include "CANopenPDO.h"

#include <climits>
#include <cstdlib>

HeartbeatMessage::HeartbeatMessage(uint32_t id) {
  this->id = id;
  ext = 0;
  len = 2;
  timeout = 0;

  buf[0] = kPayloadHeartbeat >> 8;
  buf[1] = kPayloadHeartbeat;
}

ThrottleMessage::ThrottleMessage(uint16_t throttleVoltage, bool forwardSwitch) {
  id = kCobid_TPDO5;
  ext = 0;
  len = 7;
  timeout = 0;

  TPDO5 tpdo5;
  tpdo5.throttleInputVoltage = throttleVoltage;
  tpdo5.maxBatteryDischargeCurrent = 400;
  tpdo5.maxBatteryRechargeCurrent = 400;
  tpdo5.forwardSwitch = forwardSwitch;
  tpdo5.driveSelect1Switch = false;
  tpdo5.driveSelect2Switch = false;
  tpdo5.reverseSwitch = false;

  std::memcpy(&buf, &tpdo5, sizeof(TPDO5));
}
