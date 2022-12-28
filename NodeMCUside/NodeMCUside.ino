#include <ESP8266WiFi.h>;
#include <WiFiClient.h>;
#include <ThingSpeak.h>;
#include <math.h>;
#define max_lux 250
                                                  //to connect to Thingspeak channel
WiFiClient client;
unsigned long myChannelNumber = 1802546;                  //channel ID
const char* myWriteAPIKey = "EV3JC25NL5RZWFKZ";           // the Write API Key
const char* ssid = "11B69_MaxisBroadband";                //WiFi name
const char* password = "69744040";                       //WiFI password
const char* server = "api.thingspeak.com";

int ldr = A0;
int led1 = 12; //D6
int led2 = 13; //D7
int pir1 = 5; //D1
int pirState1;
int ldrValue;
int motionstate; 
int i; 
float lux;

void setup()
{
  pinMode(pir1, INPUT);
  pinMode(ldr, INPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  Serial.begin(9600);
  
  delay(10);
  ThingSpeak.begin(client);
  WiFi.begin(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

void loop()
{
  ldrValue = analogRead(ldr);
  lightIntensityLow();
  lightIntensityHigh();

  Serial.println("_________________");
  Serial.print("Brightness Sensor: "); 
  Serial.println(ldrValue); 
  Serial.println(); 
  delay(150); 
  
  

  if (ldrValue == 1024)
  {
    Serial.println("_____________________");
    Serial.print("Maximum LDR, lux limit: ");
    Serial.print(max_lux);
    Serial.println();
    ThingSpeak.writeField(myChannelNumber, 4,max_lux, myWriteAPIKey);
    delay(500); 
    }
    
    else 
    {
    Serial.print("Calculating illuminance... ");
    Serial.println();
    delay(500); 
    }

    
  float volt_ldr = ldrValue * (3.3 / 1024);         //voltage across LDR
  Serial.println();
  Serial.print("Voltage form of LDR: ");
  Serial.print("");
  Serial.print(volt_ldr);
  Serial.println("");

  float R_ldr = (33000 / volt_ldr) - 10000; 
   Serial.println("____________________");
  Serial.print("Resistance form of LDR: ");
  Serial.print(R_ldr);
  Serial.println();
  
  float lux = (pow(R_ldr, -0.78)) * (pow(10, 3.934));
  Serial.println("________________________");
  Serial.print("Calculated Illuminance, Lux: ");
  Serial.print(lux);
  Serial.println();

  ThingSpeak.writeField(myChannelNumber, 1,pirState1, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 2,ldrValue, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 3,volt_ldr, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 4,lux, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 5,R_ldr, myWriteAPIKey);
}


void lightIntensityLow()
{
  if (ldrValue < 600)  //dark
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    Serial.println("Dark Condition! | Light On! ");
    delay(1000);
  }
}


void lightIntensityHigh()
{
 if (ldrValue >= 600) //ldrValue > 600
 {
    pirState1 = digitalRead(pir1);
    if (pirState1 == HIGH) 
    {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      Serial.println("_______________________");
      Serial.println("Motion detected PIR 1| Light On!");
      delay(1000);
    }
    
    else  // pirState == LOW
   {
     digitalWrite(led1, LOW);
     digitalWrite(led2, LOW);
     Serial.println("_______________________");
     Serial.println("Motion absent from PIR 1| Light Off! ");
     delay(1000);
    }
  }
}
