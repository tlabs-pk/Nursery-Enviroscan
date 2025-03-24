#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"

#include <WiFiUdp.h>
#include <NTPClient.h>

// NTP Client settings
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "asia.pool.ntp.org", 18000, 60000); // 18000 seconds offset for Pakistan Standard Time

#include <Callmebot_ESP8266.h>
String phoneNumber = "Add Phone Number given to CallmeBot here";
String apiKey = "Add API Key given by Callmebot here";
String lowTmsg = "Alert! Low Temperature in Nursery";
String highTmsg = "Alert! High Temperature in Nursery";
String highHmsg = "Alert! High Humidity in Nursery";
String highLmsg = "Alert! High Lighting in Nursery";
String welcomemsg = "Nursery EnviroScan is turned ON.";

#include <Arduino.h>
#include <string>
#include <vector>
#include "GoogleFormPost.h"
#define FORM_ROOT_URL "Add google form URL here"
bool postOnce;

int LDRVALUE;

#define buzzerBeep D6
#define led D5


unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
const unsigned long interval = 900000; // 15 minutes in milliseconds

#define OLED_RESET -1
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define DHTPIN D7      // Pin where the DHT22 is connected
#define DHTTYPE DHT22  // Define the type of sensor used (DHT22)
#define WIFI_SSID "Add wifi SSID here" // Your Wi-Fi SSID
#define WIFI_PASSWORD "Add password here" // Your Wi-Fi Password

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  pinMode(buzzerBeep, OUTPUT);

  pinMode(led, OUTPUT);
  
  digitalWrite(buzzerBeep, HIGH); //BUZZER TEST
  delay(50);
  digitalWrite(buzzerBeep, LOW);
  delay(50); 

  digitalWrite(led, HIGH);
  delay(100); 
  digitalWrite(led, LOW);
    delay(100); 
 digitalWrite(led, HIGH);
  delay(100); 
  digitalWrite(led, LOW);
    delay(100); 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 

   display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 21);
  display.println("Nursery");
  display.setCursor(0, 42);
  display.println("EnviroScan");
  display.display();
  delay(4000);

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Tasleem");
  display.setCursor(0, 21);
  display.println("Labs");
  display.setCursor(0, 41);
  display.println("Pakistan");

  display.display();
  delay(2000);
  display.clearDisplay();

  // Initialize DHT22 sensor
  dht.begin();
  Serial.println("DHT22 sensor initialization complete.");

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
   display.setTextSize(2);
   display.setCursor(0, 0);
  display.println("Connecting");
  display.setCursor(0, 21);
  display.println("to");
  display.setCursor(0, 41);
  display.println("WiFi");
  display.display();

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");

    digitalWrite(buzzerBeep, HIGH); //BUZZER TEST
  delay(50);
  digitalWrite(buzzerBeep, LOW);
  delay(50);  


  // Initialize NTP Client for local time update according to PST
  timeClient.begin();

Callmebot.begin(); //Whatsapp messaging capability begin
Callmebot.whatsappMessage(phoneNumber, apiKey, welcomemsg);

  Serial.println(WiFi.localIP());

  postOnce = true;
  
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("WiFi");
  display.setCursor(0, 21);
  display.println("connected");
  display.setCursor(0, 41);
  display.setTextSize(1);
  display.print("IP: ");
  display.println(WiFi.localIP());
  display.display();
  delay(2000);
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");

  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("Humidity ");
  display.setCursor(0, 24);
  display.print(humidity);
  display.println(" %");
  display.display();
  delay(3500);

  display.clearDisplay();
  display.setCursor(0, 21);
  display.setTextSize(1);
  display.print("TEMPERATURE ");
  display.setTextSize(2);
  display.setCursor(0, 41);
  display.print(temperature);
  display.println(" *C");
  display.display();
  delay(3500);

  LDRVALUE = analogRead(A0);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.print("Ambient");
  display.setCursor(0, 21);
  display.setTextSize(2);
  display.print("Light ");
  display.setCursor(0, 41);
  display.print(LDRVALUE);
  display.display();
  delay(3500);

  timeClient.update();
    // Get current time
  String formattedTime = timeClient.getFormattedTime();


  
  // Display time on OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.print("Time: ");
  display.setCursor(0, 41);
  display.print(formattedTime);
  display.display();

  delay(3500);


if (temperature < 25 || temperature > 28 || humidity > 80) {
    digitalWrite(buzzerBeep, HIGH);
    delay(50);
    digitalWrite(buzzerBeep, LOW);
    delay(50);

  if (humidity > 80) {
     
        digitalWrite(led, HIGH);
        delay(50);
        digitalWrite(led, LOW);
        delay(50);
        display.clearDisplay();
        display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("HIGH");
    display.setCursor(0, 21);
  display.print("HUMIDITY");
  digitalWrite(led, HIGH);
        delay(50);
        digitalWrite(led, LOW);
        delay(50);
        digitalWrite(led, HIGH);
        delay(50);
        digitalWrite(led, LOW);
        delay(50);
        digitalWrite(led, HIGH);
        delay(50);
        digitalWrite(led, LOW);
        delay(50);
    }

    if (temperature < 25) {
  
        digitalWrite(led, HIGH);
        delay(50);
        digitalWrite(led, LOW);
        delay(50);
        display.clearDisplay();
  
  display.setCursor(0, 21);
   display.setTextSize(1);
  display.print("LOW TEMPERATURE");
   display.display();
  digitalWrite(led, HIGH);
        delay(50);
        digitalWrite(led, LOW);
        delay(50);
        digitalWrite(led, HIGH);
        delay(50);
        digitalWrite(led, LOW);
        delay(50);
        digitalWrite(led, HIGH);
        delay(50);
        digitalWrite(led, LOW);
        delay(3000);
    }

     if (temperature > 28) {
       
        digitalWrite(led, HIGH);
        delay(50);
        digitalWrite(led, LOW);
        delay(50);
        display.clearDisplay();
  display.setCursor(0, 21);
  display.print("HIGH TEMPERATURE");
   display.display();
  digitalWrite(led, HIGH);
        delay(50);
        digitalWrite(led, LOW);
        delay(50);
        digitalWrite(led, HIGH);
        delay(50);
        digitalWrite(led, LOW);
        delay(50);
        digitalWrite(led, HIGH);
        delay(50);
        digitalWrite(led, LOW);
        delay(3000);
    }

if (humidity > 80) {
        
        digitalWrite(led, HIGH);
        delay(50);
        digitalWrite(led, LOW);
        delay(50);
        display.clearDisplay();
  display.setCursor(0, 21);
  display.print("HIGH HUMIDITY");
   display.display();
  digitalWrite(led, HIGH);
        delay(50);
        digitalWrite(led, LOW);
        delay(50);
        digitalWrite(led, HIGH);
        delay(50);
        digitalWrite(led, LOW);
        delay(50);
        digitalWrite(led, HIGH);
        delay(50);
        digitalWrite(led, LOW);
        delay(3000);
    }


   // Check if current time is between 20:00:00 and 08:00:00
  bool isNightTime = (formattedTime >= "20:00:00" || formattedTime < "08:00:00");

  // Beep if conditions are met
  if (isNightTime && LDRVALUE > 600) {
        
        
            digitalWrite(buzzerBeep, HIGH);
    delay(50);
    digitalWrite(buzzerBeep, LOW);
    delay(50);
            digitalWrite(led, HIGH);
            delay(50);
            digitalWrite(led, LOW);
            delay(50);
            display.clearDisplay();
            display.setCursor(0, 21);
            display.print("HIGH LIGHT");
            display.display();
            display.setCursor(0, 41);
            display.print("IN ROOM");
            display.display();
            digitalWrite(led, HIGH);
            delay(50);
            digitalWrite(led, LOW);
            delay(50);
            digitalWrite(led, HIGH);
            delay(50);
            digitalWrite(led, LOW);
            delay(50);
            digitalWrite(led, HIGH);
            delay(50);
            digitalWrite(led, LOW);
            delay(3000);
        



}


currentMillis = millis();

if (currentMillis - previousMillis >= interval)
{ previousMillis = currentMillis;

  if (postOnce) {
        GoogleFormPost gf;
        gf.setDebugMode(true);
        gf.setFormUrl(String(FORM_ROOT_URL));
               
        gf.reset();
        gf.setFormUrl(String(FORM_ROOT_URL));
        gf.addData(String(temperature) , String("entry.865528716"));
        gf.addData(String(humidity) , String("entry.1991991600"));
        gf.addData(String(LDRVALUE) , String("entry.529907439"));

if (temperature > 28) {
gf.addData(String("Yes") , String("entry.1210753571"));
Callmebot.whatsappMessage(phoneNumber, apiKey, highTmsg);
}

if (temperature < 25) {
gf.addData(String("Yes") , String("entry.1227030553"));
Callmebot.whatsappMessage(phoneNumber, apiKey, lowTmsg);
}

if (humidity > 80) {
gf.addData(String("Yes") , String("entry.429669119"));
Callmebot.whatsappMessage(phoneNumber, apiKey, highHmsg);
}

if (isNightTime && LDRVALUE > 600) {
gf.addData(String("Yes") , String("entry.415165666"));
Callmebot.whatsappMessage(phoneNumber, apiKey, highLmsg);
}


        gf.showDebug();
        gf.send();
        postOnce = true;
        delay(2000);



    }
}

}

}
