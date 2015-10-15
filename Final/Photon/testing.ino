
SYSTEM_MODE(SEMI_AUTOMATIC);
int led1 = D2;
int led2 = D3;
int led3 = D4;
int led4 = D5;
int led5 = D6;
int led6 = D7;
int led7 = A2;
int led8 = A3;
int led9 = A4;
/*
void setup()
{
    pinMode(led9, OUTPUT);
}

void loop()
{
  digitalWrite(led9,HIGH);
}*/

#include <MMA8452Q.h>
//SYSTEM_MODE(SEMI_AUTOMATIC);
char publishString1[180];
// Create an MMA8452Q object, used throughout the rest of the sketch.
MMA8452Q accel;
//int led1 = A5;
int selection = 1;
char inByte = 'D';
int state = 68;
int button = A1;
// The above works if the MMA8452Q's address select pin (SA0) is high.
// If SA0 is low (if the jumper on the back of the SparkFun MMA8452Q breakout
// board is closed), initialize it like this:
// MMA8452Q accel(MMA8452Q_ADD_SA0_);

void setup()
{
    Serial.begin(9600);
    accel.init(SCALE_2G, ODR_1);
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);
    pinMode(led5, OUTPUT);
    pinMode(led6, OUTPUT);
    pinMode(led7, OUTPUT);
    pinMode(led8, OUTPUT);
    pinMode(led9, OUTPUT);
    //Spark.function("led",ledToggle);
    pinMode(button, INPUT);
    //pinMode(D5, OUTPUT);
    //pinMode(D6, OUTPUT);
    //pinMode(D7, OUTPUT);
}

void loop()
{

    if (Serial.available())
    {
       inByte = Serial.read();
       state = int(inByte);
       if(state == 68){
         ledToggle("on");
       }else if( state == 86){
         ledToggle("off");
       }
    }

    if (accel.available())
    {
        accel.read();
        unsigned lightSensor = analogRead(A0);
        int x = accel.x;
        float cx = accel.cx;
        int y = accel.y;
        float cy = accel.cy;
        int z = accel.z;
        float cz = accel.cz;
        int click = 0;
        //int tap= accel.readTap();
        allLight(x, y);
        if(digitalRead(button) == HIGH)
        {
          click = 1;
        }

        sprintf(publishString1,"{\"sensor\":%u, \"cx\":%f, \"x\":%d, \"cy\":%f, \"y\":%d, \"cz\":%f, \"z\":%d, \"click\":%d, \"state\":%d}",lightSensor,cx,x,cy,y,cz,z,click,state);
        Serial.println(publishString1);
        if(selection == 1){
          Spark.publish("everything",publishString1);
        }else{
          Spark.publish("erase",publishString1);
        }
    }


}

void allLight(int xValue, int yValue){
  if(xValue > 0){
    digitalWrite(led7,HIGH);
  }else{
    digitalWrite(led7, LOW);
  }

  if(xValue > 341){
    digitalWrite(led8, HIGH);
  }else{
    digitalWrite(led8, LOW);
  }

  if(xValue > 685){
    digitalWrite(led9, HIGH);
  }else{
    digitalWrite(led9, LOW);
  }

  if(xValue < 0){
    digitalWrite(led1,HIGH);
  }else{
    digitalWrite(led1, LOW);
  }

  if(xValue < -341){
    digitalWrite(led2, HIGH);
  }else{
    digitalWrite(led2, LOW);
  }

  if(xValue < -685){
    digitalWrite(led3, HIGH);
  }else{
    digitalWrite(led3, LOW);
  }

  if(yValue > 0){
    digitalWrite(led4,HIGH);
  }else{
    digitalWrite(led4, LOW);
  }

  if(yValue > 341){
    digitalWrite(led5, HIGH);
  }else{
    digitalWrite(led5, LOW);
  }

  if(yValue > 685){
    digitalWrite(led6, HIGH);
  }else{
    digitalWrite(led6, LOW);
  }
}

int ledToggle(String command) {

    if (command=="on") {
        digitalWrite(led1,LOW);
        selection = 1;
        return 1;
    }
    else if (command=="off") {
        digitalWrite(led1,HIGH);
        selection = 0;
        return 0;
    }
    else {
        return -1;
    }
}
