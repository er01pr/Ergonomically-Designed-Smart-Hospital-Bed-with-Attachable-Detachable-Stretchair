void testButton() {
  while (1) {
    btn0Read = digitalRead(btn0); btn45Read = digitalRead(btn45); btnMaxRead = digitalRead(btnMax);
    btnLockRead = digitalRead(btnLock); btnEmergencyRead = digitalRead(btnEmergency);
    btnAddDelRead = digitalRead(btnAddDel); limitActuatorRead = digitalRead(limitActuator);
    Serial.print(btn0Read); Serial.print("\t"); Serial.print(btn45Read); Serial.print("\t"); Serial.print(btnMaxRead); Serial.print("\t");
    Serial.print(btnLockRead); Serial.print("\t"); Serial.print(btnEmergencyRead); Serial.print("\t"); Serial.print(btnAddDelRead);
    Serial.print("\t"); Serial.println(limitActuatorRead);
  }
}
void testWrite() {
 
}
