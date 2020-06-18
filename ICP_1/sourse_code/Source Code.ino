int switchState = 0;
void setup() {
  pinMode(3, OUTPUT);//yelow
  pinMode(4, OUTPUT);//red
  pinMode(6, OUTPUT); //green
  pinMode(2,INPUT); 
}

void loop(){
 switchState = digitalRead(2);
 if(switchState ==LOW){
  
  digitalWrite(3, LOW); //yellow LED
  digitalWrite(4, LOW); //Red LED
  digitalWrite(6, LOW); //green LED
  delay(500);
  }
 

  else{
  digitalWrite(3,LOW);
  digitalWrite(4, HIGH);
  digitalWrite(6,LOW);

  delay(2000); // wait for a quarter seconds
  digitalWrite(3,HIGH);
  digitalWrite(4,LOW);
  digitalWrite(6, LOW);
  delay(1000);
   digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(6,HIGH);
  delay(1500);
  }

}
