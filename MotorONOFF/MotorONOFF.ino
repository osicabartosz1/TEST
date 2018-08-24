const int Wire13 = 13;     
const int Wire12 = 12;     

bool rigth=true;
void setup() {
    Serial.begin(9600);
    pinMode(Wire13, OUTPUT);
    pinMode(Wire12, OUTPUT);

}

void loop() {
     delay(1000);

      if(rigth){
        digitalWrite(Wire13, LOW);
        digitalWrite(Wire12, LOW);

        rigth=false;
        Serial.println("False");
      }
      else{
        digitalWrite(Wire13, HIGH);
        digitalWrite(Wire12, HIGH);

         rigth=true;
         Serial.println("True");
        }
}
