// defines pins numbers
const int trigPin = 11;
const int echoPin = 12;

// defines variables
long duration;
int distance;
int buzzar = 10;
int ledGreen = 9;

//LCD
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
byte degree_symbol[8] = 
              {
                0b00111,
                0b00101,
                0b00111,
                0b00000,
                0b00000,
                0b00000,
                0b00000,
                0b00000
              };

void setup() 
{
lcd.init();                       // initialize the lcd
lcd.backlight(); 
pinMode(buzzar,OUTPUT);
pinMode(ledGreen, OUTPUT);

pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
lcd.setCursor(0,0);
lcd.print("Distance = ");
Serial.begin(9600); // Starts the serial communication


}
void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in
delayMicroseconds;
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
if(distance >=20)
{
    digitalWrite(buzzar,LOW);
    digitalWrite(ledGreen,HIGH);
    
}
else
{
    digitalWrite(buzzar,HIGH);
    digitalWrite(ledGreen,LOW);
    
}
// Prints the distance on the Serial Monitor
//Serial.print("Distance: ");
Serial.println(distance); 
//Serial.write(distance);


lcd.setCursor(0,0);
lcd.print("Distance: ");
lcd.print(distance);
lcd.setCursor(0,1);
if(distance <=20)
{
  lcd.print("Very Close");
}
delay(500);

lcd.clear();
}
