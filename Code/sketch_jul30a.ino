#include <Unistep2.h>

int sensor1 = 9;  //ky003
int sensor2 = 10;  //3144
int val1;
int val2;
long previousMillis = 0;
int StepperCountstep = 0;
Unistep2 stepperX(14, 12, 13, 15, 4096, 1000);
Unistep2 stepperY(5, 4, 0, 2, 4096, 1000);
int StepperStep = 137;
bool calibrating = false;

void setup()
{
  Serial.begin(115200);
  pinMode(sensor1, INPUT); //set sensor pin as input
  pinMode(sensor2, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  
  val1 = digitalRead(sensor1);
  val2 = digitalRead(sensor2);
  if (val1 == LOW) {
    digitalWrite(LED_BUILTIN, LOW);  
    stepperX.run();
    stepperY.run();
    stepperX.moveTo(0);
    stepperY.moveTo(0);
  }

    if (val2 == LOW) {
    digitalWrite(LED_BUILTIN, HIGH);   
    long currentMillis = millis();
        if (currentMillis - previousMillis >= 2000) {
           previousMillis = currentMillis;
           stepperX.run();
           stepperX.move(-5000);
           Serial.print(val1);
           Serial.print(" ,  ");
           Serial.println(val2);
        }
  }

  else {
    digitalWrite(LED_BUILTIN, HIGH);
    long currentMillis = millis();
    stepperX.run();
    stepperY.run();
    if (currentMillis - previousMillis >= 1000) {
      previousMillis = currentMillis;
      StepperCountstep++;

      if (stepperY.stepsToGo() == 0 ){ 
        stepperY.move(StepperStep);
      }

      if (stepperX.stepsToGo() == 0 ){ 
        stepperX.move(StepperStep);
      }

      Serial.print(StepperStep);
      Serial.print(" ,  ");
      Serial.print(StepperCountstep);
      Serial.print(" ,  ");
      Serial.print(stepperX.currentPosition());
      Serial.print(" ,  ");
      Serial.println(stepperY.currentPosition());
      
      }
    }
  }
