//infinite Xpro
// firstly need to add i2c library 
//thingspeak code
#include <SoftwareSerial.h>
#include <dht11.h>
#define RX 2
#define TX 3
#define dht_apin 11 // Analog Pin sensor is connected to
dht11 dhtObject;
String AP = "KingsVirus";       // AP NAME
String PASS = "ThreeoSix"; // AP PASSWORD
String API = "A82M4Y3OUJAOKXRQ";   // Write API KEY
String HOST = "api.thingspeak.com";
String PORT = "80";
int countTrueCommand;
int countTimeCommand; 
boolean found = false; 
int valSensor = 1;
SoftwareSerial esp8266(RX,TX);   
//thingspeak code close

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display 
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
int gate=11; 
volatile unsigned long duration=0;
unsigned char i[5];
unsigned int j[40];
unsigned char value=0;
unsigned answer=0;
int z=0;
int b=1;
int buzzer=9;
int ledGreen = 8;
int ledRed = 7;
int sensorValue;

void setup() 
{
 lcd.init();                       // initialize the lcd
 lcd.init();
 lcd.backlight(); 
// lcd.print("Temp = ");
// lcd.setCursor(0,1);
// lcd.print("Humidity = ");
// lcd.createChar(1, degree_symbol);
// lcd.setCursor(9,0);
// lcd.write(1);
// lcd.print("C");
// lcd.setCursor(13,1);
// lcd.print("%");
// pinMode(buzzer, OUTPUT);  
// pinMode(ledRed, OUTPUT); 
// pinMode(ledGreen, OUTPUT); 

 //thingspeak code
 Serial.begin(9600);
  esp8266.begin(115200);
  sendCommand("AT",5,"OK");
  sendCommand("AT+CWMODE=1",5,"OK");
  sendCommand("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",20,"OK");
 //thingspeak code close
 
}

void loop() 
{

 delay(1000);
 while(1)
 {
  delay(1000);
  pinMode(gate,OUTPUT);
  digitalWrite(gate,LOW);
  delay(20);
  digitalWrite(gate,HIGH);
  pinMode(gate,INPUT_PULLUP);//by default it will become high due to internal pull up
 // delayMicroseconds(40);

  
  duration=pulseIn(gate, LOW);
  if(duration <= 84 && duration >= 72)
  {
      while(1)
      {
        duration=pulseIn(gate, HIGH);
        
        if(duration <= 26 && duration >= 20){
        value=0;}
        
        else if(duration <= 74 && duration >= 65){
        value=1;}
        
        else if(z==40){
        break;}
        
        i[z/8]|=value<<(7- (z%8));
        j[z]=value;
        z++;
      }
    }
answer=i[0]+i[1]+i[2]+i[3];

if(answer==i[4] && answer!=0)
{
sensorValue = analogRead(0);  
Serial.print(sensorValue, DEC);
lcd.setCursor(0,0);
lcd.print("T=");
lcd.print(i[2]);
lcd.print(" H=");
lcd.print(i[0]);
lcd.print(" AQ=");
lcd.print(sensorValue);
lcd.setCursor(0,1);
lcd.print("Test")
//thingspeak code 
String getData = "GET /update?api_key="+ API +"&field1="+i[2]+"&field2="+i[0]+"&field3="+sensorValue;
 sendCommand("AT+CIPMUX=1",5,"OK");
 sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");
 sendCommand("AT+CIPSEND=0," +String(getData.length()+4),4,">");
 esp8266.println(getData);delay(1500);countTrueCommand++;
 sendCommand("AT+CIPCLOSE=0",5,"OK");
//thingspeak code close

}

z=0;
i[0]=i[1]=i[2]=i[3]=i[4]=0;
 }
}

void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  {
    esp8266.println(command);//at+cipsend
    if(esp8266.find(readReplay))//ok
    {
      found = true;
      break;
    }
  
    countTimeCommand++;
  }
  
  if(found == true)
  {
    Serial.println("OYI");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  
  if(found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  
  found = false;
 }
