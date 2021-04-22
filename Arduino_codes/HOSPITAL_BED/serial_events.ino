//void serialEvent() {
//  serial = Serial.readStringUntil('\n');
//
//  if (false) {
//  }
//  else if (serial == "p1") {
//    Serial.println("POSITION 1");
//    position1();
//  }
//  else if (serial == "p2") {
//    Serial.println("POSITION 2");
//    position2();
//  }
//  else if (serial == "p3") {
//    Serial.println("POSITION 3");
//    position3();
//  }
//  else if (serial == "m1") {
//    Serial.println("MAGNETIC LOCK ON");
//    digitalWrite(relayMagneticLock, LOW);
//  }
//  else if (serial == "m2") {
//    Serial.println("MAGNETIC LOCK OFF");
//    digitalWrite(relayMagneticLock, HIGH);
//  }
//  else if (serial == "off") {
//    Serial.println("OFF");
//    digitalWrite(relayActuator1Forward, HIGH); digitalWrite(relayActuator1Backward, HIGH);
//    digitalWrite(relayActuator2Forward, HIGH); digitalWrite(relayActuator2Backward, HIGH);
//  }
//}
