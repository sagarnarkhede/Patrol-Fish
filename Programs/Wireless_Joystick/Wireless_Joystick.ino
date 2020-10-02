
/*
  ▪ * Team Id: pf#1296
  ▪ * Author List: Sagar Narkhede, Omkar Sutar,Pooja katkar, Ashlesha Borade
  ▪ * Filename: transmitter_code
  ▪ * Theme: Patrol Fish
  ▪ * Functions: void buzzer(),void read()
  ▪ * Global Variables:button_up,button_down,button_left,button_right
  ▪ *
  ▪ */
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define joyX A6 // Horizontal axis Potentiometer of Joystick module
#define joyY A7  // Vertical axis Potentiometer of Joystick module
int button = A5;   // Button is connected to pin A5 of arduino
int buttonState = 0;  // variable to store value from the in-built push button in the joystick module
int buz = A0;//buzzer pin
int button_up;
int button_up1 = 2; //button for upword movement of fish
int button_down1 = 4;//button for downword movement of fish
int button_down;
int button_left1 = 3;//button for leftword movement of fish
int button_left;
int button_right1 = 5;//button for rightword movement of fish
int button_right;
int buzz = A0;//conect buzzer to A0 pin
int xValue = 0; // read the analog value of Horizontal axis Potentiometer
int yValue = 0; // read the analog value of Vertical axis Potentiometer
int fLED = A2;//LED for forward ditection indicator
int rLED = A1;//LED for right ditection indicator
int lLED = A4;//LED for left ditection indicator
int tLED = A3;//LED for transmision indicator
int count = 0;
RF24 radio(7, 8);// CE, CSN pins of the nRF24L01 module are connected to these pins [CE: Chip Enable, CSN: Chip Select Not]
const byte address[6] = "00001";// 5 byte address of transmitter
char text[2];// array to store the character to be sent
void setup() {
  Serial.begin(9600);//start serial communication
  Serial.println("Tx Starting");//start transmission
  radio.begin();// begin the radio with default conditions
  radio.openWritingPipe(address);////open  pipe for transmission
  radio.setPALevel(RF24_PA_MIN);// SET PA level High(0 dBm)
  radio.setDataRate(RF24_250KBPS);//set data rate 250 kbps options are (1MBps,2MBps)
  radio.stopListening();// make radio transmitter ready to tarnsmitt.
  radio.powerUp();
  pinMode(buzz, OUTPUT);
  pinMode(button, INPUT);
  digitalWrite(button, HIGH);
  pinMode(joyX, INPUT);
  pinMode(joyY, INPUT);
  pinMode(button_up1, OUTPUT);
  digitalWrite(button_up1, HIGH);
  pinMode(button_down1, OUTPUT);
  digitalWrite(button_down1, HIGH);
  pinMode(button_left1, OUTPUT);
  digitalWrite(button_left1, HIGH);
  pinMode(button_right1, OUTPUT);
  digitalWrite(button_right1, HIGH);
  pinMode(fLED, OUTPUT);
  pinMode(rLED, OUTPUT);
  pinMode(lLED, OUTPUT);
  pinMode(tLED, OUTPUT);
  digitalWrite(buzz, HIGH);

}

void loop()
{
  read(); //read the value of joystick
  buzzer();//beep the buzzer


  //Depending on the position of the joystick, and the corresponding values from the two potentiometers the command is encoded into characters ff, ll, rr
  // which represent Forward,  Left, Right respectively.


  if (xValue >= 1020 && button_up == 1)
  {
    if (xValue > yValue)
    {
      text[0] = 'f';
      text[1] = 'f';
      send();
      digitalWrite(fLED, HIGH);
      delay(1000);
      digitalWrite(fLED, LOW);
    }
  }

  else if (xValue >= 1020 && button_up == 0 )
  {
    if (xValue > yValue)
    {
      text[0] = 's';
      text[1] = 'f';
      send();
      digitalWrite(fLED, HIGH);
      delay(300);
      digitalWrite(fLED, LOW);
    }
  }

  else if ( yValue >= 1020)
  {
    if (xValue < yValue)
    {
      text[0] = 'l';
      text[1] = 'l';
      send();
      digitalWrite(lLED, HIGH);
      delay(300);
      digitalWrite(lLED, LOW);
    }
  }
  else if ( yValue >= 1020 &&  button_left == 0 )
  {
    if (xValue < yValue)
    {
      text[0] = 's';
      text[1] = 'l';
      send();
      digitalWrite(lLED, HIGH);
      delay(300);
      digitalWrite(lLED, LOW);
    }
  }
  else if ( yValue <= 10)
  {
    text[0] = 'r';
    text[1] = 'r';;
    send();
    digitalWrite(rLED, HIGH);
    delay(300);
    digitalWrite(rLED, LOW);
  }
  else if ( yValue <= 10 &&  button_right == 0)
  {
    text[0] = 's';
    text[1] = 'r';;
    send();
    digitalWrite(rLED, HIGH);
    delay(300);
    digitalWrite(rLED, LOW);
  }
  else if ( xValue <= 10 )
  {
    text[0] = 's';
    text[1] = 's';;
    send();
  }

  else if (button_down == 0 )
  {
    text[0] = 'w';
    text[1] = 'd';;
    send();
    digitalWrite(fLED, HIGH);
    digitalWrite(lLED, HIGH);
    digitalWrite(rLED, HIGH);
    delay(100);
    digitalWrite(fLED, LOW);
    digitalWrite(lLED, LOW);
    digitalWrite(rLED, LOW);
  }
}
/*
  ▪ * Function Name: void send()
  ▪ * Input: none
  ▪ * Output: none
  ▪ * Logic: this function are use for send the data toword thr receiver
  ▪ * Example Call: send()
  ▪ */
void send()
{
  bool ack;  //initilize the variable to store the statuse of data send or not
  ack = radio.write(&text, sizeof(text));// sends data to receiver
  Serial.println(text);
  if (ack) //if data is succesfully transmitted then ack =1 and transmision LEd is on else off
  {
    Serial.println("tx succesful");
    digitalWrite(tLED, HIGH);

  }
  else {
    Serial.println("  Tx failed");
    digitalWrite(tLED, LOW);
  }
}
/*
  ▪ * Function Name:void read()
  ▪ * Input: none
  ▪ * Output:none
  ▪ * Logic:this function read the statuse of joystick module and push buttons
  ▪ * Example Call:read();
  ▪ */

void read()
{
  button_up = digitalRead(button_up1); //read state of the up Button
  button_down = digitalRead(button_down1); //read state of the down Button
  button_left = digitalRead(button_left1); //read state of the left Button
  button_right = digitalRead(button_right1); //read state of the right Button
  xValue = analogRead(joyX);// read the analog value of Horizontal axis Potentiometer
  yValue = analogRead(joyY);// read the analog value of Vertical axis Potentiometer
  buttonState = digitalRead(button); //read state of the Button
}
/*
   Function Name:void buzzer()
   Input: none
   Output:none
   Logic: this function turn on the buzzer at starting the run and end of the run
   Example Call:buzzer();
*/

void buzzer()
{

  if (buttonState == 0) //if the bush button of joystick is press for start of the run
  {
    if (count == 0)//turn on the buzzer for 2sec
    {
      digitalWrite(buzz, 0);
      delay(2000);
      digitalWrite(buzz, 1);
      count++;
    }
    else if (count == 1)//turn on the buzzer for 3sec for end of the run
    {
      digitalWrite(buzz, 0);
      delay(3000);
      digitalWrite(buzz, 1);
      count++;
    }
  }

}
