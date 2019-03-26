#include "variable.h"

#include <Servo.h> 

//---------======== 
Servo base; 
Servo left;           
Servo grip;           
Servo right;


void back()
{rref=80;
  lref=100;
  for(int i=1;i<=30;i++)
{  left.write(lref);
  right.write(rref);
  rref=rref+2;
  lref--;
  delay(20);
 }
delay(200);
}

void front()
{
rref=140;
lref=70;
for(int i=1;i<=30;i++)
{
left.write(lref);
right.write(rref);
rref=rref-2;
lref++;
delay(20);
}
delay(200);
}
void gripopen()
{for(pos = 179; pos >60; pos -= 5) 
  { grip.write(pos);             
    delay(15);                      
  }
delay(200);
}
void gripclose()
 {for(pos = 60; pos <179; pos += 5) 
  {                               
    grip.write(pos);            
    delay(15);                       
  }
  Serial.println("Grip is closed");
  delay(200);
  }
 
void sright ()
 {for(pos = 30; pos < 150; pos += 1)   
  { base.write(pos); delay(15);}delay(200);}
void sleft()
 {for(pos = 150; pos >30; pos -= 1) 
  {base.write(pos);delay(15); }delay(200);}

  void remote()
  {
    if(_k==remotebutton1)
   {
    if(!button1)
      {
     sright();  
   delay(100); 
      button1=true;
      }
      else if(button1)
      {
       sleft();  
       delay(100);
      button1=false;
      }
   
   }
   else if(_k==remotebutton3)
   {
    if(!button3)
      {
       gripopen();  
     delay(100);
      button3=true;
      }
      else if(button3)
      {
       gripclose();  
       delay(100);
      button3=false;
      }
   
   }
    else if(_k==remotebutton4)
   {
     if(!button4)
      {
      front();  
     delay(100);
      button4=true;
      }
      else if(button4)
      {
       back();  
       delay(100);
      button4=false;
      }
      
   }
  }
//===============================================================================
  void bluetooth()
  {
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

gripclose();
delay(300);
back();
for(pos = 20; pos < (int)theta1; pos += 1)   
  { base.write(pos); delay(15);}
// base.write((int)theta1);
// front();
 gripopen();
 delay(300);
 front();
 delay(300);
 gripclose();
 delay(300);
 back();
 for(pos = 20; pos < (int)angle; pos += 1)   
  { base.write(pos); delay(15);}
 //base.write((int)angle);
 front();
 delay(300);
 gripopen();
 delay(300);
 back();
 delay(300);
 gripclose();
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
 
  }
