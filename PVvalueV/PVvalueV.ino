const int test = 20;     
bool rigth=true;


void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(test, OUTPUT);

}

void loop() {
  Serial.println((float(analogRead(A0)*5)/1024*float(analogRead(A0)*5)/1024)*1000);
  delay(1000);        // delay in between reads for stability
        if(rigth){
        digitalWrite(test, LOW);
        rigth=false;
        Serial.println("False");
      }
      else{
        digitalWrite(test, HIGH);
         rigth=true;
         Serial.println("True");
     }
}
