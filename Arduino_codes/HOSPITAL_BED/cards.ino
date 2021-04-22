void card1() { //this was disabled
  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) { //if there a card
      dump_byte_array(mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size); //a function thats read the card
      MFRC522::PICC_Type piccType = mfrc522[reader].PICC_GetType(mfrc522[reader].uid.sak);
      mfrc522[reader].PICC_HaltA();
      mfrc522[reader].PCD_StopCrypto1();
      rfidCardRead.toCharArray(writeRFID1, rfidCardRead.length() + 1);
      mySerial.println(); mySerial.println("THE CARD1: "); mySerial.println(writeRFID1);
      writeMyRFID1(); delay(100); getMyRFID1(); delay(100);
      rfidCardRead = ""; resets(); currentState = 2; delay(500);
    }
  }
}
void card2() {
  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) { //if there a card
      dump_byte_array(mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size); //a function thats read the card
      MFRC522::PICC_Type piccType = mfrc522[reader].PICC_GetType(mfrc522[reader].uid.sak);
      mfrc522[reader].PICC_HaltA();
      mfrc522[reader].PCD_StopCrypto1();
      rfidCardRead.toCharArray(writeRFID2, rfidCardRead.length() + 1);
      mySerial.println(); mySerial.println("THE CARD2: "); mySerial.println(writeRFID2);
      writeMyRFID2(); delay(100); getMyRFID2(); delay(100);
      rfidCardRead = ""; resets(); currentState = 2; delay(500);
    }
  }
}
void card3() {
  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) { //if there a card
      dump_byte_array(mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size); //a function thats read the card
      MFRC522::PICC_Type piccType = mfrc522[reader].PICC_GetType(mfrc522[reader].uid.sak);
      mfrc522[reader].PICC_HaltA();
      mfrc522[reader].PCD_StopCrypto1();
      rfidCardRead.toCharArray(writeRFID3, rfidCardRead.length() + 1);
      mySerial.println(); mySerial.println("THE CARD3:"); mySerial.println(writeRFID3);
      writeMyRFID3(); delay(100); getMyRFID3(); delay(100);
      rfidCardRead = ""; resets(); currentState = 2; delay(500);
    }
  }
}

void deleteCard() {
  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) { //if there a card
      dump_byte_array(mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size); //a function thats read the card
      MFRC522::PICC_Type piccType = mfrc522[reader].PICC_GetType(mfrc522[reader].uid.sak);
      mfrc522[reader].PICC_HaltA();
      mfrc522[reader].PCD_StopCrypto1();
      mySerial.println(); mySerial.println("READED CARD: "); mySerial.println(rfidCardRead);
      if (rfidCardRead == rfidCard1) {
        mySerial.println("CANT DELETE");
        //        mySerial.println("DELETE RFID1: "); char deleteRFID1[] = "          ";
        //        EEPROM.writeBlock<char>(addressCharArray1, deleteRFID1, intLength); delay(100);
        //        getMyRFID1();
      } else if (rfidCardRead == rfidCard2) {
        mySerial.println("DELETE RFID2: "); char deleteRFID2[] = "          ";
        EEPROM.writeBlock<char>(addressCharArray2, deleteRFID2, intLength); delay(100);
        getMyRFID2();
      } else if (rfidCardRead == rfidCard3) {
        mySerial.println("DELETE RFID3: "); char deleteRFID3[] = "          ";
        EEPROM.writeBlock<char>(addressCharArray3, deleteRFID3, intLength); delay(100);
        getMyRFID3();
      }
      rfidCardRead = ""; resets(); mySerial.println("DONE"); currentState = 2; delay(500);
    }
  }
}
