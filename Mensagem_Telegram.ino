#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// Dados do WiFi
#define WIFI_SSID ""
#define WIFI_PASSWORD ""
// Telegram BOT Token (Botfather)
#define BOT_TOKEN ""

// Use @myidbot (IDBot) para saber qual o seu ID
#define CHAT_ID ""

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

#define Sensor 4
bool flag = 1;

void setup() {

  pinMode(Sensor, INPUT);

  Serial.begin(115200);
  Serial.println();


  //conexão da rede:
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org");  // get UTC time via NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600) {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);

  bot.sendMessage(CHAT_ID, "Bot iniciou", "");//envia mensagem dizendo que iniciou o BOT
}

void loop() {

  int Porta = digitalRead(Sensor);


  if (Porta == 0) {
    if (flag) {
      Serial.println("Porta Aberta");
      bot.sendMessage(CHAT_ID, "Porta Aberta", "");
      flag = 0;
    }
  } else {
    flag = 1;
  }
}
