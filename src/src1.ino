#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define SENSOR A0
#define LED 13
#define BUZZER 9

void setup() 
{
    Serial.begin(9600);
    lcd.begin(16, 2);
    lcd.print(" ALCOHOL DETECTOR");
    lcd.setCursor(0, 1);
    delay(2000);
    pinMode(SENSOR, INPUT);
    pinMode(BUZZER, OUTPUT);
    pinMode(LED, OUTPUT);
    lcd.clear();
}

void loop() {
    float adcValue = 0;
    for (int i = 0; i < 10; i++) {
        adcValue += analogRead(SENSOR);
        delay(10);
    }

    float v = (adcValue / 10) * (5.0 / 1024.0);
    float mgL = 0.67 * v;
    
    Serial.print("BAC: ");
    Serial.print(mgL, 4);
    Serial.println(" mg/L");

    lcd.setCursor(0, 0);
    lcd.print("BAC: ");
    lcd.print(mgL, 4);
    lcd.print(" mg/L    ");
    lcd.setCursor(0, 1);

    if (mgL > 0.8) 
    {
        lcd.print("Drunk  ");
        Serial.println("  Drunk");
        digitalWrite(BUZZER, HIGH);
        digitalWrite(LED, HIGH);
    } 
    
    else 
    {
        lcd.print("Normal  ");
        Serial.println("  Normal");
        digitalWrite(BUZZER, LOW);
        digitalWrite(LED, LOW);
    }

    delay(100);
}
