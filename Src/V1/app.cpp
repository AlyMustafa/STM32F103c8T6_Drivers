#include "app.h"
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

#define BOTtoken "6789606163:AAH_zVPd0x06JRnBW2TtV8cBu7DKu26fufI" // Enter the bottoken you got from botfather
#define CHAT_ID "5335070779"  
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
const char* ssid = "OPPO Reno5"; // Replace with your Wi-Fi SSID
const char* password = "50005000"; // Replace with your Wi-Fi password
const int voltagepin = 36;

#define Buzzer 23
#define Max_Volt  7.4             //define max voltage as 5 volts
#define Min_Volt  2.5           //define min voltage as 2.5 volts

// ================================================================
// ===                    GLOBAL VARIABLES                     ===
// ================================================================
float distance;
float Yaw;
float Pitch;
float Roll;
bool Open_Counter = 1;
bool Fall_Counter = 1;
bool Battery_Counter = 1;
//LCD_INIT
const int rs = 25, en = 26, d4 = 13, d5 = 12, d6 = 14, d7 = 27;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void app_init()
{
  pinMode(voltagepin, INPUT); // Set the analog pin as input
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  configTime(0, 0, "pool.ntp.org");

  // Wi-Fi setup
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
  }
  bot.sendMessage(CHAT_ID, "Wifi Connected!", "");
  bot.sendMessage(CHAT_ID, "System has Started!!", "");
  //Buzzer init
  pinMode(Buzzer, OUTPUT);
  //MPU6050 init
  mpu_init();
  //UltraSonic init
  UltraSonic_init();
  //LCD init  
  lcd.begin(16, 2);
  lcd.clear();
  //LCD_init();
}


// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

void app_Start()
{
  Battery_Function ();
  checkBox_isOpened();
  checkBox_hasFalled();
  //checkBox_isOpened_AND_Falled();
}

char checkBox_isOpened()
{
distance = Ultrasonic_get_distance();
if ( distance < 19 ){
    Open_Counter = 1;
    digitalWrite(Buzzer, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Box is Safe!!");
    return 0;
  }
  
  else {
    //Send alarm
    digitalWrite(Buzzer, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Box is Opened!!");
    while ( Open_Counter == 1 ){
      Open_Counter = 0;
      bot.sendMessage(CHAT_ID, "Box is open!", "");
    }
    // lcd.setCursor(0, 1); 
    // lcd.print("                ");
    //lcd.print(distance);
    return 1;
  }
}
char checkBox_hasFalled(){
   mpu_Update();
    //Serial.print("Yaw:\t");
  Yaw   =  mpu_get_Yaw();
    //Serial.print("  Pitch:\t");
  Pitch =  mpu_get_Pitch();
    //Serial.print("  Roll:\t");
  Roll  =  mpu_get_Roll();

  if( (Pitch > 25) || (Pitch < -25) || (Roll > 25) || (Roll < -25))
  {
    lcd.setCursor(0, 1);
    lcd.print("Box has Fallen!!");
    digitalWrite(Buzzer, HIGH);
     //lcd.setCursor(0, 0); 
     //lcd.print("                ");
     while ( Fall_Counter == 1 ){
      Fall_Counter = 0;
      bot.sendMessage(CHAT_ID, "Box has fallen!", "");
    }
    return 1;
  }
  else{
    Fall_Counter = 1;
    lcd.setCursor(0, 1);
    lcd.print("                ");
  }
  return 0;
}

void Battery_Function (void){
  // start conversion on analog pin
  int sensorValue = analogRead(voltagepin);
  // convert input to the equ. volt 
  float voltage = sensorValue * (3.3 / 4095.0); 
  // get the input voltage
  float Vin = voltage * 2;
  Vin = 0.94 * Vin;
  // calculate the percentage 
  float batteryPercentage = (abs(Vin - Min_Volt )/ (Max_Volt - Min_Volt)) * 100;    //vin = 2.5v --> (0 /2.5)*100 = 0% 
                                                                                 //vin = 5v --> (2.5 /2.5)*100 = 100% 
                                                                                 //vin = 3v --> (0.5 /2.5)*100 = 20% 
  Serial.print("Battery Percentage: ");
  Serial.println(batteryPercentage);
  Serial.print("%");    
  if ( batteryPercentage <= 20.0 ){
    /*while ( Battery_Counter == 1 ){
      Battery_Counter = 0;
      bot.sendMessage(CHAT_ID, "Charge the battery!", "");
      lcd.print("Charge the battery");
    }*/
  }
  else {
    Battery_Counter = 1;
  }
  delay(1000);
}