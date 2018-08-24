const int Wire13 = 13;     
const int Wire12 =  12;      
const int Wire11 =  11;      
const int Wire10 =  10;      


const int whiteWire = 2;     
const int violetWire =  0;     
const int orangeWire = 1;     

int orangeWireState;
int violetWireState;
int whiteWireState;

bool rigth=true;
void setup() {
    Serial.begin(9600);
    pinMode(Wire13, OUTPUT);
    pinMode(Wire12, OUTPUT);
    pinMode(Wire11, OUTPUT);
    pinMode(Wire10, OUTPUT);

        digitalWrite(Wire13, HIGH);
        digitalWrite(Wire12, HIGH);
        digitalWrite(Wire11, HIGH);
        digitalWrite(Wire10, HIGH);


    pinMode(whiteWire, INPUT);
    pinMode(orangeWire, INPUT);
    pinMode(violetWire, INPUT);

    
}

void loop() {
     delay(1000);
      orangeWireState = digitalRead(orangeWire);
      violetWireState = digitalRead(violetWire);
      whiteWireState = digitalRead(whiteWire);
      String message="";
      if(whiteWireState){message+="Prawo";}
      if(violetWireState){message+="Lewo";}
      if(orangeWireState){message+=" lekko";}
      if(message==""){message="Prosto";}
      if(rigth){
        digitalWrite(Wire13, LOW);
        digitalWrite(Wire12, HIGH);
        digitalWrite(Wire11, HIGH);
        digitalWrite(Wire10, LOW);
      rigth=false;
      }
      else{
        digitalWrite(Wire13, HIGH);
        digitalWrite(Wire12, LOW);
        digitalWrite(Wire11, LOW);
        digitalWrite(Wire10, HIGH);
         rigth=true;

        }
      
      Serial.println(message);

}
