int value; 
int light;

unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 2000; 
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;

 
void setup()   
{ 
Serial.begin(57600);
}  
void loop() 
{ 
value= analogRead(0);
//Serial.print("CO value: "); 
//Serial.println(value, DEC);
//Serial.println(",");


//light code
light=analogRead(A1);
//Serial.print("Light value: "); 
//Serial.println(String(light));
String myString1=String(value);
String myString2=String(light);


//Dust Code
duration = pulseIn(6, LOW);
  lowpulseoccupancy = lowpulseoccupancy+duration;
  if ((millis()-starttime) >= sampletime_ms) //if the sampel time = = 30s
  {
    ratio = lowpulseoccupancy/(sampletime_ms*10.0);  
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; 
    String myString3=String(concentration);  
    String myString=myString1+" "+myString2+" "+myString3;
    Serial.println(myString);
    lowpulseoccupancy = 0;
    starttime = millis();
  }

delay(30000); 
} 
