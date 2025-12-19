#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// تعريف الأطراف - RFID
#define RST_PIN 9
#define SS_PIN 10

// تعريف الأطراف - Servos
#define SERVO_ENTRY 2
#define SERVO_EXIT 3
#define SERVO_VIP 8

// تعريف الأطراف - IR Sensors
#define IR_ENTRY 4
#define IR_EXIT 5
#define IR_SLOT_VIP A3
#define IR_SLOT2 A2
#define IR_SLOT3 A1

// إنشاء كائنات
MFRC522 rfid(SS_PIN, RST_PIN);
Servo servoEntry;
Servo servoExit;
Servo servoVIP;

// الشاشة
LiquidCrystal_I2C lcd(0x27, 16, 2);

// الكارت المصرح به للـ VIP
byte authorizedUID[] = {0xD0, 0x66, 0xBE, 0x5F};

// متغيرات النظام
int availableSlots = 2;
bool slotVIPOccupied = false;
bool slot2Occupied = false;
bool slot3Occupied = false;
bool vipSlotOpen = false;

// متغيرات التحكم في البوابات
bool entryGateOpen = false;
bool exitGateOpen = false;
unsigned long entryCarLeftTime = 0;
unsigned long exitCarLeftTime = 0;
bool entryCarWasPresent = false;
bool exitCarWasPresent = false;
bool entryOpenedByRFID = false;

// متغيرات VIP
unsigned long vipGateOpenTime = 0;
bool waitingForVIPCar = false;

// متغير جديد: هل العربية عدت على الأقل مرة واحدة على المستشعر؟
bool entryCarDetectedAtLeastOnce = false;

void setup() {
  Serial.begin(9600);
  
  Wire.begin();
  delay(100);
  
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Parking System");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");
  delay(1000);
  
  SPI.begin();
  rfid.PCD_Init();
  delay(100);
  
  lcd.setCursor(0, 1);
  lcd.print("RFID Ready...  ");
  delay(500);
  
  servoEntry.attach(SERVO_ENTRY);
  servoExit.attach(SERVO_EXIT);
  servoVIP.attach(SERVO_VIP);
  
  servoEntry.write(90);
  servoExit.write(90);
  servoVIP.write(90);
  
  lcd.setCursor(0, 1);
  lcd.print("Servos Ready... ");
  delay(500);
  
  pinMode(IR_ENTRY, INPUT);
  pinMode(IR_EXIT, INPUT);
  pinMode(IR_SLOT_VIP, INPUT);
  pinMode(IR_SLOT2, INPUT);
  pinMode(IR_SLOT3, INPUT);
  
  lcd.setCursor(0, 1);
  lcd.print("System Ready!   ");
  
  Serial.println("=================================");
  Serial.println("   نظام المواقف الذكي جاهز");
  Serial.println("=================================");
  Serial.println("قرب الكارت للدخول إلى موقف VIP");
  Serial.println();
  
  delay(1500);
  lcd.clear();
}

void loop() {
  checkParkingSlots();
  checkRFID();
  handleEntryGate();
  handleExitGate();
  handleVIPGate();
  
  static unsigned long lastDisplayUpdate = 0;
  if (millis() - lastDisplayUpdate > 500) {
    updateLCD();
    lastDisplayUpdate = millis();
  }
  
  static unsigned long lastStatusPrint = 0;
  if (millis() - lastStatusPrint > 2000) {
    printStatus();
    lastStatusPrint = millis();
  }
  
  delay(50);
}

void checkParkingSlots() {
  bool newSlotVIP = (digitalRead(IR_SLOT_VIP) == LOW);
  bool newSlot2 = (digitalRead(IR_SLOT2) == LOW);
  bool newSlot3 = (digitalRead(IR_SLOT3) == LOW);
  
  if (newSlotVIP != slotVIPOccupied || 
      newSlot2 != slot2Occupied || 
      newSlot3 != slot3Occupied) {
    
    slotVIPOccupied = newSlotVIP;
    slot2Occupied = newSlot2;
    slot3Occupied = newSlot3;
    
    availableSlots = 2;
    if (slot2Occupied) availableSlots--;
    if (slot3Occupied) availableSlots--;
    
    Serial.print("الأماكن المتاحة: ");
    Serial.print(availableSlots);
    Serial.print(" | VIP: ");
    Serial.println(slotVIPOccupied ? "مشغول" : "فارغ");
  }
}

void checkRFID() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }
  
  Serial.print("تم قراءة كارت: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
  }
  Serial.println();
  
  if (checkAuthorization()) {
    Serial.println("✓ كارت VIP مصرح!");
    
    if (!slotVIPOccupied && !vipSlotOpen) {
      openVIPGate();
      
      if (!entryGateOpen) {
        servoEntry.write(0);
        entryGateOpen = true;
        entryOpenedByRFID = true;
        entryCarWasPresent = false;
        entryCarDetectedAtLeastOnce = false; // reset
        entryCarLeftTime = 0;
        Serial.println(">>> فتح بوابة الدخول العادي بالكارت <<<");
      }
      
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("VIP Card OK!");
      lcd.setCursor(0, 1);
      lcd.print("Both Gates Open");
    } else if (slotVIPOccupied) {
      Serial.println("✗ موقف VIP مشغول!");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("VIP Slot Full!");
      lcd.setCursor(0, 1);
      lcd.print("Try Again Later");
    }
  } else {
    Serial.println("✗ كارت غير مصرح!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access Denied!");
    lcd.setCursor(0, 1);
    lcd.print("Wrong Card");
  }
  
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

bool checkAuthorization() {
  if (rfid.uid.size != 4) return false;
  
  for (byte i = 0; i < 4; i++) {
    if (rfid.uid.uidByte[i] != authorizedUID[i]) {
      return false;
    }
  }
  return true;
}

void openVIPGate() {
  servoVIP.write(0);
  vipSlotOpen = true;
  waitingForVIPCar = true;
  vipGateOpenTime = millis();
  Serial.println(">>> فتح باب VIP <<<");
}

void handleVIPGate() {
  if (!vipSlotOpen) return;
  
  bool carInVIPSlot = (digitalRead(IR_SLOT_VIP) == LOW);
  
  if (carInVIPSlot && waitingForVIPCar) {
    waitingForVIPCar = false;
    Serial.println("سيارة VIP دخلت الموقف");
  }
  
  if (millis() - vipGateOpenTime > 5000 || (carInVIPSlot && !waitingForVIPCar)) {
    servoVIP.write(90);
    vipSlotOpen = false;
    Serial.println("<<< إغلاق باب VIP <<<");
  }
}

void handleEntryGate() {
  bool carPresent = (digitalRead(IR_ENTRY) == LOW);
  
  // لو البوابة اتفتحت بالكارت
  if (entryOpenedByRFID) {
    // لو عربية دخلت على المستشعر لأول مرة
    if (carPresent && !entryCarWasPresent) {
      entryCarWasPresent = true;
      entryCarDetectedAtLeastOnce = true; // علم إن العربية وصلت
      Serial.println("عربية دخلت على مستشعر الدخول");
    }
    
    // لو العربية عدت (بس بعد ما تكون اتكشفت الأول)
    if (!carPresent && entryCarWasPresent) {
      entryCarWasPresent = false;
      entryCarLeftTime = millis();
      Serial.println("العربية عدت من بوابة الدخول - هيتم الإغلاق");
    }
    
    // قفل البوابة بس لو العربية عدت على المستشعر الأول
    if (entryCarDetectedAtLeastOnce && !entryCarWasPresent && entryCarLeftTime > 0) {
      if (millis() - entryCarLeftTime > 1000) {
        Serial.println("🔒 تنفيذ إغلاق بوابة الدخول...");
        servoEntry.write(90);
        delay(50);
        entryGateOpen = false;
        entryOpenedByRFID = false;
        entryCarDetectedAtLeastOnce = false;
        entryCarLeftTime = 0;
        Serial.println("✓ البوابة اتقفلت فعلاً");
      }
    }
    return;
  }
  
  // الكود العادي للمستشعر
  if (carPresent && !entryGateOpen && availableSlots > 0) {
    servoEntry.write(0);
    entryGateOpen = true;
    entryCarWasPresent = true;
    entryCarDetectedAtLeastOnce = true;
    Serial.println(">>> فتح بوابة الدخول بالمستشعر <<<");
  }
  
  if (!carPresent && entryCarWasPresent && entryGateOpen) {
    entryCarWasPresent = false;
    entryCarLeftTime = millis();
    Serial.println("العربية عدت من بوابة الدخول");
  }
  
  if (entryGateOpen && !entryCarWasPresent && entryCarLeftTime > 0) {
    if (millis() - entryCarLeftTime > 1000) {
      Serial.println("🔒 تنفيذ إغلاق بوابة الدخول...");
      servoEntry.write(90);
      delay(50);
      entryGateOpen = false;
      entryCarDetectedAtLeastOnce = false;
      entryCarLeftTime = 0;
      Serial.println("✓ البوابة اتقفلت فعلاً");
    }
  }
  
  if (carPresent && availableSlots == 0 && !entryGateOpen) {
    static unsigned long lastFullMessage = 0;
    if (millis() - lastFullMessage > 3000) {
      Serial.println("⚠ المواقف العادية ممتلئة!");
      lastFullMessage = millis();
    }
  }
}

void handleExitGate() {
  bool carPresent = (digitalRead(IR_EXIT) == LOW);
  
  if (carPresent && !exitGateOpen) {
    servoExit.write(180);
    exitGateOpen = true;
    exitCarWasPresent = true;
    Serial.println(">>> فتح بوابة الخروج <<<");
  }
  
  if (!carPresent && exitCarWasPresent && exitGateOpen) {
    exitCarWasPresent = false;
    exitCarLeftTime = millis();
    Serial.println("العربية عدت من بوابة الخروج");
  }
  
  if (exitGateOpen && !exitCarWasPresent && exitCarLeftTime > 0) {
    if (millis() - exitCarLeftTime > 1000) {
      servoExit.write(90);
      exitGateOpen = false;
      exitCarLeftTime = 0;
      Serial.println("<<< إغلاق بوابة الخروج <<<");
    }
  }
}

void updateLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Free:");
  lcd.print(availableSlots);
  lcd.print("/2");
  
  lcd.setCursor(9, 0);
  lcd.print("VIP:");
  lcd.print(slotVIPOccupied ? "X" : "O");
  
  lcd.setCursor(0, 1);
  lcd.print("S2:");
  lcd.print(slot2Occupied ? "X" : "O");
  lcd.print(" S3:");
  lcd.print(slot3Occupied ? "X" : "O");
  
  if (entryGateOpen) {
    lcd.setCursor(11, 1);
    lcd.print("IN");
  }
  if (exitGateOpen) {
    lcd.setCursor(14, 1);
    lcd.print("EX");
  }
}

void printStatus() {
  Serial.println("\n--- حالة النظام ---");
  Serial.print("المواقف العادية: ");
  Serial.print(availableSlots);
  Serial.println("/2");
  
  Serial.print("VIP: ");
  Serial.print(slotVIPOccupied ? "مشغول ✗" : "فارغ ✓");
  Serial.print(" | S2: ");
  Serial.print(slot2Occupied ? "مشغول ✗" : "فارغ ✓");
  Serial.print(" | S3: ");
  Serial.println(slot3Occupied ? "مشغول ✗" : "فارغ ✓");
  Serial.println("-------------------\n");
}
