#include <LiquidCrystal.h>
const int rs = 3, en = 4, d4 = A2, d5 = A3, d6 = A4, d7 = A5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  Serial.begin(9600);
  Serial.println("initializing setup...");
  lcd.begin(16, 2);
  lcd.clear();
}
void loop() {
  lcd.setCursor(0, 0);
  lcd.print("HELLO");
  lcd.setCursor(0, 1);
  lcd.print("WORLD");
  while(1);
}