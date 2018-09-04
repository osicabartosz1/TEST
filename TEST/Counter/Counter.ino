int Wire6=6;
int counter=0;
bool rigth=false;
void setup() {
  // put your setup code here, to run once:
      Serial.begin(9600);
          pinMode(6, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
     delay(1000);

      if(rigth){
        digitalWrite(Wire6, LOW);

        rigth=false;
        Serial.println("False");
      }
      else{
        digitalWrite(Wire6, HIGH);
         rigth=true;
         Serial.println("True");
        }
}

