

#include <Wire.h>
#include <AccelStepper.h>
#include <Adafruit_MotorShield.h>

#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

int incr = 15, decr = 10, selectedLi = 2;
const int  buttonPin1 = 6;    // the pin that the pushbutton is attached to
const int  buttonPin2 = 4;    // the pin that the pushbutton is attached to
// Variables will change:
int buttonState1 = 0;         // current state of the button
int lastButtonState1 = 0;     // previous state of the button
// Variables will change:
int buttonState2 = 0;         // current state of the button
int chnagecount = 0;
int lastButtonState2 = 0;     // previous state of the button

#define PINLed1 12
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(60, PINLed1, NEO_GRB + NEO_KHZ800);
#define PINLed2 13
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(60, PINLed2, NEO_GRB + NEO_KHZ800);

Adafruit_MotorShield AFMSbot(0x60); // Rightmost jumper closed
Adafruit_MotorShield AFMStop(0x61); // Default address, no jumpers

// Connect two steppers with 200 steps per revolution (1.8 degree)
// to the top shield
Adafruit_StepperMotor *myStepper1 = AFMStop.getStepper(200, 1);
Adafruit_StepperMotor *myStepper2 = AFMStop.getStepper(200, 2);

// Connect one stepper with 200 steps per revolution (1.8 degree)
// to the bottom shield
Adafruit_StepperMotor *myStepper3 = AFMSbot.getStepper(200, 1);

// you can change these to DOUBLE or INTERLEAVE or MICROSTEP!
// wrappers for the first motor!
// you can change these to DOUBLE or INTERLEAVE or MICROSTEP!
// wrappers for the first motor!
void forwardstep1() {
  myStepper1->onestep(FORWARD, DOUBLE);
}
void backwardstep1() {
  myStepper1->onestep(BACKWARD, DOUBLE);
}
// wrappers for the second motor!
void forwardstep2() {
  myStepper2->onestep(FORWARD, DOUBLE);
}
void backwardstep2() {
  myStepper2->onestep(BACKWARD, DOUBLE);
}
// wrappers for the third motor!
void forwardstep3() {
  myStepper3->onestep(FORWARD, DOUBLE);
}
void backwardstep3() {
  myStepper3->onestep(BACKWARD, DOUBLE);
}

// Now we'll wrap the 3 steppers in an AccelStepper object
AccelStepper stepper1(forwardstep1, backwardstep1);
AccelStepper stepper2(forwardstep2, backwardstep2);
AccelStepper stepper3(forwardstep3, backwardstep3);

# include "DFRobot_LedDisplayModule.h"
int Fahrstufen_Schiebepotie[25] = {14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10};

int Display1_Drehzahlen[25] = {1620, 1740, 1860, 1980, 2133, 2000, 1866, 1733, 1600, 1466, 1333, 1200, 1066, 933, 800, 920, 1040, 1160, 1280, 1400, 1520, 1640, 1760, 1880, 2000};
float Display2_KMH[25] = {42, 39, 36, 33, 30, 27, 24, 21, 18, 15, 12, 9, 6, 3, 0, 2.5, 5, 7.5, 10, 12, 15, 17, 20, 22, 25};
float Display3_Einspeisedruck[25] = {0, 21, 21, 24, 24, 24, 21, 21, 21, 19, 19, 19, 16.5, 16.5, 0, 16.5, 16.5, 19, 19, 19, 19, 21, 21, 21, 24};
float Display4_Ausspeisedruck[25] = {0, 13.5, 13.5, 16, 16, 16, 13.5, 13.5, 13.5, 11.5, 11.5, 11.5, 9.5, 9.5, 0, 9.5, 9.5, 11.5, 11.5, 11.5, 11.5, 13.5, 13.5, 13.5, 16};

float Drehzahl_Motor1[25] = { 16.2, 17.4, 18.6, 19.8, 21.33, 20, 18.66, 17.33, 16, 14.66, 13.33, 12, 10.66, 9.33, 8, 9.2, 10.4, 11.6, 12.8, 14, 15.2, 16.4, 17.6, 18.8, 20};
float Drehzahl_Motor2[25] = { 0.00, 1.27, 2.71, 4.33, 6.22, 7.29, 8.16, 8.84, 9.33, 9.62, 9.72, 9.62, 9.32, 8.84, 8.16, 10.33, 12.73, 15.39, 18.29, 21.43, 24.82, 28.45, 32.33, 36.45, 40.82};
float Drehzahl_Motor3[25] = { 24.55, 24.48, 24.16, 23.57, 23.08, 19.48, 16.16, 13.13, 10.39, 7.93, 5.77, 3.90, 2.31, 1.01, 0.00, -1.39, -3.15, -5.27, -7.76, -10.61, -13.82, -17.39, -21.33, -25.64, -30.30};

float Servomotor1[25] = { 46, 42, 39, 35, 32, 32, 26, 22, 19, 16, 13, 9.6, 6.4, 3.2, 0, -3, -6, -9, -12, -15, -18, -21, -24, -27, -30};
float Servomotor2[25] = { 0, 6.4, 13, 19, 26, 29, 39, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45};

DFRobot_LedDisplayModule LED1(Wire, 0x48);
//DFRobot_LedDisplayModule LED2(Wire, 0x4B);
Servo ServoMotor1;
Servo ServoMotor2;

#define PINServoM1 9
#define PINServoM2 10

int prevStep = 0;
bool runoncecolor = true;

int eingang = A0; // Port A0 wird nun mit dem Wort "eingang" gleichgesetzt
int sensorwert = 0; // "sensorwert" wird als Variable für den Wert des Schiebereglers verwendet

void setup()
{
  Wire.begin();
  Wire.setClock(400000);  // Set the SCL clock speed to 400kHz
  Serial.begin(9600);
  /*Wait for the chip to be initialized completely, and then exit*/
  //  while (LED1.begin4() != 0)
  //  {
  Serial.println("111 Failed to initialize the chip , please confirm the chip connection!");
  //    delay(1000);
  //  }
  ServoMotor1.attach(PINServoM1);
  ServoMotor2.attach(PINServoM2);

  /* Set the display area to 1, 2, 3, 4
     It can show 4 bits, the region of each parameter is 1~4
     Please resend the display value if the display area is changed
  */
  LED1.setDisplayArea4(1, 2, 3, 4);
  //LED2.setDisplayArea4(1, 2, 3, 4);

  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
//#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
//#endif
  // End of trinket special code

  strip1.begin();
  strip1.setBrightness(100);
  strip1.show(); // Initialize all pixels to 'off'

  strip2.begin();
  strip2.setBrightness(100);
  strip2.show(); // Initialize all pixels to 'off'

  AFMSbot.begin(); // Start the bottom shield
  AFMStop.begin(); // Start the top shield

  stepper1.setMaxSpeed(5000.0);
  stepper1.setAcceleration(5000.0);

  stepper2.setMaxSpeed(5000.0);
  stepper2.setAcceleration(5000.0);

  stepper3.setMaxSpeed(5000.0);
  stepper3.setAcceleration(5000.0);

  // initialize the button pin as a input:
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
}

void loop()
{
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  if (buttonState1 != lastButtonState1)
  {
    chnagecount++;
    if (chnagecount > 2) chnagecount = 2;
    if (chnagecount == 2)
    {
      Serial.println("on1");
      chnagecount = 0;
      selectedLi--;
    }
    incr++;

  }
  lastButtonState1 = buttonState1;
  if (buttonState2 != lastButtonState2)
  {
    chnagecount++;
    if (chnagecount > 2) chnagecount = 2;
    if (chnagecount == 2)
    {
      Serial.println("on2"); chnagecount = 0; selectedLi++;
    }
    decr++;
  }
  lastButtonState2 = buttonState2;

  int potienStep;
  potienStep = selectedLi;
  Serial.print("Fahrstufen: ");
  Serial.println(Fahrstufen_Schiebepotie[potienStep]);

  stepper1.setSpeed(Drehzahl_Motor1[potienStep]);
  stepper2.setSpeed(Drehzahl_Motor2[potienStep]);
  stepper3.setSpeed(40);
 // stepper1.run();
 // stepper2.run();
  stepper3.run();

  // for (int i = 0; i < 90 ; i++)
  // {
  ServoMotor1.write(Servomotor1[potienStep] + 75);
  // Serial.print("Motor: ");
  //Serial.println(Servomotor1[potienStep] + 75);
  ServoMotor2.write(Servomotor2[potienStep] + 75);

  if ((Fahrstufen_Schiebepotie[potienStep]) > 0)
  {
    theaterChase(strip1.Color(0, 0, 127), 1, 0); // Blue
    runoncecolor = true;
    theaterChase(strip2.Color(0, 0, 127), 1, 0); // Blue
  }

  if ((Fahrstufen_Schiebepotie[potienStep]) == 0)
  {
    colorWipe(strip1.Color(0, 0, 255), 10); // Blue
    colorWipe(strip2.Color(0, 0, 255), 10); // Blue
    runoncecolor = true;
  }

  if ((Fahrstufen_Schiebepotie[potienStep]) < 0)
  {
    if (runoncecolor)
    {
      colorWipe(strip1.Color(255, 0, 0), 10); // Red
      colorWipe(strip2.Color(255, 0, 0), 10); // Red
      runoncecolor = false;
    }
    theaterChase(strip1.Color(127, 0, 0), 1, 1); // Red
    theaterChase(strip2.Color(127, 0, 0), 1, 1); // Red
  }

  // colorWipe(strip.Color(255, 0, 0), 10); // Red
  // colorWipe(strip.Color(0, 0, 255), 1); // Blue
  //  theaterChase(strip.Color(127, 0, 0), 10); // Red

  LED1.print4(Display1_Drehzahlen[potienStep]);
  //Serial.println(Display1_Drehzahlen[potienStep]);
  int currStep = Fahrstufen_Schiebepotie[potienStep];
  delay(300);
  if (prevStep != currStep)
  {
    prevStep = currStep;
    ServoMotor1.attach(PINServoM1);
    ServoMotor2.attach(PINServoM2);
  }
  else
  {
    ServoMotor1.detach();
    ServoMotor2.detach();
  }

  /*
    LED1.print4(Display1_Drehzahlen[potienStep]);
    Serial.println(Display1_Drehzahlen[potienStep]);
    // delay(1000);

    LED1.print4(Display2_KMH[potienStep]);
    Serial.println(Display2_KMH[potienStep]);
    // delay(1000);

    LED1.print4(Display3_Einspeisedruck[potienStep]);
    Serial.println(Display3_Einspeisedruck[potienStep]);
    // delay(1000);

    LED1.print4(Display4_Ausspeisedruck[potienStep]);
    Serial.println(Display4_Ausspeisedruck[potienStep]);
    delay(1000);  */
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait)
{
  for (uint16_t i = 0; i < strip1.numPixels(); i++)
  {
    strip1.setPixelColor(i, c);
    strip1.show();
    strip2.setPixelColor(i, c);
    strip2.show();
    delay(wait);
  }


}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait, int oppo)
{
  // for (int j = 0; j < 50; j++)
  //{ //do 10 cycles of chasing
  for (int q = 0; q < 3; q++) {
    for (uint16_t i = 0; i < strip1.numPixels(); i = i + 3)
    {
      if (oppo == 1)
      {
        strip1.setPixelColor(i - q, c);  //turn every third pixel on
        strip2.setPixelColor(i - q, c);  //turn every third pixel on
      }
      else
      {
        strip1.setPixelColor(i + q, c);  //turn every third pixel on
        strip2.setPixelColor(i + q, c);  //turn every third pixel on
      }
    }
    strip1.show();
    strip2.show();

    delay(50);

    for (uint16_t i = 0; i < strip1.numPixels(); i = i + 3)
    {
      if (oppo == 1)
      {
        strip1.setPixelColor(i - q, 0);      //turn every third pixel off
        strip2.setPixelColor(i - q, 0);      //turn every third pixel off
      }
      else
      {
        strip1.setPixelColor(i + q, 0);      //turn every third pixel off
        strip2.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
  //}
}
