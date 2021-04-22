void getMyRFID1() {
  EEPROM.readBlock<char>(addressCharArray1, getRFID1, intLength);
  rfidCard1 = String(getRFID1);
  mySerial.print("SAVE RFID1: "); mySerial.println(rfidCard1);
}
void getMyRFID2() {
  EEPROM.readBlock<char>(addressCharArray2, getRFID2, intLength);
  rfidCard2 = String(getRFID2);
  mySerial.print("SAVE RFID2: "); mySerial.println(rfidCard2);
}
void getMyRFID3() {
  EEPROM.readBlock<char>(addressCharArray3, getRFID3, intLength);
  rfidCard3 = String(getRFID3);
  mySerial.print("SAVE RFID3: "); mySerial.println(rfidCard3);
}
void writeMyRFID1() {
  mySerial.print("WRITE RFID1: ");
  EEPROM.writeBlock<char>(addressCharArray1, writeRFID1, intLength);
  mySerial.println(writeRFID1);
}
void writeMyRFID2() {
  mySerial.print("WRITE RFID2: ");
  EEPROM.writeBlock<char>(addressCharArray2, writeRFID2, intLength);
  mySerial.println(writeRFID2);
}
void writeMyRFID3() {
  mySerial.print("WRITE RFID3: ");
  EEPROM.writeBlock<char>(addressCharArray3, writeRFID3, intLength);
  mySerial.println(writeRFID3);
}
