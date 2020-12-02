// Katelyn DePaula and Lara Vaz final project ESE 111

#define BLYNK_PRINT Serial

// Include libraries required for Blynk and NodeMCU communication
#include <ESP8266WiFi.h>                   
#include <BlynkSimpleEsp8266.h>

// Auth Token in the Blynk App.
char auth[] = "SliHqjOTCyAlzg5vJ2mxgYpc9aw_0Q0L";

// WiFi credentials.
char ssid[] = "Katelyn's iPhone";
char pass[] = "iPhone300";

// Create variable of type BlynkTimer
BlynkTimer timer;

//These correspond to the pins on NodeMCU
int green = 4; //D2 in Node MCU
int red = 5;   //D1 in Node MCU
int soundsensor = 16; // D0
int blue = 0;   //D3
int soundAnalog = 2; // D4
int pResistor = A0; // A0

//d5 = 14
//d6=12

int blueValue;
int redValue;
int greenValue;

void myTimerEvent()
{
  Blynk.virtualWrite(V5, soundAnalog); // send data to app
}

void setup()
{
  // Sets up pins
  pinMode (red, OUTPUT);
  pinMode (green, OUTPUT);
  pinMode (blue, OUTPUT);
  pinMode (soundsensor, INPUT);
  pinMode (soundAnalog, INPUT);
  pinMode(pResistor, INPUT);
  
  // Opens serial monitor at 115200 baud
  Serial.begin(115200);
  Serial.println("Setup runs...");

  // Starts the connection with Blynk using the data provided at the top (Wi-Fi connection name, password, and auth token)
Blynk.begin(auth, ssid, pass);

  // A timer function which is called every 1000 millisecond. Note that it calls the function myTimerEvent, which in turn send the currentDistance to the Blynk server
timer.setInterval(1000L, myTimerEvent); // setup a function to be called every second
}

BLYNK_WRITE(V1){
  blueValue = param.asInt();
  analogWrite(0, blueValue);
}

BLYNK_WRITE(V2){
  redValue = param.asInt();
  analogWrite(5, redValue);
}

BLYNK_WRITE(V0){
  greenValue = param.asInt();
  analogWrite(4, greenValue);
}

void loop()
{
  // Runs the code
  Blynk.run();
  timer.run();
  int sensorvalue = digitalRead (soundsensor);
  int pValue = analogRead(pResistor);
  Serial.println(pValue);
  if (sensorvalue == 0)                                  
  {
    Serial.println("sensor0");
    digitalWrite(red, LOW);
    digitalWrite(blue, LOW);
    digitalWrite(green, LOW);
  }
  
  else
  {
    if (pValue < 700) {
      analogWrite(red, redValue);
      analogWrite(blue, blueValue);
      analogWrite(green, greenValue);
    } else {
      digitalWrite(red, LOW);
      digitalWrite(blue, LOW);
      digitalWrite(green, LOW);
    }
    Serial.println("sensor1");
  }
}
