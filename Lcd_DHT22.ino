#include <Adafruit_Sensor.h>
//DHT22 and 16X2 LCD
#include <DHT.h>
#include <LiquidCrystal.h>         //Add this library to initialize LCD

//Constants
#define DHTPIN 7     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino
LiquidCrystal lcd(12,11,10,5,4,3,2); //initialize pins for LCD

//Variables
int chk;
float humidity;  //Stores humidity value
float temperature; //Stores temperature value

void setup()
{
  lcd.begin(16,2);
  Serial.begin(9600);
  dht.begin();
  pinMode(LED_BUILTIN, OUTPUT); // initialize digital pin LED_BUILTIN as an output.
}

void loop()
{
    delay(2000);
    //Read data and store it to variables humidity and temperature
    humidity = dht.readHumidity();
    temperature= dht.readTemperature();
    dht22sensor(humidity); //calling function
    //Print temperature and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %, Temp: ");
    Serial.print(temperature);
    Serial.println(" Celsius");
    //Print temperature and humidity value on 16X2 LCD
    lcd.setCursor(0,0);      //top left     
    lcd.print(temperature);
    lcd.print(" C");
    lcd.setCursor(0,1);      //bottom left     
    lcd.print(humidity);
    lcd.print(" per");
    delay(10000); //Delay 2 sec.
}

void dht22sensor(float humidity)
{
  float hum;
  if(hum > 50)
  {
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on
      delay(1000);                       // wait for a second
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off
      delay(1000);                       // wait for a second
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off
  }
}
