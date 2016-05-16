


//-----AUTRE-----
int Tpin = A1; //température
float Tread;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
printTempc();
delay(1000);
}

float printTempc(){
  analogRead(Tpin);
  delay(200);
  Tread = analogRead(Tpin)*(5.000 / 1023.000); //0.48828125
  Serial.println(Tread);
  return Tread;

}
