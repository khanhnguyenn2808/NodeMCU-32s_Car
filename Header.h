
#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial
#define SOUND_VELOCITY 0.034
#define BLYNK_TEMPLATE_ID "TMPLZ8dn1U-w"
#define BLYNK_DEVICE_NAME "Yeah"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Servo.h>
Servo myservo;
BlynkTimer Timer;

// Wifi config
char auth[] = "EFA2bsV3nEnlGb7a9wxHfSj01SO6GUUC";
char ssid[] = "VinaHome";
char pass[] = "thankyous";
// Motor 1 , Motor 2 congif
const int IN1 = 16 , IN2 = 17 , IN3 = 5 , IN4 = 18 ,ENA = 26 , ENB = 27;
// HC-SR04 congif
const int trigPin = 22, echoPin = 23;
long duration;
float distance ,DisR, DisL, limit = 20.0;
// Blynk function
bool forward , backward  , left  , right  , stop ;
// Setting PWM properties
const int freq = 10000,freq1 = 10000;
const int pwmChannel = 0,pwmChannel1 = 1;
const int resolution =16,resolution1 = 16;
double dutyCycle;
// Functions declare
void Control();
void autocar();
void smartcar();
void PWM_setup();
void CalDis();
void Foward();
void Backward();
void Left(int D);
void Right(int D);
void Reset();
void ServoRight();
void ServoLeft();
void ResetServo();
