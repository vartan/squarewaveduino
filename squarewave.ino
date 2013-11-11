#include <stdlib.h> // for the atol() function
unsigned long frequency = 5;
int mode=0;
long halfPeriod;
String content = "";
void setup() {
  pinMode(2,OUTPUT);
  halfPeriod = 500000/frequency;
  Serial.begin(9600);

}
void loop() {  
  while(Serial.available()) {
      char c = Serial.read();
      content.concat(c);
      delay(2);
  }
  if (content != "") {
    content.toLowerCase();
    content.replace("k","000");
    content.replace("m","000000");
    char a[content.length()+1];
    content.toCharArray(a, content.length()+1) ;
    frequency = atol(a);
    if(frequency>500000) {
      Serial.print("Frequency cannot exceed 500KHz");
      content="";
      return;
    }
    Serial.println("Now outputting "+content+"hz");
    halfPeriod = 500000/frequency;
    content="";
  }
  mode=(mode+1)%2;
  digitalWrite(2,mode);
  if(halfPeriod<16383) //max value of delayMicroseconds
    delayMicroseconds(halfPeriod);
  else
    delay(halfPeriod/1000);
  

}
