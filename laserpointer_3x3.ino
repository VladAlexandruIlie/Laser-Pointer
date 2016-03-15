
#include <Servo.h> 
#include <string.h>
String readString, searching;
Servo bot,top;
int commaIndex;
int n,m,readPos=0, readPos2=0;
int pos_x[3] = {45, 90, 135};
int pos_y[3] = {45, 90, 135};
  const char* items[][10] = 
    {
     { "a11,b11,", "a12,b12,", "a13,b13," },
     { "a21,b21,", "a22,b22,", "a23,b23," },
     { "a31,b31,", "a32,b32,", "a33,b33," }
    };

void setup()
 {
  Serial.begin(9600);
  bot.attach(9);                   // the pin for the bottom servo control = pan servo motor
  top.attach(8);                   // the pin for the top servo motor = tilt servo motor
 }

void loop ()
 {
  
   ReadPositions();
   SerialRead(); 
   
   }

void ReadPositions()
 {
  byte pos_x[3] = {45,90,135};
  byte pos_y[3] = {45,90,135};
 
  int i=0,j=0;
  byte x,y;
  
  if (readPos==0) 
   { 
     Serial.print("Box position matrix:"); Serial.print('\n');
     for ( i=0; i< 3; i+=1)
        { for( j=0; j< 3; j+=1) 
              { x=pos_x[i];
                y=pos_y[j];
                Serial.print(x, DEC);
                Serial.print(".");
                Serial.print(y, DEC);
                Serial.print("  ");
                }
         Serial.write('\n');
        }       
    readPos=1;
    Serial.print('\n');
    }
    delay(100);  
    if (readPos2==0) 
       { 
        Serial.print("Box description / items:"); Serial.print('\n');
        for ( i=0; i< 3; i+=1)
           { for( j=0; j< 3; j+=1) 
                {
                 Serial.print(items[i][j]); 
                 if (j!=2)Serial.print(" ; ");
                 }
            Serial.write('\n');
            }       
        readPos2=1;
        Serial.write('\n');
        }
 }

void SerialRead()
 {
  byte x,y;
  int i,j,l=0,l1,l2;
  
  while (Serial.available())
       {
         if (Serial.available() >0) 
            {
             char c = Serial.read();         //gets one byte from serial buffer
             readString += c;                //makes the string readString
             } 
        }
 
  int commaIndex = readString.indexOf(' ');
  String firstValue = readString.substring(0, commaIndex);
  String secondValue = readString.substring(commaIndex+1, readString.length());
  int n = firstValue.toInt(); 
  int m = secondValue.toInt();
  
 if (readString.length() >0 && n!=0 && m!=0 ) 
   {
    //n = constrain(n, 35, 155);
    //m = constrain(m, 25, 145);   
    
    bot.write(0);
    delay(100);               
    top.write(0);
    delay(500);
    
    int x=n, y=m;
    
    Serial.print("Moving laser to position: "); Serial.print (x); Serial.print("."); Serial.print(y); Serial.print('\n'); Serial.print('\n');
    
    for(i=0;i<=x;i+=1)
            {
              bot.write(i);
              delay(5);
              }   
                 
    for(j=0;j<=y;j+=1)
            {
              top.write(j);
              delay(5);
              }  
    
    readString="";
    } 
   
  else if (readString.length() >0)
   {  
    int sw=1, sw2=0, ok=0;    
    readString.remove(readString.length()-1);

    int l1=readString.length();
      
    Serial.print ("Looking for item:." ); Serial.print (readString); Serial.print("."); Serial.print('\n');
    for ( i=0; i< 3 && sw2==0 ; i+=1)
       { for( j=0; j< 3 && sw2==0; j+=1) 
              { 
                String t = items[i][j];   //Serial.print("Processing string: ");  Serial.print(t);   Serial.print('\n');
                while (t != "" && sw2==0)
                  {   
                    l=0; sw=1;
                    commaIndex = t.indexOf(',');
                    String firstValue = t.substring(0, commaIndex);
                    int l2=firstValue.length();               
                    while(sw==1 && l1==l2 && l<=l1) 
                            {   
                              if (readString[l] != firstValue[l]) {sw=0;}
                              l++;
                              }
                    if(sw==1) ok=1;
                    
                    if (ok==1) 
                        { 
                          ok=0;
                          sw2=1;
                          n=i;
                          m=j;
                          Serial.print("String: "); Serial.print(readString); Serial.print(" was found at location "); Serial.print(n);Serial.print("."); Serial.print(m); Serial.print('\n');
                          }
                     t = t.substring(commaIndex+1, t.length());                      
                     }
                }
            delay(10);               
          }
    if (sw2==1)                             
    {
      x=pos_x[n];
      y=pos_y[m];
      
      bot.write(0);               
      top.write(0);
      //int x=n, y=m;
    
      Serial.print("Moving laser to position: "); Serial.print (x); Serial.print("."); Serial.print(y); Serial.print('\n'); Serial.print('\n');
    
      for(i=0;i<=x;i+=1)
            {
              bot.write(i);
              delay(5);
              }   
                 
      for(j=0;j<=y;j+=1)
            {
              top.write(j);
              delay(5);
              }  


      
    }
    else { Serial.print("Item not found !!! ");  Serial.write('\n');  Serial.write('\n'); }
      
      
    readString="";
    } 
}

















