#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

const int Wire13 = 13;     
const int Wire12 =  12;      
const int Wire11 =  11;      
const int Wire10 =  10;   

int input_pin = 10; // wpisujemy nazwę pinu, po którym nastepuje komunikacja
IRrecv irrecv(Wire10);
decode_results signals;

   

void setup()
{
    Serial.begin(9600);
    irrecv.enableIRIn(); // włączenie odbierania danych
    
    pinMode(Wire13, OUTPUT);
    pinMode(Wire12, OUTPUT);
    pinMode(Wire11, OUTPUT);


    digitalWrite(Wire13, HIGH);
    digitalWrite(Wire12, HIGH);
    digitalWrite(Wire11, HIGH);
    
}
 
void loop() {
if (irrecv.decode(&signals)) {
       // Serial.println(signals.decode_type); // typ nadajnika
       // Serial.print(F("wynik = 0x"));
       // Serial.println(signals.value, HEX); // wynik w systemie szesnatkowym
       // Serial.println(signals.bits); // ilość przesłanych danych
        irrecv.blink13(true); // mrugamy diodami w arduino
        
        // Przykładowe porównanie:
        //Serial.println("Nic");
        if (signals.value != 0xFFFFFFFF)
        {
          Serial.println(String(signals.value));
        }
        if (signals.value == 0xFFFFFFFF)
        {
          Serial.println("Wcisnieto klawisz Overflow");
        }
        if (signals.value == 0xFF10EF)
        {
          Serial.println("Wcisnieto klawisz lewo");
        }
        if (signals.value == 0xFF18E7)
        {
          Serial.println("Wcisnieto klawisz gora");
        }
        if (signals.value == 0xFF5AA5)
        {
          Serial.println("Wcisnieto klawisz prawo");
        }    
        if (signals.value == 0xFFA25D)
        {
          Serial.println("Wcisnieto klawisz jeden/lewo");
          digitalWrite(Wire13, LOW);
          digitalWrite(Wire12, LOW);
        } 
                if (signals.value == 0xFF629D)
        {
          Serial.println("Wcisnieto klawisz dwa/prosto");
          digitalWrite(Wire13, HIGH);
          digitalWrite(Wire12, HIGH);
          digitalWrite(Wire11, LOW);
        } 
                if (signals.value == 0xFFE21D)
        {
          Serial.println("Wcisnieto klawisz trzy/prawo");
          digitalWrite(Wire13, HIGH);
          digitalWrite(Wire12, LOW);
        } 
                if (signals.value == 0xFF02FD)
        {
          Serial.println("Wcisnieto klawisz piec/stop");
          digitalWrite(Wire13, HIGH);
          digitalWrite(Wire12, HIGH);
          digitalWrite(Wire11, HIGH);
        }     
        
        // ... i tak dalej
        
        irrecv.resume(); // nasłuchujemy na następne nadanie     
    }
}
