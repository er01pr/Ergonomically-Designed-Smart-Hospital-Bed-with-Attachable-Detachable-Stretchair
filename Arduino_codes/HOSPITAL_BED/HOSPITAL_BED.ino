#include <SPI.h>
#include <MFRC522.h>
#include <millisDelay.h>
#include <SoftwareSerial.h>
#include <EEPROMex.h>
#include "Arduino.h"
#define btn0 22
#define btn45 24
#define btnMax 26
#define btnLock 34
#define btnEmergency 30
#define relayActuator1Forward 23
#define relayActuator1Backward 25
#define relayActuator2Forward 27
#define relayActuator2Backward 29
#define relayMagneticLock 31
#define limitActuator 4
#define btnAddDel 32

SoftwareSerial mySerial (10, 11);
//For Mega: RST->5, SDA(SS)->53, MOSI->51, MISO->50, SCK->52
//For UNO: RST->9, SDA(SS)->10, MOSI->11, MISO->12, SCK->13

constexpr uint8_t RST_PIN = 5;
constexpr uint8_t SS_PIN = 53;
constexpr uint8_t NR_OF_READERS = 1;

MFRC522 mfrc522[NR_OF_READERS];   // Create MFRC522 instance.
MFRC522 mfrc522load(SS_PIN, RST_PIN);

millisDelay actuatorDelay;

String rfidCardRead, rfidCard1, rfidCard2, rfidCard3;
const int maxAllowedWrites = 80;
const int memBase          = 0;
int addressCharArray1 = 1, addressCharArray2 = 21, addressCharArray3 = 41, intLength = 10;
char writeRFID1[10] = "", writeRFID2[10] = "", writeRFID3[10] = "";
char getRFID1[] = "", getRFID2[] = "", getRFID3[] = "";
int currentState = 0, btn0Read, btn45Read, btnMaxRead, btnLockRead, btnEmergencyRead, btnAddDelRead, limitActuatorRead, positionState = 1;
int flagControl = 0, flagLock = 0, flagEmergency = 0, flagButton = 0, flagAddDelete = 0, flagLogin = 0, flagLogout = 0;
String serial = "";
long fullDelay = 30000, halfDelay = 15000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);
  SPI.begin();
  pinMode(btn0, INPUT_PULLUP); pinMode(btn45, INPUT_PULLUP); pinMode(btnMax, INPUT_PULLUP);
  pinMode(btnLock, INPUT_PULLUP); pinMode(btnEmergency, INPUT_PULLUP);  pinMode(btnAddDel, INPUT_PULLUP);
  pinMode(limitActuator, INPUT_PULLUP);
  pinMode(relayActuator1Forward, OUTPUT); pinMode(relayActuator1Backward, OUTPUT);
  pinMode(relayActuator2Forward, OUTPUT); pinMode(relayActuator2Backward, OUTPUT); pinMode(relayMagneticLock, OUTPUT);
  digitalWrite(relayActuator1Forward, HIGH); digitalWrite(relayActuator1Backward, HIGH);
  digitalWrite(relayActuator2Forward, HIGH); digitalWrite(relayActuator2Backward, HIGH); digitalWrite(relayMagneticLock, LOW);
  EEPROM.setMemPool(memBase, EEPROMSizeMega);
  EEPROM.setMaxAllowedWrites(maxAllowedWrites);
  delay(100);
  mySerial.println();
  homePosition();
  getMyRFID1(); delay(100);
  getMyRFID2(); delay(100);
  getMyRFID3(); delay(100);

  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    mfrc522[reader].PCD_Init(SS_PIN, RST_PIN); // Init each MFRC522 card, for one card
    Serial.print(F("Reader "));
    Serial.print(reader);
    Serial.print(F(": "));
    mfrc522[reader].PCD_DumpVersionToSerial();
  }
  mfrc522load.PCD_Init();
  mySerial.println("START");
  //  currentState = 7; //use to register main user card
}

void loop() {
  // put your main code here, to run repeatedly:
//      testButton();

  if (currentState == 0) {
    for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
      if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) { //if there a card
        dump_byte_array(mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size); //a function thats read the card
        MFRC522::PICC_Type piccType = mfrc522[reader].PICC_GetType(mfrc522[reader].uid.sak);
        mfrc522[reader].PICC_HaltA();
        mfrc522[reader].PCD_StopCrypto1();
        mySerial.println(); mySerial.println("THE CARD"); mySerial.println(rfidCardRead);
        if (rfidCardRead == rfidCard1) {
          mySerial.println("RFID MATCH"); rfidCardRead = ""; currentState = 1; flagAddDelete = 1; flagLogin = 1; flagLock = 0;
          flagControl = 0; mySerial.println("ON"); delay(100);
          for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
            mfrc522[reader].PCD_Init(SS_PIN, RST_PIN); // Init each MFRC522 card, for one card
            Serial.print(F("Reader ")); Serial.print(reader); Serial.print(F(": "));
            mfrc522[reader].PCD_DumpVersionToSerial();
          }
          mfrc522load.PCD_Init(); delay(1000);
        } else if (rfidCardRead == rfidCard2) {
          mySerial.println("RFID MATCH"); rfidCardRead = ""; currentState = 1; flagAddDelete = 0; flagLogin = 2; flagLock = 0;
          flagControl = 0; mySerial.println("ON"); delay(100);
          for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
            mfrc522[reader].PCD_Init(SS_PIN, RST_PIN); // Init each MFRC522 card, for one card
            Serial.print(F("Reader ")); Serial.print(reader); Serial.print(F(": "));
            mfrc522[reader].PCD_DumpVersionToSerial();
          }
          mfrc522load.PCD_Init(); delay(1000);
        } else if (rfidCardRead == rfidCard3) {
          mySerial.println("RFID MATCH"); rfidCardRead = ""; currentState = 1; flagAddDelete = 0; flagLogin = 3; flagLock = 0;  
          flagControl = 0; mySerial.println("ON"); delay(100);
          for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
            mfrc522[reader].PCD_Init(SS_PIN, RST_PIN); // Init each MFRC522 card, for one card
            Serial.print(F("Reader ")); Serial.print(reader); Serial.print(F(": "));
            mfrc522[reader].PCD_DumpVersionToSerial();
          }
          mfrc522load.PCD_Init(); delay(1000);
        } else {
          mySerial.println("RFID NOT MATCH "); rfidCardRead = "";
        }
      }
    }
  }

  if (currentState == 1) {
    for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
      if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) { //if there a card
        dump_byte_array(mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size); //a function thats read the card
        MFRC522::PICC_Type piccType = mfrc522[reader].PICC_GetType(mfrc522[reader].uid.sak);
        mfrc522[reader].PICC_HaltA();
        mfrc522[reader].PCD_StopCrypto1();
        mySerial.println(); mySerial.println("THE CARD"); mySerial.println(rfidCardRead);
        if (rfidCardRead == rfidCard1 && flagLogin == 1) {
          mySerial.println("RFID MATCH"); rfidCardRead = ""; currentState = 0; flagControl = 1; flagAddDelete = 0; flagLogin = 0;
          mySerial.println("OFF"); delay(100);
          for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
            mfrc522[reader].PCD_Init(SS_PIN, RST_PIN); // Init each MFRC522 card, for one card
            Serial.print(F("Reader ")); Serial.print(reader); Serial.print(F(": "));
            mfrc522[reader].PCD_DumpVersionToSerial();
          }
          mfrc522load.PCD_Init(); delay(1000);
        } else if (rfidCardRead == rfidCard2  && flagLogin == 2) {
          mySerial.println("RFID MATCH"); rfidCardRead = ""; currentState = 0; flagControl = 1; flagAddDelete = 0; flagLogin = 0;
          mySerial.println("OFF"); delay(100);
          for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
            mfrc522[reader].PCD_Init(SS_PIN, RST_PIN); // Init each MFRC522 card, for one card
            Serial.print(F("Reader ")); Serial.print(reader); Serial.print(F(": "));
            mfrc522[reader].PCD_DumpVersionToSerial();
          }
          mfrc522load.PCD_Init(); delay(1000);
        } else if (rfidCardRead == rfidCard3  && flagLogin == 3) {
          mySerial.println("RFID MATCH"); rfidCardRead = ""; currentState = 0; flagControl = 1; flagAddDelete = 0; flagLogin = 0;
          mySerial.println("OFF"); delay(100);
          for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
            mfrc522[reader].PCD_Init(SS_PIN, RST_PIN); // Init each MFRC522 card, for one card
            Serial.print(F("Reader ")); Serial.print(reader); Serial.print(F(": "));
            mfrc522[reader].PCD_DumpVersionToSerial();
          }
          mfrc522load.PCD_Init(); delay(1000);
        } else {
          mySerial.println("RFID NOT MATCH "); rfidCardRead = "";
        }
      }
    }

    process();
    if (flagEmergency == 1) {
      mySerial.println("EMERGENCY STOP");
      while (1) {
        btnEmergencyRead = digitalRead(btnEmergency); //reading the data of button, if press data = 0, if not data = 1
        if (btnEmergencyRead == 0) {
          mySerial.println("EMERGENCY STOP PRESSED");
          homePosition(); resets(); flagEmergency = 0; flagButton = 0; break;
        }
      }
    }

    btnAddDelRead = digitalRead(btnAddDel);
    if (btnAddDelRead == 0 && flagAddDelete == 1) {
      mySerial.println("STATE 2"); currentState = 2; delay(1000);
    }
  }

  if (currentState == 2) {
    btn0Read = digitalRead(btn0); btn45Read = digitalRead(btn45); btnMaxRead = digitalRead(btnMax); btnLockRead = digitalRead(btnLock);
    btnAddDelRead = digitalRead(btnAddDel);
    if (btn0Read == 0) {
      //mySerial.println("CARD1"); currentState = 3;
    } else if (btn45Read == 0) {
      mySerial.println("CARD2"); currentState = 4;
    } else if (btnMaxRead == 0) {
      mySerial.println("CARD3"); currentState = 5;
    } else if (btnLockRead == 0) {
      mySerial.println("DELETE"); currentState = 6;
    } else if (btnAddDelRead == 0) {
      mySerial.println("STATE 0"); currentState = 0;
      rfidCardRead = ""; flagControl = 1; flagAddDelete = 0; flagLogin = 0; delay(1000);
    }
  }

  if (currentState == 3) {
    //    card1();
  }
  if (currentState == 4) {
    card2();
  }
  if (currentState == 5) {
    card3();
  }
  if (currentState == 6) {
    deleteCard();
  }

  if (currentState == 7) { //use to register main user card
    for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
      if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) { //if there a card
        dump_byte_array(mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size); //a function thats read the card
        MFRC522::PICC_Type piccType = mfrc522[reader].PICC_GetType(mfrc522[reader].uid.sak);
        mfrc522[reader].PICC_HaltA();
        mfrc522[reader].PCD_StopCrypto1();
        rfidCardRead.toCharArray(writeRFID1, rfidCardRead.length() + 1);
        mySerial.println(); mySerial.println("THE CARD"); mySerial.println(writeRFID1);
        writeMyRFID1(); delay(100);
        rfidCardRead = ""; resets(); delay(1000);
      }
    }
  }

}

void dump_byte_array(byte * buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : "");
    Serial.print(buffer[i], DEC);
    //const char currentChar = (buffer[i] < 0x10 ? " 0" : "");
    rfidCardRead += buffer[i]; //append all buffer to a string type variable
  }
}
