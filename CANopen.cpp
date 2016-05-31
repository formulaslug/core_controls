#include "CANopen.h"
#include <kinetis_flexcan.h>

CANopen::CANopen(uint32_t id, uint32_t baud) : FlexCAN(baud) {
  CAN_filter_t mask;
  mask.rtr = 0;
  mask.ext = 0;
  mask.id = id;
  begin(mask);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWriteFast(LED_BUILTIN, 0);

  setFilters({0x620, 0x002});
}

CANopen::~CANopen() {
  end();
}

void CANopen::setFilters(std::initializer_list<uint32_t> filters) {
  CAN_filter_t filter;
  filter.rtr = 0;
  filter.ext = 0;

  uint32_t i = 0;
  for (auto id : filters) {
    // Set remaining filters to last entry if the provided list is too short
    if (i < filters.size()) {
      filter.id = id;
      i++;
    }
    setFilter(filter, i);
  }
}

bool CANopen::sendMessage(const CAN_message_t& msg) {
  if (write(msg)) {
    digitalWriteFast(LED_BUILTIN, 1);
    return true;
  } else {
    digitalWriteFast(LED_BUILTIN, 0);
    return false;
  }
}

bool CANopen::recvMessage(CAN_message_t& msg) {
  return read(msg);
}

void CANopen::printTxMsg(const CAN_message_t& msg) const {
  Serial.print("[EVENT]: CAN message TX >> [ COB-ID: 0x");

  // Print the node's ID
  Serial.print(msg.id, HEX);

  Serial.print(", payload: ");
  for (uint32_t i = 0; i < msg.len; ++i) {
    Serial.print(" 0x");
    // Print every byte of message payload
    Serial.print(msg.buf[i], HEX);
  }

  Serial.println(" ]");
}

void CANopen::printRxMsg(const CAN_message_t& msg) const {
  Serial.print("[EVENT]: CAN message RX >> [ COB-ID: 0x");

  // Print the node's ID
  Serial.print(msg.id, HEX);

  Serial.print(", payload: ");
  for (uint32_t i = 0; i < msg.len; ++i) {
    Serial.print(" 0x");
    // Print every byte of message payload
    Serial.print(msg.buf[i], HEX);
  }

  Serial.println(" ]");
}

/**
 * @desc Transmits all enqueued messages, in g_canTxQueue, of type CAN_message_t. Enqueue
 *       them onto the transmit logs queue after so that they can be printed
 */
void CANopen::processTx() {
  while (txQueue.Size() > 0) {
    // write message
    sendMessage(txQueue[0]);
    // enqueue them onto the logs queue
    txLogsQueue.PushBack(txQueue[0]);
    // dequeue new message
    txQueue.PopFront();
  }
}

/**
 * @desc Enqueue any messages apearing on the CAN bus
 */
void CANopen::processRx() {
  static CAN_message_t rxMsgTmp;
  while (recvMessage(rxMsgTmp)) {
    rxQueue.PushBack(rxMsgTmp);
    rxLogsQueue.PushBack(rxMsgTmp); // TODO: figure out a way to remove this duplication
  }
}

/**
 * @desc Prints over serial all messages currently in the tx logs queue
 */
void CANopen::printTxAll() {
  static CAN_message_t queueMsg;
  queueMsg = txLogsQueue.PopFront();
  while (queueMsg.id) {
    // print
    printTxMsg(queueMsg);
    // dequeue another message
    queueMsg = txLogsQueue.PopFront();
  }
}

/**
 * @desc Prints over serial all messages currently in the rx queue
 */
void CANopen::printRxAll() {
  static CAN_message_t msg;
  msg = rxLogsQueue.PopFront();
  while (msg.id) {
    // print
    printRxMsg(msg);
    // dequeue another message
    msg = rxLogsQueue.PopFront();
  }
}

/**
 * @desc Enqueues a packaged message to be transmitted over the CAN bus
 */
void CANopen::queueTxMsg(CAN_message_t msg) {
  txQueue.PushBack(msg);
}

/**
 * @desc Dequeues a packaged message to be unpacked and used
 * @param msg The message at the front of the rx queue
 */
CAN_message_t CANopen::dequeueRxMsg() {
  return rxQueue.PopFront();
}

/**
 * @desc Gets the current size of the tx queue
 * @return The size
 */
uint8_t CANopen::txQueueSize() {
  return txQueue.Size();
}

/**
 * @desc Gets the current size of the rx queue
 * @return The size
 */
uint8_t CANopen::rxQueueSize() {
  return rxQueue.Size();
}
