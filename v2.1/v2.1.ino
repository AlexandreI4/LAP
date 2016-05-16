//------TIME-----
//ne pas oublier de les intégrer dans l'IDE
#include<TimeLib.h>
//#include<time.h>
//-------LCD-------------
//supprimer tous les fichiers liquidcrystal de l'ordi
//importer NewLiquidCrystal
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C  lcd(0x3f,2,1,0,4,5,6,7); //initialisation lcd

//-----LCD-----
//SDA = A4
//SCL = A5

//-----int time-----
int h;
int m;
int s;

//-----CAPTEURS-----
int Lpin = A0; //light
int Tpin = A1; //température
int thermoPin = 2; //r
int lightPin = 3; //j
int agitatePin = 4; //v 

//-----AUTRE-----
int waterPin1 = A2;
int waterOK1 = 5;
int waterPin2 = A3;
int waterOK2 = 6;
int rPin = 7; //choix moteur
int buzzPin = 8;



//-----VARIABLES-----
float Lread;
float Tread;
float temps;
int wLevel1 = 0;
int wLevel2 = 0;
boolean dState=false;


void setup() {
  
  //Serial.begin(115200); //nb paquets
  
  //-----SET TIME-----
  setTime(20,49,00,0,0,0); // regler heure (hh,mm,ss,jj,mm,aaaa)
  
  //-----PIN MODE-----
  pinMode(thermoPin,OUTPUT);
  pinMode(lightPin,OUTPUT);
  pinMode(agitatePin,OUTPUT);
  pinMode(buzzPin,OUTPUT);
  pinMode(rPin,OUTPUT);
  pinMode(waterOK1,OUTPUT);
  pinMode(waterOK2,OUTPUT);
  tone(buzzPin,2000,50); //(pin, frequence, durée ms)
  
  //-------------LCD------------
  lcd.begin (20,4);
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home(); //set cursor (0,0)
  lcd.print("LAP-TEAM");
}



void loop() {
h=hour();
m=minute();
s=second();
printTime();
printTempc();
printLum();
dayState();
thermo();
alert();
light();
water();
agitation();
testR();
//timeSerial();
delay(980);
//lcd.clear(); //effacer lcd
}

float testR (){
  digitalWrite(rPin, HIGH);
  delay(50);
  digitalWrite(rPin,LOW);
}
float dayState (){
  if (h<18 && h>6){
    dState=true; 
    lcd.setCursor(10,1);
    lcd.print("DAY  ");
  }
  else { 
    dState=false;
    lcd.setCursor(10,1);
    lcd.print("NIGHT ");
  }
}


float printTempc(){
  analogRead(Tpin);
  delay(20);
  Tread = (analogRead(Tpin)*500.0/1024.0);
  //Serial.print("Temperature: ");
  lcd.setCursor(0,2);
  lcd.print("Temp: ");
  lcd.print(Tread,1); //nb décimales = 1 lcd.print(Tread,1);
  lcd.print((char)223);//générer "°" degré
  lcd.print("C");
  lcd.print(" ");
  lcd.setCursor(0,3);
  //Serial.print(Tread); //PYTHON
  //Serial.print(" , "); //PYTHON
  //Serial.println(" C");
  return Tread;
}


float printLum(){
  Lread = analogRead(Lpin);
  //Serial.print("Luminosite: ");
  lcd.setCursor(0,1);
  lcd.print("Lum: ");
  lcd.print(Lread,0); //nb décimales = 0
  //Serial.println(Lread); //PYTHON
  return Lread;
}


float printTime(){
  //Serial.print(h);
  //Serial.print(":");
  //Serial.print(m);
  //Serial.print(":");
  //Serial.print(s);
  //Serial.print(" , ");
  lcd.setCursor(12,0);
  if (h<=9){
    lcd.print("0");
    lcd.print(h);
  }
  else{
  lcd.print(h);
  }
  lcd.print(":");
  if (m<=9){
    lcd.print("0");
    lcd.print(m);
  }
  else{
    lcd.print(m);
  }
  lcd.print(":");
  if (s<=9){
    lcd.print("0");
    lcd.print(s);
  }
  else{
    lcd.print(s);
  }
}


float thermo(){
   if (Tread <= 28){
     digitalWrite(thermoPin,HIGH);
     lcd.setCursor(14,2);
     lcd.print("T=ON");
     lcd.print(" ");
   }
   else {
      digitalWrite(thermoPin,LOW);
      lcd.setCursor(14,2);
      lcd.print("T=OFF");
   }
}


float light(){
    if (Lread <= 700 && dState==true){ //il faudra placer le capteur de luminosité en direction inverse de la phytotière
      digitalWrite(lightPin,HIGH);
    }
    if (dState==false) {
      if (m>0 && m<=30) {
        digitalWrite(lightPin,HIGH);
      }
      else {
        digitalWrite(lightPin,LOW);
      }
    }
}

    
float alert(){
  if (Tread <=10) { //change to 20
    tone(buzzPin,1000,100);
  }
}


float water(){
  wLevel1 = analogRead(waterPin1);
  lcd.setCursor(0,3);
  lcd.print("W1:");
  lcd.print(wLevel1); //gérer affichage
  lcd.print(" ");
  if (wLevel1 <= 200){
    digitalWrite(waterOK1,LOW); 
  }
  if (wLevel1 >= 425){
    digitalWrite(waterOK1,HIGH);
  }

    wLevel2 = analogRead(waterPin2);
  lcd.setCursor(7,3);
  lcd.print("W2:");
  lcd.print(wLevel2); //gérer affichage
  lcd.print(" ");
  if (wLevel2 <= 200){
    digitalWrite(waterOK2,LOW); 
  }
  if (wLevel2 >= 425){
    digitalWrite(waterOK2,HIGH);
  }
}


float agitation(){
  if (m>0 && m<=30){
    digitalWrite(agitatePin,HIGH);
  }
  else {
    digitalWrite(agitatePin,LOW);
  }
}



