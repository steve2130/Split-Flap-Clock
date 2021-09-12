#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Unistep2.h>

const char *ssid     = "Test";
const char *password = "11335577";
long previousMillis = 0;
char PreviousSecond = 0;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
unsigned int TimeZone= 28800;

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", TimeZone);

// Stepper
Unistep2 stepperX(14, 12, 13, 15, 4096, 1000);
Unistep2 stepperY(5, 4, 0, 2, 4096, 1000);

void setup(){
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  timeClient.begin();
}


void loop() {
  long currentMillis = millis();
  if (currentMillis - previousMillis >= 1000) {
    stepperX.run();
    timeClient.update();
    timeClient.getSeconds();
    Serial.println(timeClient.getSeconds());
    previousMillis = currentMillis;
    char CurrentSecond = timeClient.getSeconds();

    if (CurrentSecond - PreviousSecond >= 1) {
      PreviousSecond = CurrentSecond;
      
      if ( stepperX.stepsToGo() == 0 ){ 
      stepperX.move(2500);
      }
    }
    else if (CurrentSecond - PreviousSecond <= 0){
      PreviousSecond = 0;
      
      if ( stepperX.stepsToGo() == 0 ){ 
      stepperX.move(2500);
      }
    }
  }
}
