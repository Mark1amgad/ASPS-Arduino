// تعريف الأطراف
#define FLAME_SENSOR 2
#define TRIG_PIN 3
#define ECHO_PIN 4
#define BUZZER 5
#define LDR_PIN A0  // تغيير إلى A0 للقراءة الصحيحة
#define LED_PIN 7

// متغيرات النظام
bool fireDetected = false;
unsigned long lastBuzzerToggle = 0;
unsigned long fireDetectedTime = 0;
bool autoLightOn = false;

// إعدادات
const int DARK_THRESHOLD = 300;        // عتبة الظلام (أقل = أظلم)
const int DANGER_DISTANCE = 2;         // مسافة خطر شديد (سم)
const int WARNING_DISTANCE = 10;       // مسافة تحذير (سم)
const int FIRE_ALARM_DURATION = 10000; // مدة إنذار الحريق

// متغيرات البازر
unsigned long lastBeep = 0;
bool buzzerState = false;

void setup() {
  Serial.begin(9600);
  
  // تهيئة الأطراف
  pinMode(FLAME_SENSOR, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  
  // إيقاف البازر والليد
  digitalWrite(BUZZER, LOW);
  digitalWrite(LED_PIN, LOW);
  
  Serial.println("=================================");
  Serial.println("نظام الأمان والإضاءة جاهز");
  Serial.println("=================================");
  delay(1000);
}

void loop() {
  // 1. فحص مستشعر اللهب
  checkFlame();
  
  // 2. قياس المسافة والتحذير
  float distance = getDistance();
  handleDistanceWarning(distance);
  
  // 3. التحكم في الإضاءة التلقائية
  autoLight();
  
  // 4. عرض الحالة
  static unsigned long lastDisplay = 0;
  if (millis() - lastDisplay > 2000) {
    displayStatus(distance);
    lastDisplay = millis();
  }
  
  delay(50);
}

void checkFlame() {
  // قراءة مستشعر اللهب (LOW = حريق)
  bool currentFire = (digitalRead(FLAME_SENSOR) == LOW);
  
  if (currentFire && !fireDetected) {
    fireDetected = true;
    fireDetectedTime = millis();
    Serial.println("\n🔥🔥🔥 تحذير: حريق مكتشف! 🔥🔥🔥");
  }
  
  if (!currentFire && fireDetected) {
    fireDetected = false;
    noTone(BUZZER);
    Serial.println("\n✓ الحريق تم السيطرة عليه\n");
  }
  
  // إنذار الحريق (أولوية قصوى)
  if (fireDetected) {
    // صوت متقطع سريع للحريق
    if (millis() - lastBeep > 150) {
      if (buzzerState) {
        noTone(BUZZER);
      } else {
        tone(BUZZER, 2500); // نغمة عالية جداً
      }
      buzzerState = !buzzerState;
      lastBeep = millis();
    }
    
    // إيقاف بعد 10 ثواني
    if (millis() - fireDetectedTime > FIRE_ALARM_DURATION) {
      fireDetected = false;
      noTone(BUZZER);
      Serial.println("\n⏱ انتهى وقت إنذار الحريق\n");
    }
  }
}

void handleDistanceWarning(float distance) {
  // إذا كان هناك حريق، لا تتعامل مع تحذيرات المسافة
  if (fireDetected) return;
  
  if (distance < 0) {
    // لا يوجد قياس صحيح
    noTone(BUZZER);
    return;
  }
  
  // 🔴 خطر شديد (أقل من 2 سم)
  if (distance < DANGER_DISTANCE) {
    if (millis() - lastBeep > 100) {
      if (buzzerState) {
        noTone(BUZZER);
      } else {
        tone(BUZZER, 2000); // نغمة عالية
      }
      buzzerState = !buzzerState;
      lastBeep = millis();
    }
  }
  // 🟡 تحذير متوسط (2-10 سم)
  else if (distance < WARNING_DISTANCE) {
    if (millis() - lastBeep > 300) {
      if (buzzerState) {
        noTone(BUZZER);
      } else {
        tone(BUZZER, 1500); // نغمة متوسطة
      }
      buzzerState = !buzzerState;
      lastBeep = millis();
    }
  }
  // 🟢 مسافة آمنة
  else {
    noTone(BUZZER);
    buzzerState = false;
  }
}

void autoLight() {
  // قراءة مستشعر الضوء
  int lightLevel = analogRead(LDR_PIN);
  
  // تشغيل LED في الظلام (قراءة منخفضة = ظلام)
  if (lightLevel < DARK_THRESHOLD) {
    if (!autoLightOn) {
      digitalWrite(LED_PIN, HIGH);
      autoLightOn = true;
      Serial.println("💡 تشغيل الإضاءة التلقائية (ظلام)");
    }
  } 
  // إطفاء LED في الضوء
  else {
    if (autoLightOn) {
      digitalWrite(LED_PIN, LOW);
      autoLightOn = false;
      Serial.println("💡 إطفاء الإضاءة التلقائية (ضوء كافي)");
    }
  }
}

float getDistance() {
  // تنظيف TRIG
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(5);
  
  // إرسال نبضة
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // قراءة ECHO مع timeout
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  
  if (duration == 0) {
    return -1; // لا يوجد echo
  }
  
  // حساب المسافة (سرعة الصوت = 340 م/ث)
  float distance = (duration * 0.0343) / 2.0;
  
  return distance;
}

void displayStatus(float distance) {
  Serial.println("\n========== حالة النظام ==========");
  
  // حالة الحريق
  Serial.print("🔥 مستشعر اللهب: ");
  Serial.println(fireDetected ? "[!] حريق مكتشف!" : "[✓] آمن");
  
  // المسافة والتحذير
  Serial.print("📏 المسافة: ");
  if (distance > 0) {
    Serial.print(distance, 1);
    Serial.print(" سم ");
    
    if (distance < DANGER_DISTANCE) {
      Serial.println("[🔴 خطر شديد!]");
    } else if (distance < WARNING_DISTANCE) {
      Serial.println("[🟡 تحذير]");
    } else {
      Serial.println("[🟢 آمن]");
    }
  } else {
    Serial.println("-- [لا يوجد قياس]");
  }
  
  // الإضاءة
  int lightLevel = analogRead(LDR_PIN);
  Serial.print("💡 مستوى الضوء: ");
  Serial.print(lightLevel);
  Serial.print(" | LED: ");
  Serial.println(autoLightOn ? "[ON ✓]" : "[OFF]");
  
  Serial.println("=====================================\n");
}
