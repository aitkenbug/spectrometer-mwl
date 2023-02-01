#include <Adafruit_AS7341.h>

Adafruit_AS7341 as7341;

bool msg = false;

void setup(){
  Serial.begin(115200);

  if (!as7341.begin()){
    Serial.println("No AS7341 found");
    while (1) {delay(10);}
  }
  as7341.setATIME(358);
  as7341.setASTEP(999);
  as7341.setGain(AS7341_GAIN_4X);
  
  pinMode(5, OUTPUT);
}


void loop() {
  if (Serial.available()){
    char c = Serial.read();
    if (c == 'm'){
      msg = true;
      digitalWrite(5, HIGH);
      while (msg) {
        measure();
        c = Serial.read();
        if (c == 's'){
          msg = false;
          digitalWrite(5, LOW);
        }
      }
    }
  }
}

void measure(){
  uint16_t readings[12];

  if (!as7341.readAllChannels(readings)){
    Serial.println("Failed to read all channels");
    return;
  }
  Serial.print(readings[0]); //ADC0/F1 415nm
  Serial.print(", ");
  Serial.print(readings[1]); //ADC1/F2 445nm
  Serial.print(", ");
  Serial.print(readings[2]); //ADC2/F3 480nm
  Serial.print(", ");
  Serial.print(readings[3]); //ADC3/F4 515nm
  Serial.print(", ");
  Serial.print(readings[6]); //ADC0/F5 555nm
  Serial.print(", ");
  Serial.print(readings[7]); //ADC1/F6 590nm
  Serial.print(", ");
  Serial.print(readings[8]); //ADC2/F7 630nm
  Serial.print(", ");
  Serial.print(readings[9]); //ADC3/F8 680nm
  Serial.print(", ");
  Serial.print(readings[10]);//ADC4/Clear
  Serial.print(", ");
  Serial.print(readings[11]);//ADC5/NIR
  Serial.println(); //Newline for new data
}
