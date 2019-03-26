/*
=======================MevArm V1.0=========================
This is first version of mavarm .
Pick and place function is programmed here.

This code is made in maverickden by vishal Patil .
In case of any query go to our webside.
This may resullt in copy right please do not copy or try to modified the code for personal use.
It may be committed for legle panelty.
It is property of maverickden.
=============================================================
*/
#include "function.h"
#include <IRremote.h>
const int ir_sensore_pin1 = 10;
IRrecv irrecv(ir_sensore_pin1);
decode_results results;

void setup() 
{ 
  
Serial.begin(9600);
 irrecv.enableIRIn();
base.attach(2);  
left.attach(3);
grip.attach(5);
right.attach(4);
base.write(0);
delay(1000);
left.write(70);
delay(1000);
grip.write(180);
delay(1000);
right.write(140);
delay(2000);

 button1 = false;
  button2 = false;
  button3 = false;
  button4 = false;
  button5 = false;
  button6 = false;
  button7 = false;
  button8 = false;
} 
 
void loop() 
{ 
//========================================================================
  if (irrecv.decode(&results))
  {
    Serial.println("receveed ir data..........");
    temp2 = results.value;
    irrecv.resume(); // Receive the next value
    //temp2 = -temp2;
    Serial.println(temp2);
    if(temp2 != -1)
    {
      _k = temp2;
    }
}
//Serial.println(_k);
    if(Serial.available()>0)
 {
  char data=Serial.read();
out=out+data;

if(data=='D')
{
   _a= out.indexOf('A');
 X1 = out.substring(0, _a);
 Serial.print("X1=");
 Serial.println(X1);
  _b= out.indexOf('B');
 Y1= out.substring( (_a+1),_b);
  Serial.print("Y1=");
 Serial.println(Y1);
  _c= out.indexOf('C');
 X2= out.substring( (_b+1),_c);
  Serial.print("X2=");
 Serial.println(X2);
  _d= out.indexOf('D');
 Y2= out.substring( (_c+1),_d);
  Serial.print("Y2=");
 Serial.println(Y2);
 
hypo1=sqrt(sq(middlepoint-X1.toInt())+sq(Y1.toInt()));
theta1=asin((Y1.toInt()/hypo1));
hypo2=sqrt(sq(X2.toInt()-middlepoint)+sq(Y2.toInt()));
theta2=asin((Y2.toInt()/hypo2));
theta1=(theta1*180)/pi;
theta2=(theta2*180)/pi;
angle=180-(theta1+theta2);
Serial.print("theta1==");
Serial.println(theta1);
Serial.print("theta2==");
Serial.println(theta2);
Serial.println(angle);

gripopen();
delay(300);
back();
for(pos = 20; pos < (int)theta1; pos += 1)   
  { base.write(pos); delay(15);}
// base.write((int)theta1);
// front();
 gripclose();
 delay(300);
 front();
 delay(300);
 gripopen();
 delay(300);
 back();
 for(pos = 20; pos < (int)angle; pos += 1)   
  { base.write(pos); delay(15);}
 //base.write((int)angle);
 front();
 delay(300);
 gripclose();
 delay(300);
 back();
 //delay(300);
 //gripopen();
 delay(300);
// back();
 base.write(0);
 front();
   out="";
 theta1=0;
 theta2=0;
 data="";
}
 }

 remote();
// bluetooth();
_k=0;
temp2=0;
//delay(1000);
   //==============================================================================
   /*
sright();  
delay(100);  
gripopen();  
delay(100);  
front();  
delay(100);  
gripclose();  
delay(100);  
back();  
delay(100);  
sleft();  
delay(100);
front();  
delay(100);  
gripopen();  
delay(100);  
back();  
delay(100);*/
} 
