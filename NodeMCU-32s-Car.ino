#include "Header.h"

void setup() 
{
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(ENA, OUTPUT);
  // PWM config
  ledcSetup(pwmChannel, freq, resolution);
  ledcSetup(pwmChannel1, freq1, resolution1);
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ENA, pwmChannel);
  ledcAttachPin(ENB, pwmChannel1);
  // attach Pin 21 to Servo
  myservo.attach(21,500,2400);
  myservo.write(90);
  // Start WiFi connection and sever Blynk
  WiFi.begin(ssid,pass);
  Blynk.begin(auth, ssid, pass);
  // Function run every 0.3 second with timer
  Timer.setInterval(300L,Control);
}

void loop()
{
  Blynk.run();
  Timer.run();
}

// SR04
void CalDis()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  // Convert the time into a distance
  distance = duration*SOUND_VELOCITY/2;
  Serial.print("Distance = ");
  Serial.println(distance);
  Blynk.virtualWrite(V6,distance);
}

// Motor
void PWM_setup()
{
  ledcWrite(pwmChannel,dutyCycle);
  ledcWrite(pwmChannel1,dutyCycle * 1.05);
}

void Foward()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    PWM_setup();
}

void BackWard()
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    ledcWrite(pwmChannel,10000);
    ledcWrite(pwmChannel1,10000 * 1.05);
}

void Left(int D)
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  ledcWrite(pwmChannel,D);
  ledcWrite(pwmChannel1,D * 1.05);
}

void Right(int D)
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  ledcWrite(pwmChannel,D);
  ledcWrite(pwmChannel1,D * 1.05);
}

// Servo
void Reset()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  ledcWrite(pwmChannel,30000);
  ledcWrite(pwmChannel1,30000 * 1.05);
}

void ServoRight()
{
 myservo.write(30);
 BlynkDelay(500);
 CalDis();
 myservo.write(90);

}

void ServoLeft()
{
 myservo.write(170);
 BlynkDelay(500);
 CalDis();
 myservo.write(90);
}

void ResetServo()
{
 myservo.write(100);
 BlynkDelay(500);
 CalDis();
 myservo.write(90);
}

// Blynk
BLYNK_WRITE(V0)
{
  forward = param.asInt();
}
BLYNK_WRITE(V1)
{
  backward = param.asInt();
}
BLYNK_WRITE(V2)
{
  left = param.asInt();
}
BLYNK_WRITE(V3)
{
  right = param.asInt();
}
BLYNK_WRITE(V4)
{
  stop = param.asInt();
}
BLYNK_WRITE(V5)
{
  dutyCycle = param.asInt();
  Blynk.virtualWrite(V7,dutyCycle);
  PWM_setup();
}

// Main functions
void Control()
{
  CalDis();
  if(distance == 0 || distance > limit) smartcar();
  else if(distance < limit) autocar();
}

void autocar()
{
    Reset();
    ServoRight();
    DisR = distance;
    ServoLeft();
    DisL = distance;
    ResetServo();
    if(DisR < limit && DisL < limit) BackWard();
    else if(DisR > DisL) Right(60000);
    else if(DisL > DisR) Left(60000);
}

void smartcar()
{
  if(forward == 1) Foward();
  else if( backward == 1) BackWard();
  else if (left == 1) Left(10000);
  else if (right == 1) Right(10000);
  else if (stop == 1) Reset();
  else Reset();
}








