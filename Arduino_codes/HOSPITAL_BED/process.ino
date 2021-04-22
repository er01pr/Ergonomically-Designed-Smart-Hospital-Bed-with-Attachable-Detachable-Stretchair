void process() {
  if (flagControl == 0) {
    btn0Read = digitalRead(btn0); btn45Read = digitalRead(btn45); btnMaxRead = digitalRead(btnMax); 
    btnLockRead = digitalRead(btnLock); btnEmergencyRead = digitalRead(btnEmergency);
//    Serial.print(btn0Read); Serial.print("\t"); Serial.print(btn45Read); Serial.print("\t"); Serial.print(btnMaxRead); Serial.print("\t");
//    Serial.print(btnLockRead); Serial.print("\t"); Serial.print(btnEmergencyRead); Serial.print("\t"); Serial.print(btnAddDelRead);
//    Serial.print("\t"); Serial.println(limitActuatorRead);
    if (btn0Read == 0 && flagButton == 0) {
      flagButton = 1; position1(); 
    } else if (btn45Read == 0 && flagButton == 0) {
      flagButton = 1; position2();
    } else if (btnMaxRead == 0 && flagButton == 0) {
      flagButton = 1; position3();
    } else if (btnLockRead == 0 && flagLock == 0) {
      mySerial.println("UNLOCK"); digitalWrite(relayMagneticLock, HIGH); flagLock = 1; delay(1000); resets();
    } else if (btnLockRead == 0 && flagLock == 1) {
      mySerial.println("LOCK"); digitalWrite(relayMagneticLock, LOW); flagLock = 0; delay(1000); resets();
    }
  }
}
