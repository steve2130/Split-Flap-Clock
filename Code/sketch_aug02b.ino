#include <Unistep2.h>
//Motor stops if hall effect sensor is activated


int sensor = 9;
int val;
long previousMillis = 0;
int StepperCountstep = 0;
Unistep2 stepperX(14, 12, 13, 15, 4096, 1000);// 
Unistep2 stepperY(5, 4, 0, 2, 4096, 1000);// 
int StepperStep = 137;
bool calibrating = false;

void setup()
{
  Serial.begin(115200);
  pinMode(sensor, INPUT); //set sensor pin as input
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  
  val = digitalRead(sensor);
  if (val == LOW) {
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
    stepperX.run();
    stepperY.run();
    stepperX.moveTo(0);
    stepperY.moveTo(0);
  }

  else {
    digitalWrite(LED_BUILTIN, HIGH);
    long currentMillis = millis();
    stepperX.run();
    stepperY.run();


      if (stepperX.stepsToGo() == 0 ){ 
        stepperX.move(StepperStep);
      }

      }
    }
  
