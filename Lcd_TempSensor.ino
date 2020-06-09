//temperature sensor MCP9700 and 16X2 LCD
const int mcp9700Vout=0;
#include <LiquidCrystal.h>         //Add this library to initialize LCD
LiquidCrystal lcd(12,11,10,5,4,3,2); //initialize pins for LCD
const byte degreeSymbol="B11011111";  //used to display degree sign on LCD
void setup() 
{
    lcd.begin(16,2);
    Serial.begin(9600);
}

void loop() 
{
    long degree;
    degree=mcp9700(mcp9700Vout);
    Serial.print("degrees Celsius = ");
    Serial.print(degree);
    Serial.println("c");
    lcd.setCursor(0,0);           
    lcd.print(degree,DEC);
    lcd.print(degreeSymbol);
    lcd.print("C");
    delay(1000);
}
long mcp9700(int mcp9700Vout)
{
  int value;
  long degree;
  value=analogRead(mcp9700Vout);     
  degree=(long)value*500/1024;
  return degree;
}
/*/////////////////////////////////
          LCD
//////////////////////////////////*/
