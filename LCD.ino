#include <Wire.h> 
#include "LiquidCrystal_I2C.h"

int press_time;
int ledpin=7;
unsigned long now_time;
unsigned long start_time;
unsigned long interpress_time;

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
    lcd.init();                     
    lcd.backlight();
    pinMode(ledpin, INPUT);
    press_time=0;
    Serial.begin(9600);
    start_time = millis();
}

void sayThanks()
{
    lcd.setCursor(4,0); // go to start of 2nd line
    lcd.print("Thank you");
    delay(5000);
    lcd.clear();
    
}

void saySorry()
{
    lcd.setCursor(1,0); // go to start of 2nd line
    lcd.print("I am so sorry!");
    delay(5000);
    lcd.clear();
}

void sayFuck()
{
    lcd.setCursor(0,0); // go to start of 2nd line
    lcd.print("Hi you:");
    lcd.setCursor(0,1); // go to start of 2nd line
    lcd.print("Go to hell!");
    delay(5000);
    lcd.clear();
}

void showNumber()
{
    lcd.setCursor(8,0); // go to start of 2nd line
    lcd.print(press_time);
}

void loop()
{
  now_time = millis();
  interpress_time = now_time - start_time;
  if(interpress_time < 20000)
  {
    //waiting for the input
    if (digitalRead(7)==HIGH)
    {
      delay(2000);
      press_time+=1;
      Serial.println(press_time);
      showNumber();
      delay(3000);
    }

    if (press_time>3)
    {
      press_time=0;
    }
    
  }

  if(interpress_time > 20000)
  {
    lcd.clear();
    if(press_time==1)
    {
      sayThanks();
    }

    if(press_time==2)
    {
      saySorry();
    }

    if(press_time==3)
    {
      sayFuck();
    }
    start_time = millis();
    press_time=0;
  }
}
