@@ -0,0 +1,73 @@
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "smLenIPAygho5hV88UGBU4E0g08G4Ukn";
char ssid[] = "iPhone";
char pass[] = "asd12345";

const int DHTPIN = D4;      
const int DHTTYPE = DHT11;

DHT dht(DHTPIN, DHTTYPE);
int status;

int buzzer = D6;

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display

void setup() {
  lcd.init();
  lcd.clear();     
  dht.begin();    
  lcd.backlight();
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  Blynk.virtualWrite(V0, 0);
  Blynk.virtualWrite(V1, 0);
  Blynk.virtualWrite(V2, 0);
}

BLYNK_WRITE(V0)
{
  status = param.asInt();
}

void loop() {
  Blynk.run();
  lcd.clear(); 
  if (status == 1)
  {
    float h = dht.readHumidity();    
    float t = dht.readTemperature();
     Serial.print("Nhiet do: ");
    Serial.println(t);               
    Serial.print("Do am: ");
    Serial.println(h);  
    lcd.setCursor(0,0);
    lcd.print("Nhiet do : ");
    lcd.print(h);
    lcd.setCursor(0,1);
    lcd.print("Do am    : ");
    lcd.print(t);
    if (t > 30)
    {
      tone(buzzer, 1000);t
    }
    else
    {
      noTone(buzzer);
    }
    Blynk.virtualWrite(V1, t);
    Blynk.virtualWrite(V2, h);
    Blynk.virtualWrite(V3, );
    
    delay(1000);
  }
  else
  {
    Blynk.virtualWrite(V1, 0);
    Blynk.virtualWrite(V2, 0);
    Blynk.virtualWrite(V3, 0);
  }
}
