
#include <dht.h>
#include <LiquidCrystal_I2C.h>
//LCD display is defined as device number 0x27 on the I2C bus
LiquidCrystal_I2C lcd(0x27, 20, 4);
//DHT11 is connected to pin 8
dht DHT;
#define sensorPin 8
//Raspberry Pi is connected to Serial 0
#define serialPi Serial
void setup() {
  lcd.begin(20, 4); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
  lcd.init();
  lcd.backlight();
  serialPi.begin(9600);  //Arduino to serial monitor
}
void loop() {
  //Read sensor data
  int sensorData = DHT.read11(sensorPin);
  float temperature = DHT.temperature;
  float humidity = DHT.humidity;
  //Print temperature
  lcd.setCursor(0, 0);
  lcd.print("Temperature ");
  lcd.print(temperature);
  lcd.print(" C");
  //Print humidity
  lcd.setCursor(0, 1);
  lcd.print("Humidity    ");
  lcd.print(humidity);
  lcd.print(" %");
  //Send temperature and humidity data to Raspberry Pi
  serialPi.print("<");
  serialPi.print(temperature);
  serialPi.print(",");
  serialPi.print(humidity);
  serialPi.println(">");
  //Wait for 10 seconds
  delay(10000);
}
