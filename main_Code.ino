#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <LiquidCrystal.h>         //Add this library to initialize LCD

//Constants
#define DHTPIN 7                  // what pin we're connected to
#define DHTTYPE DHT22            // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE);        // Initialize DHT sensor for normal 16mhz Arduino
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7); //initialize pins for LCD

//Variables
int chk;
float humidity;             //Stores humidity value
float temperature;         //Stores temperature value
const int speakerpin = 8; // digital pin on the Arduino that the positive lead of speaker is attached.


void setup()
{
  lcd.begin(16,2);
  Serial.begin(9600);
  dht.begin();
  pinMode(LED_BUILTIN, OUTPUT);                     // initialize digital pin LED_BUILTIN as an output.
  pinMode(speakerpin,OUTPUT);                       // pin 8 is set as output.
  lcd.print("hello, world!");                       // Print a message to the LCD.
  lcd.clear();
  Serial.println("Humidity,Temp");
}

void loop()
{
    //Read data and store it to variables humidity and temperature
    humidity = dht.readHumidity();
    temperature= dht.readTemperature();
    
    if(humidity > 50)
     {
       digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on
       delay(1000);                       // wait for 1sec
       digitalWrite(LED_BUILTIN, LOW);    // turn the LED off
       delay(100);
     }
    else
     {
       digitalWrite(LED_BUILTIN, LOW);    // turn the LED off
     }

     if(humidity > 50)
     {
      tone(speakerpin, 1000, 500);    //tone(pin,freq(1KHz),duration(500msec))
      delay(500);
      noTone(speakerpin);
      delay(500);
     }
     else
     {
      noTone(speakerpin);
     }
  
    //Print temperature and humidity values to serial monitor
    //Serial.print("Humidity: ");
    Serial.print(humidity);
    //Serial.print(" %, Temp: ");
    Serial.print(",");
    Serial.println(temperature);
    //Serial.println(" Celsius");
    
    lcd.display(); // Turn on the display:
    //Print temperature and humidity value on 16X2 LCD
    lcd.setCursor(0,0);                                //top left     
    lcd.print(temperature);
    lcd.print(" C");
    lcd.setCursor(0,1);                               //bottom left     
    lcd.print(humidity);
    lcd.print(" percent");
    delay(1000);                                     //Delay 2 sec.
}
/*
void dht22sensor(float humidity)
{
  float hum;
  if(hum > 50)
  {
    for(int i = 0; i<5; i++){ 
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on
      delay(1000);                       // wait for 1sec
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off
      delay(100);
    }
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off
  }
}

void speaker(float humidity)
{
  float humidityValue;
  if(humidityValue > 50){
     //for(int i = 0; i<5; i++){
      tone(speakerpin, 1000, 500);    //tone(pin,freq(1KHz),duration(500msec))
      delay(500);
      noTone(speakerpin);
      delay(500);
    // }
  }
  else{
    noTone(speakerpin);
  }
}
*/
