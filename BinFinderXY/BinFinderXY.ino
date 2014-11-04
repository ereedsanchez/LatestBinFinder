// add case for Network Status -LED ON
//add case arms moving - flashing LED


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
  //establishContact();


}




void loop() {

  int sendData = 0;
  Servo currentServoX;
  Servo currentServoY;

  //currentServoX = 50;
  //currentServoY = 50;

  int PositionX = 50;
  int PositionY = 50;

  digitalWrite(laser, LOW);
  digitalWrite(LED, LOW);

  // if there's any serial data in the buffer, read a byte:
  if (Serial.available() > 0) {
    int inByte = Serial.read();

    // respond to the values 'x', 'y', 'b'
    switch (inByte) {

      case'N':     // Network Status
        //update
        break;

      case'x':     // x D-Pad
        sendData = 1;
        //currentServoX = servoX;
        break;

      case 'y':    // y D-Pad
        sendData = 2;
        //currentServoY = servoY;

        break;

      case 'u':    // User info Automove
        sendData = 3;
        //currentServoX = servoX;
        //currentServoY = servoY;

        break;

      case 'o':

        break;



        //  digitalWrite(laser, HIGH);
    }


    if (sendData == 1 ) {
      int PositionX = Serial.parseInt();
      // map the result to a level from 0 to 180
      PositionX = map(PositionX, 0, 100, 150, 30);
      servoX.write(PositionX);

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

      int PositionNAMEX = posXstring.toInt();
      int PositionNAMEY = posYstring.toInt();


      PositionNAMEX = map(PositionNAMEX, 0, 100, 1, 179);
      posY = PositionNAMEX;
      servoY.write(posY);

      PositionNAMEY = map(PositionNAMEY, 0, 100, 1, 179);
      posX = PositionNAMEY;
      servoX.write(posX);

      digitalWrite(laser, HIGH);
      delay(1000);
      digitalWrite(laser, LOW);
      Serial.print("PositionNAMEX");
      Serial.println(PositionNAMEX);
      delay(10);


    }
  }

}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.print('A');   // send a capital A
    delay(300);
  }
}


