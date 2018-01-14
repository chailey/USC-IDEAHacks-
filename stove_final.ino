#include <Servo.h>
#include <Servo.h>
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

//Mario main theme melody
int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};

const int ulsonicPin = 4;
const int melodyPin = 8; 
const int buttonPin = 2; 
const int cameraPin = 3; 
const int redLEDPin = 5;
const int greenLEDPin = 6;
const int blueLEDPin = 7; 
const int notifyLEDPin = 10; 
volatile int state = 0; 

//Servo myservo;
//int pos = 0;

//variables needed to store values
long pulse, inches, cm;

void(* resetFunc) (void) = 0; //declare reset function @ address 0

void setup()

{
  //This opens up a serial connection to shoot the results back to the PC console
  Serial.begin(9600);
  pinMode(melodyPin, OUTPUT);//buzzer
  pinMode(ulsonicPin, INPUT);
  pinMode(buttonPin, INPUT); 
  pinMode(cameraPin, INPUT); 
  pinMode(notifyLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT); 
  attachInterrupt(digitalPinToInterrupt(buttonPin), resetFunc, HIGH);

  //myservo.attach(9);
}



void loop()
{
  
  //Used to read in the pulse that is being sent by the MaxSonar device.
  //Pulse Width representation with a scale factor of 147 uS per Inch.
  pulse = pulseIn(ulsonicPin, HIGH);
  //147uS per inch
  inches = pulse / 147;

  Serial.print(digitalRead(buttonPin)); 

  //Serial.print(inches);
 // Serial.print("in, ");
  //Serial.println();

    if (state == 0)
  {
    if(!digitalRead(cameraPin))
      flicker();
    else {
      digitalWrite(notifyLEDPin, LOW); 
    }
     changeColors(0); 
     if (inches <= 7)
     {
        state = 2; 
     }
     else if (inches <= 12)
     {
        state = 1;  
     }
     //myservo.write(0);
  }
  else if (state == 1)
  {
    if(!digitalRead(cameraPin))
      flicker();
    else {
      digitalWrite(notifyLEDPin, LOW); 
    } 
    changeColors(1); 
    if (inches <= 7)
    {
      state = 2; 
    }
    else if (inches > 7 && inches <= 12)
    {
      state = 1; 
    }
    else
    {
      state = 0; 
    }
    
  }
  else if (state == 2)
  {
    digitalWrite(notifyLEDPin, LOW); 
    changeColors(2); 
    alarm(); 
    Serial.println(digitalRead(buttonPin)); 
    //if (digitalRead(buttonPin) == LOW)
    //{
     
    //}
    
    //myservo.write(180);
  }
  //delay(50);
  ///Serial.print(state); 

}
void changeColors(int state)
{
  if (state == 0) 
  {
     analogWrite(redLEDPin, 0);
     analogWrite(greenLEDPin, 0); 
     analogWrite(blueLEDPin, 0);     
  }
  else if (state == 1)
  {
    analogWrite(redLEDPin, 100);
    analogWrite(greenLEDPin, 230);
    analogWrite(blueLEDPin, 50);
    delay(50);
    analogWrite(redLEDPin,  250);
    analogWrite(greenLEDPin, 255);
    analogWrite(blueLEDPin, 51);
    delay(50);
         
  }
  else if (state == 2)
  {
    analogWrite(redLEDPin, 0);
    analogWrite(greenLEDPin, 255); 
    analogWrite(blueLEDPin, 0);
  }
}

void flicker()
{
    digitalWrite(notifyLEDPin, HIGH); 
    delay(10);
    digitalWrite(notifyLEDPin, LOW);
    delay(10);     
}

void alarm()
{
    Serial.println(" 'Mario Theme'");
    int size = sizeof(melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo[thisNote];

      buzz(melodyPin, melody[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.0;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);
}
}

void buzz(int targetPin, long frequency, long length) {
  digitalWrite(melodyPin, HIGH);
  long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to
  //// get the total number of cycles to produce
  for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
    digitalWrite(targetPin, HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin, LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
  digitalWrite(melodyPin, LOW);

}
  

