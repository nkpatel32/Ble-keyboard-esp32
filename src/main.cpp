#include <SPI.h>
#include <MFRC522.h>
#include <BleKeyboard.h>

#define SS_PIN    21   // RFID SDA (CS)
#define RST_PIN   22   // RFID Reset
#define BUZZER_PIN 13  // Buzzer pin

// Create BleKeyboard instance with device name "Card Scanner"
BleKeyboard bleKeyboard("Card Scanner");

MFRC522 mfrc522(SS_PIN, RST_PIN);

// Declare beep function prototype so setup() knows about it
void beep(int durationMs);

void setup() {
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  // bleKeyboard.setSecurity(true);  // REMOVE or COMMENT OUT this line because it's not supported

  bleKeyboard.begin();

  // Startup beep (active buzzer assumed)
  beep(300);

  Serial.println("RFID Reader Ready");
}

void loop() {
  // Check BLE connection status changes and beep accordingly
  static bool wasConnected = false;
  bool isConnected = bleKeyboard.isConnected();

  if (isConnected && !wasConnected) {
    Serial.println("BLE Keyboard Connected");
    beep(150); // Beep on connect
  } 
  else if (!isConnected && wasConnected) {
    Serial.println("BLE Keyboard Disconnected");
    beep(500); // Longer beep on disconnect
  }
  wasConnected = isConnected;

  if (!isConnected) return;

  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  String rfidData = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) rfidData += "0";
    rfidData += String(mfrc522.uid.uidByte[i], HEX);
  }
  rfidData.toUpperCase();

  unsigned long int rfidDataInt = strtoul(rfidData.c_str(), NULL, 16);
  long rfidDataLong = static_cast<long>(rfidDataInt);

  Serial.print("RFID UID String: ");
  Serial.println(rfidData);
  Serial.print("RFID UID as unsigned long: ");
  Serial.println(rfidDataInt);
  Serial.print("RFID UID as long: ");
  Serial.println(rfidDataLong);

  // Send RFID UID as decimal number via BLE keyboard
  bleKeyboard.print(String(rfidDataLong));
  bleKeyboard.write(KEY_RETURN);

  // Beep on card read
  beep(150);

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();

  delay(1000);
}

// Helper function to beep buzzer for given milliseconds
void beep(int durationMs) {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(durationMs);
  digitalWrite(BUZZER_PIN, LOW);
}