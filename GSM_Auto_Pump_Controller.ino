#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
#define BUZ 13
#define LCTR 2

int A, B, C, D, E, LEV;

void setup() {
  Serial.begin(9600);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(BUZ, OUTPUT);
  pinMode(LCTR, OUTPUT);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print(" GSM BASED AUTO ");
  lcd.setCursor(0, 1);
  lcd.print(" PUMP CONTROLLER ");
  delay(3000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" SUBMITTED BY: ");
  delay(1500);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" TORIQUL ISLAM ");
  delay(1000);

  // Buzzer tone
  digitalWrite(BUZ, LOW);
  delay(60);
  digitalWrite(BUZ, HIGH);
  delay(60);
  digitalWrite(BUZ, LOW);
  delay(60);
  digitalWrite(BUZ, HIGH);
  delay(60);
  digitalWrite(BUZ, LOW);
  delay(600);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" System Ready.. ");
  SendMessage1();
}

void loop() {
  E = digitalRead(A1);
  D = digitalRead(A2);
  C = digitalRead(A3);
  B = digitalRead(A4);
  A = digitalRead(A5);

  DISPLAY1();

  if (Serial.find("#A.")) {
    digitalWrite(BUZ, HIGH);
    delay(100);
    digitalWrite(BUZ, LOW);
    SendMessage4();
  }

  delay(500);
}

void DISPLAY1() {
  lcd.setCursor(0, 0);
  lcd.print("LEVEL:");
  lcd.print(LEV);
  lcd.print("%  ");

  if (A == 1) {
    LEV = 0;
    digitalWrite(LCTR, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("MOTOR:ON   ");
    SendMessage2();
  } else if (E == 0) {
    LEV = 100;
    digitalWrite(LCTR, LOW);
    lcd.setCursor(0, 1);
    lcd.print("MOTOR:OFF  ");
    SendMessage3();
  } else if (D == 0) {
    LEV = 80;
  } else if (C == 0) {
    LEV = 60;
  } else if (B == 0) {
    LEV = 40;
  } else if (A == 0) {
    LEV = 20;
  }
}

// GSM Message Functions
void SendMessage1() {
  Serial.println("AT+CMGS="+8801960682324"\r");
  Serial.println("SYSTEM READY");
}

void SendMessage2() {
  Serial.println("AT+CMGS="+8801960682324"\r");
  Serial.println("WATER LEVEL < 10%. MOTOR ON");
}

void SendMessage3() {
  Serial.println("AT+CMGS="+8801960682324"\r");
  Serial.println("WATER LEVEL 100%. MOTOR OFF");
}

void SendMessage4() {
  Serial.println("AT+CMGS="+8801960682324"\r");
  Serial.print("WATER LEVEL: ");
  Serial.println(LEV);
}
