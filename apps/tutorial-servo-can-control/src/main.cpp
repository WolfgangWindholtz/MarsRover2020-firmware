/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "CANBus.h"
#include "CANMsg.h"
#include "TutorialServo.h"
#include "hw_bridge.h"
#include "mbed.h"

// servo
TutorialServo servo_1(PA_1);

// AnalogIn potVoltageIn(PA_0);
// CAN Object
CANBus can1(CAN1_RX, CAN1_TX, HWBRIDGE::ROVERCONFIG::ROVER_CANBUS_FREQUENCY);
CANMsg rxMsg, txMsg;
// Threads
Thread rxCANProcessorThread(osPriorityAboveNormal);
Thread txCANProcessorThread(osPriorityBelowNormal);

// Incoming Message Processor
/*void rxCANProcessor() {
  const auto rxPeriod = 2ms;

  float servo_pos = 0.0, servo_range = 180;

  while (true) {
    if (can1.read(rxMsg)) {
      switch (rxMsg.getID()) {
        // had modifeid local hw-bridge
        case HWBRIDGE::CANID::SERVO_SET_POSITION:
          rxMsg.getPayload(servo_pos);

          servo_1.setPositionInDegrees(servo_pos * servo_range);
          break;
        default:
          break;
      }
    }

    ThisThread::sleep_for(rxPeriod);
  }
}*/

// Outgoing message processor
/*void txCANProcessor() {
  while (true) {
    // This thread does not sleep, but only executes if signaled by rxCANProcessor to write out a response
    // event_flags.wait_any(ACK_FLAG);
  }
}*/

int main() {
  printf("\r\n\r\n");
  printf("TUTORIAL SERVO APPLICATION STARTED\r\n");
  printf("=======================\r\n");

  // CAN init stuff
  /*can1.setFilter(HWBRIDGE::CANFILTER::ROVER_CANID_FIRST_TUT_RX, CANStandard,
                 HWBRIDGE::ROVERCONFIG::ROVER_CANID_FILTER_MASK);*/
  // rxCANProcessorThread.start(rxCANProcessor);
  // txCANProcessorThread.start(txCANProcessor);

  while (true) {
    // ThisThread::sleep_for(2ms);
  }
}