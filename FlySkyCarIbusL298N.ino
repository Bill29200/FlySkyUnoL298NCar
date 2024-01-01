#include <IBusBM.h>
IBusBM ibus;


// Read the number of a given channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue) {
  uint16_t ch = ibus.readChannel(channelInput);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

// Read the channel and return a boolean value
bool readSwitch(byte channelInput, bool defaultValue) {
  int intDefaultValue = (defaultValue) ? 100 : 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}


// Motor A

int enA = 9;
int in1 = 8;
int in2 = 7;

// Motor B

int enB = 3;
int in3 = 4;
int in4 = 5;

// leds
int ledWhite = 13;
int ledRed = 12;

//-------------------------------------------------------------------------------
void setup() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  Serial.begin(115200);

  // Attach iBus object to serial port
  ibus.begin(Serial,1);

  pinMode(ledWhite, OUTPUT);
  pinMode(ledRed, OUTPUT);

  digitalWrite(ledWhite, LOW);
  digitalWrite(ledRed, LOW);

}

//-------------------------------------------------------------------------------
void loop() {
 int  rcCH1 = readChannel(0, -100, 100, 0);
int  rcCH2 = readChannel(1, -100, 100, 0 );
int rcCH3 = readChannel(2, 0, 255, 125);

  // Print values to serial monitor for debugging
  Serial.print("Ch1 = ");
  Serial.print(rcCH1);
  Serial.print("   §§   Ch2 = ");
  Serial.print(rcCH2);
 
  Serial.print("   §§   Ch3 = ");
  Serial.println(rcCH3);


  int speed = rcCH3;
  
  if (rcCH1 > 50) 
  {
     // ,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,right
     Serial.print("right  speed : "); 
     // Turn on motor A
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);          
        analogWrite(enA, speed);
     // Turn on motor B
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        analogWrite(enB, speed);  

        digitalWrite(ledWhite, LOW);
        digitalWrite(ledRed, LOW);
     
  }
  else  if (rcCH1 < -50) 
  {
   // ,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,left
    Serial.print("left  speed : "); 
    // Turn on motor A
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);          
        analogWrite(enA, speed);
     // Turn on motor B
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        analogWrite(enB, speed); 
        
        digitalWrite(ledWhite, LOW);
        digitalWrite(ledRed, LOW);
  }
  else if (rcCH2 > 50) 
  {
      //,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,, direct
     Serial.println("--> direct  speed : "); 
     // Turn on motor A
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);          
        analogWrite(enA, speed);
     // Turn on motor B
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        analogWrite(enB, speed);  

        digitalWrite(ledWhite, HIGH);
        digitalWrite(ledRed, LOW);
     
  }
  else  if (rcCH2 < -50) 
  {
     //,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,, reverse
     Serial.print("reverse  speed : "); 
     // Turn on motor A
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);          
        analogWrite(enA, speed);
     // Turn on motor B
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        analogWrite(enB, speed); 

        digitalWrite(ledWhite, LOW);
        digitalWrite(ledRed, HIGH);
  }
  else 
  {
    
    // ,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,stop
    Serial.print("stop  speed : "); 
    // Turn on motor A
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);          
        analogWrite(enA, speed);
     // Turn on motor B
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        analogWrite(enB, speed); 
       
       digitalWrite(ledWhite, LOW);
       digitalWrite(ledRed, LOW);
       
  }
  Serial.println( speed);
  
 
 
 delay(3);
 
 

}
