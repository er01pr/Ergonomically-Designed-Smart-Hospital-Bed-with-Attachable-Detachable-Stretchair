void homePosition() {
  digitalWrite(relayActuator1Backward, LOW); digitalWrite(relayActuator2Forward, LOW); //activate the relay to power on th actuator
  while (1) {
    limitActuatorRead = digitalRead(limitActuator); //reading the data of limit switch, if trigger data = 0, if not data = 1
    if (limitActuatorRead == 0) { //deactivate when limit switch is triggered
      delay(1000); digitalWrite(relayActuator1Backward, HIGH); digitalWrite(relayActuator2Forward, HIGH); positionState = 1; delay(100); break;
    }
  }
}
void position1() {
  mySerial.println("POSITION 1 START");
  if (positionState == 3) { //activate relay to power on actuator and start the timer
    digitalWrite(relayActuator1Backward, LOW); digitalWrite(relayActuator2Forward, LOW); //actuatorDelay.start(fullDelay);
    while (1) {
      btnEmergencyRead = digitalRead(btnEmergency); //reading the data of button, if press data = 0, if not data = 1
      limitActuatorRead = digitalRead(limitActuator);
      if (limitActuatorRead == 0) { //when timer is finished deactivate the relay to power off actuator
        digitalWrite(relayActuator1Backward, HIGH); digitalWrite(relayActuator2Forward, HIGH); actuatorDelay.stop(); delay(100); break;
      } else if (btnEmergencyRead == 0) { //if button emergency is press, deactivate the relay to power off actuator, go to flagEmergency 1
        digitalWrite(relayActuator1Backward, HIGH); digitalWrite(relayActuator2Forward, HIGH); actuatorDelay.stop(); flagEmergency = 1; delay(100); break;
      }
      //      if (actuatorDelay.isFinished()) { //when timer is finished deactivate the relay to power off actuator
      //        digitalWrite(relayActuator1Backward, HIGH); digitalWrite(relayActuator2Forward, HIGH); actuatorDelay.stop(); delay(100); break;
      //      } else if (btnEmergencyRead == 0) { //if button emergency is press, deactivate the relay to power off actuator, go to flagEmergency 1
      //        digitalWrite(relayActuator1Backward, HIGH); digitalWrite(relayActuator2Forward, HIGH); actuatorDelay.stop(); flagEmergency = 1; delay(100); break;
      //      }
    }
  } else if (positionState == 2) {
    digitalWrite(relayActuator1Backward, LOW); digitalWrite(relayActuator2Forward, LOW); actuatorDelay.start(halfDelay);
    while (1) {
      btnEmergencyRead = digitalRead(btnEmergency); limitActuatorRead = digitalRead(limitActuator);
      if (limitActuatorRead == 0) { //when timer is finished deactivate the relay to power off actuator
        digitalWrite(relayActuator1Backward, HIGH); digitalWrite(relayActuator2Forward, HIGH); actuatorDelay.stop(); delay(100); break;
      } else if (btnEmergencyRead == 0) { //if button emergency is press, deactivate the relay to power off actuator, go to flagEmergency 1
        digitalWrite(relayActuator1Backward, HIGH); digitalWrite(relayActuator2Forward, HIGH); actuatorDelay.stop(); flagEmergency = 1; delay(100); break;
      }
      //      if (actuatorDelay.isFinished()) {
      //        digitalWrite(relayActuator1Backward, HIGH); digitalWrite(relayActuator2Forward, HIGH); actuatorDelay.stop(); delay(100); break;
      //      } else if (btnEmergencyRead == 0) {
      //        digitalWrite(relayActuator1Backward, HIGH); digitalWrite(relayActuator2Forward, HIGH); actuatorDelay.stop(); flagEmergency = 1; delay(100); break;
      //      }
    }
  } else {
    allOff(); delay(100);
  }
  positionState = 1; resets(); flagButton = 0; mySerial.println("POSITION 1 DONE");
}
void position2() {
  mySerial.println("POSITION 2 START");
  if (positionState == 1) {
    digitalWrite(relayActuator1Forward, LOW); digitalWrite(relayActuator2Backward, LOW); actuatorDelay.start(halfDelay);
    while (1) {
      btnEmergencyRead = digitalRead(btnEmergency);
      if (actuatorDelay.isFinished()) {
        digitalWrite(relayActuator1Forward, HIGH); digitalWrite(relayActuator2Backward, HIGH); actuatorDelay.stop(); delay(100); break;
      } else if (btnEmergencyRead == 0) {
        digitalWrite(relayActuator1Forward, HIGH); digitalWrite(relayActuator2Backward, HIGH); actuatorDelay.stop(); flagEmergency = 1; delay(100); break;
      }
    }
  } else if (positionState == 3) {
    digitalWrite(relayActuator1Backward, LOW); digitalWrite(relayActuator2Forward, LOW); actuatorDelay.start(halfDelay);
    while (1) {
      btnEmergencyRead = digitalRead(btnEmergency);
      if (actuatorDelay.isFinished()) {
        digitalWrite(relayActuator1Backward, HIGH); digitalWrite(relayActuator2Forward, HIGH); actuatorDelay.stop();  delay(100); break;
      } else if (btnEmergencyRead == 0) {
        digitalWrite(relayActuator1Backward, HIGH); digitalWrite(relayActuator2Forward, HIGH); actuatorDelay.stop(); flagEmergency = 1; delay(100); break;
      }
    }
  } else {
    allOff(); delay(100);
  }
  positionState = 2; resets(); flagButton = 0; mySerial.println("POSITION 2 DONE");
}
void position3() {
  mySerial.println("POSITION 3 START");
  if (positionState == 1) {
    digitalWrite(relayActuator1Forward, LOW); digitalWrite(relayActuator2Backward, LOW); actuatorDelay.start(fullDelay);
    while (1) {
      btnEmergencyRead = digitalRead(btnEmergency);
      if (actuatorDelay.isFinished()) {
        digitalWrite(relayActuator1Forward, HIGH); digitalWrite(relayActuator2Backward, HIGH); actuatorDelay.stop(); delay(100); break;
      } else if (btnEmergencyRead == 0) {
        digitalWrite(relayActuator1Forward, HIGH); digitalWrite(relayActuator2Backward, HIGH); actuatorDelay.stop(); flagEmergency = 1; delay(100); break;
      }
    }
  } else if (positionState == 2) {
    digitalWrite(relayActuator1Forward, LOW); digitalWrite(relayActuator2Backward, LOW); actuatorDelay.start(halfDelay);
    while (1) {
      btnEmergencyRead = digitalRead(btnEmergency);
      if (actuatorDelay.isFinished()) {
        digitalWrite(relayActuator1Forward, HIGH); digitalWrite(relayActuator2Backward, HIGH); actuatorDelay.stop(); delay(100); break;
      } else if (btnEmergencyRead == 0) {
        digitalWrite(relayActuator1Forward, HIGH); digitalWrite(relayActuator2Backward, HIGH); actuatorDelay.stop(); flagEmergency = 1; delay(100); break;
      }
    }
  } else {
    allOff(); delay(100);
  }
  positionState = 3; resets(); flagButton = 0; mySerial.println("POSITION 3 DONE");
}
void allOff() {
  digitalWrite(relayActuator1Forward, HIGH); digitalWrite(relayActuator1Backward, HIGH);
  digitalWrite(relayActuator2Forward, HIGH); digitalWrite(relayActuator2Backward, HIGH);
}
void resets() {
  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    mfrc522[reader].PCD_Init(SS_PIN, RST_PIN); // Init each MFRC522 card, for one card
    Serial.print(F("Reader ")); Serial.print(reader); Serial.print(F(": "));
    mfrc522[reader].PCD_DumpVersionToSerial();
  }
  mfrc522load.PCD_Init(); delay(100);
}
