#include <SoftwareSerial.h>

SoftwareSerial nodemcu(2,3);


int pir2 = 8; 
int pir3 = 9;

int pirState2;
int pirState3;
int ldrValue;
int count = 0;



void setup()
{
  pinMode(pir2, INPUT);
  pinMode(pir3, INPUT);


  
  Serial.begin(9600); 
  nodemcu.begin(9600);

}

void loop()
{
  if(digitalRead(pir2)==1)
  {
    delay(2500);
    count++;

    Serial.print("PEOPLE INSIDE:   ");
    Serial.println(count);
  }
  
  
  else
  if(digitalRead(pir3)==1)
  {
    delay(2500);
    count--;
    
    if (count < 0)
    {
      count = 0;
    }
    

    Serial.print("PEOPLE INSIDE:   ");
    Serial.println(count);
  }
}
