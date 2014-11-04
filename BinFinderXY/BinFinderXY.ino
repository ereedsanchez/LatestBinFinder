
#include <Servo.h>
#include <Process.h>

//Process XYNAMEstring;
String XYString;

Servo servoX;
Servo servoY;
int posX;
int posY;
int laser = 4;
int LED = 5;


void setup() {
  Serial.begin(9600);
  pinMode(laser, OUTPUT);
  pinMode(LED, OUTPUT);

  servoX.attach(2);
  servoY.attach(3);
  establishContact();

}


void loop() {

  int sendData = 0;
  Servo currentServoX;
  Servo currentServoY;

  int PositionX = 50;
  int PositionY = 50;

  digitalWrite(laser, LOW);

  // if there's any serial data in the buffer, read a byte:
  if (Serial.available() > 0) {
        digitalWrite(LED, HIGH);

    int inByte = Serial.read();

    // respond to the values 'x', 'y', 'N'
    switch (inByte) {

      case'A':     // Network Status
        digitalWrite(LED, HIGH);
        break;

      case'x':     // x D-Pad
        sendData = 1;
        break;

      case 'y':    // y D-Pad
        sendData = 2;
        break;

      case 'u':    // User info Automove
        sendData = 3;

        break;

      case 'o':

        break;

    }


    if (sendData == 1 ) {
      int PositionX = Serial.parseInt();
      // map the result to a level from 0 to 180
      PositionX = map(PositionX, 0, 100, 150, 50);
      servoX.write(PositionX);
      //digitalWrite(LED, HIGH);
      //delay(100);
      digitalWrite(LED, LOW);
      delay(100);
      digitalWrite(LED, HIGH);
      delay(100);
      digitalWrite(LED, LOW);
      delay(100);
      digitalWrite(LED, HIGH);

      Serial.print("PositionX:");
      Serial.println(PositionX);
      delay(15);
      digitalWrite(laser, HIGH);
      delay(1500);
    }


    if (sendData == 2 ) {
      int PositionY = Serial.parseInt();
      PositionY = map(PositionY, 0, 100, 140, 40);

      servoY.write(PositionY);
      
      digitalWrite(LED, LOW);
      delay(100);
      digitalWrite(LED, HIGH);
      delay(100);
      digitalWrite(LED, LOW);
      delay(100);
      digitalWrite(LED, HIGH);
      
      Serial.print("PositionY:");
      Serial.println(PositionY);
      delay(15);
      digitalWrite(laser, HIGH);
      delay(1500);
      delay(10);
    }


    if (sendData == 3 ) {

      //      if (!XYNAMEstring.running()) {
      //   XYNAMEstring.begin("string");
      //   XYNAMEstring.addParameter("+%T");
      //   XYNAMEstring.run();
      // }

      Serial.println("Got U");


      String XYString = Serial.readString();

      Serial.println("Got string");

      // find the colons:
      int firstColon = XYString.indexOf(":");
      int secondColon = XYString.lastIndexOf(":");

      String posXstring = XYString.substring(0, firstColon);
      String posYstring = XYString.substring(firstColon + 1, secondColon);

      int PositionX = posXstring.toInt();
      int PositionY = posYstring.toInt();

      PositionX = map(PositionX, 0, 100, 150, 30);
      PositionY = map(PositionY, 0, 100, 140, 40);

      servoX.write(PositionX);
      servoY.write(PositionY);
      
    digitalWrite(LED, LOW);
      delay(100);
      digitalWrite(LED, HIGH);
      delay(100);
      digitalWrite(LED, LOW);

      digitalWrite(laser, HIGH);
      
      digitalWrite(LED, LOW);
      delay(100);
      digitalWrite(LED, HIGH);
      delay(100);
      digitalWrite(LED, LOW);
      delay(100);
      digitalWrite(LED, HIGH);

      Serial.print("PositionX:Y = ");
      Serial.print(PositionX);
      Serial.print(":");
      Serial.print(PositionY);

      delay(5000);
      digitalWrite(laser, LOW);
      delay(10);


    }
  }

}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.print('A');   // send a capital A
    digitalWrite(LED, HIGH);
    delay(10);
    digitalWrite(LED, LOW);
    delay(300);
  }



}


