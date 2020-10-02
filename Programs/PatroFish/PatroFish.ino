/*
  ▪ * Team Id: pf#1296
  ▪ * Author List: Sagar Narkhede, Omkar Sutar,Pooja katkar, Ashlesha Borade
  ▪ * Filename: receiver_code
  ▪ * Theme: Patrol Fish
  ▪ * Functions: void servo(char servo_no, int angle, int speed)
  ▪ * Global Variables:None
  ▪ *
  ▪ */

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <VarSpeedServo.h>
/*
VarSpeedServo myservo1; // left fin servo pin
VarSpeedServo myservo2; // right fin servo pin
*/VarSpeedServo myservo3; // head servo pin
VarSpeedServo myservo4; // middel servo pin
VarSpeedServo myservo5; // tail servo pin

RF24 radio(7, 8);// CE, CSN pins of the nRF24L01 module are connected to these pins [CE: Chip Enable, CSN: Chip Select Not]
const byte address[6] = "00001";//5 Byte address of nrf device

void setup()
{
  Serial.begin(9600);//Start serial communication port
  Serial.println("Rx Starting");//Print a line on serial monitor to indicate start of code.

  //***********  Initialize the nRF24L01 module ************************************************
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  radio.setDataRate(RF24_250KBPS);
  //********************************************************************************************
  //attach the servo motors to pins 3, 5, 6 ,9,10 of Arduino Nano
  /*myservo1.attach(10);
  myservo2.attach(9);*/
  myservo3.attach(3);
  myservo4.attach(5);
  myservo5.attach(6);
  pinMode(A1, OUTPUT);
  pinMode(A0, INPUT);
}

void loop()
{

 
  
  if (radio.available())
  {
    char text[32] = ""; //initialize array to save input command from joystick
    radio.read(&text, sizeof(text));//read the command from joystic
    Serial.println(text);//print the command
    /*
       comapir the input data with the fix data and give the particular movement to the fish
    */
    if (text[0] == 'f' && text[1] == 'f')//take a forward motion
    {

     /* servo('l', 90, 250);
      servo('r', 90, 250);*/
      servo('h', 90, 100);
      servo('m', 30, 100);
      servo('t', 100, 100);
      delay(500);
      servo('m', 160, 100);
      delay(500);
      servo('m', 90, 100);
    }
    else   if (text[0] == 's' && text[1] == 'f')//take a forward motion
    {
      servo('h', 140, 200);
      servo('m', 40, 100);
      servo('t', 150, 250);
     /* servo('l', 90, 250);
      servo('r', 90, 250);*/
      delay(150);

      servo('h', 50, 200);
      servo('m', 130, 100);
      servo('t', 50, 250);
      delay(150);
      servo('h', 90, 100);
      servo('m', 90, 100);
      servo('t', 100, 100)  ;
    }

    else if (text[0] == 'l' && text[1] == 'l')//take a left motion
    {
      servo('h', 170, 200);
      servo('m', 30, 100);
      servo('t', 160, 250);
     /* servo('l', 90, 250);
      servo('r', 90, 200);*/
      delay(150);
      servo('t', 100, 250);
      delay(150);
    }

    else if (text[0] == 'r' && text[1] == 'r')//take a right motion
    {
     /* servo('l', 90, 250);
      servo('r', 90, 250);*/
      servo('h', 30, 200);
      servo('m', 160, 100);
      servo('t', 40, 250);
      delay(150);
      servo('t', 100, 250);
      delay(150);
    }
    else if (text[0] == 's' && text[1] == 's')//stop the robot
    {
   /*   servo('l', 90, 250);
      servo('r', 90, 250);*/
      servo('h', 90, 100);
      servo('m', 80, 100);
      servo('t', 100, 100);
      // delay(300);
    }
    else if (text[0] == 'w' && text[1] == 'd')//detect water
    {
      digitalWrite(A0, HIGH);//initialize the input pin
      int s = analogRead(A0); //read the status of input pin
      Serial.println(s);
      if (s <= 500)//comapire the input value with threshold
      {
        Serial.println(s);
        digitalWrite(A1, HIGH);//turn on the indicator
        delay(200);//wait for indication
        digitalWrite(A1, LOW);//turn off the indicator
        delay(200);//wait for indication
        s = analogRead(A0);
      }
      else
        digitalWrite(A1, LOW);//turn off  indication
    }
    else
      Serial.println("wrong data");
  }
  else
    Serial.println("conection_fail");
}

/*
    Function Name:void servo(char servo_no, int angle, int speed)
     Input:servo_no,angle,speed
     Output: none
     Logic: this function are use to reduse the complixity to apply the saperaty angle ,speed ,no of servos etc
     as per the example given below the head servo moveto 90 degree angle with speed 200
     Example Call: servo('h', 90, 200);
*/
void servo(char servo_no, int angle, int speed)
{
  switch (servo_no)
  {
    case 'l'://select left fine servo
     // myservo1.write(angle, speed); //move left fine servo to input angle with input speed
      break;
    case 'r'://select right fine servo
     // myservo2.write(angle, speed);//move right fine servo to input angle with input speed
      break;
    case 'h'://select head servo
      myservo3.write(angle, speed);//move head servo to input angle with input speed
      break;
    case 'm'://select middel servo
      myservo4.write(angle, speed);//move middel servo to input angle with input speed
      break;
    case 't'://select tail servo
      myservo5.write(angle, speed);//move tail servo to input angle with input speed
      break;
  }
}
