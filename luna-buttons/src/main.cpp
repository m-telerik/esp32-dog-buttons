#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "driver/i2s.h"
#include <math.h>
#include "config.h"   // содержит WIFI_SSID и WIFI_PASS

const int I2S_BCLK = 9;   // ESP32-C3 -> MAX98357 BCLK
const int I2S_LRC  = 10;  // ESP32-C3 -> MAX98357 LRC/WS
const int I2S_DIN  = 8;   // ESP32-C3 -> MAX98357 DIN
const int BUTTON_PIN = 6; // пин кнопки

const char* WEBHOOK_URL = "https://n8n.bynau.me:5678/webhook/buttons";

void i2sInit() {
  i2s_config_t cfg = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
    .sample_rate = 22050,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,
    .intr_alloc_flags = 0,
    .dma_buf_count = 6,
    .dma_buf_len = 256,
    .use_apll = false,
    .tx_desc_auto_clear = true,
    .fixed_mclk = 0
  };
  i2s_pin_config_t pins = {
    .bck_io_num = I2S_BCLK,
    .ws_io_num  = I2S_LRC,
    .data_out_num = I2S_DIN,
    .data_in_num  = I2S_PIN_NO_CHANGE
  };
  i2s_driver_install((i2s_port_t)0, &cfg, 0, NULL);
  i2s_set_pin((i2s_port_t)0, &pins);
  i2s_zero_dma_buffer((i2s_port_t)0);
}

void beep(uint32_t f=1200, uint32_t ms=250, uint32_t sr=22050) {
  const size_t N=256; int16_t buf[N];
  double ph=0, step=2.0*M_PI*f/sr;
  size_t total=(sr*ms)/1000, sent=0;
  while(sent<total){
    size_t n = min(N, total-sent);
    for(size_t i=0;i<n;i++){ buf[i]=(int16_t)(sin(ph)*16000); ph+=step; if(ph>2*M_PI) ph-=2*M_PI; }
    size_t w=0; i2s_write((i2s_port_t)0, buf, n*sizeof(int16_t), &w, portMAX_DELAY);
    sent+=n;
  }
}

void sendWebhook() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(WEBHOOK_URL);
    http.addHeader("Content-Type", "application/json");

    String payload = "{\"event\":\"button_pressed\"}";
    int httpCode = http.POST(payload);

    Serial.printf("Webhook status: %d\n", httpCode);
    http.end();
  } else {
    Serial.println("WiFi not connected, cannot send webhook");
  }
}

void connectWiFi() {
  Serial.printf("Connecting to %s...\n", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  int retry = 0;
  while (WiFi.status() != WL_CONNECTED && retry < 30) {
    delay(500);
    Serial.print(".");
    retry++;
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.printf("\nConnected! IP: %s\n", WiFi.localIP().toString().c_str());
  } else {
    Serial.println("\nFailed to connect to WiFi");
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Booting...");
  i2sInit();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  connectWiFi();
  Serial.println("Ready");
}

void loop() {
  static bool prevState = HIGH;
  static unsigned long lastPress = 0;
  bool state = digitalRead(BUTTON_PIN);

  // защита от дребезга и удержания
  if (prevState == HIGH && state == LOW && millis() - lastPress > 500) {
    Serial.println("Button pressed");
    beep(800, 150);
    sendWebhook();
    lastPress = millis();
  }

  prevState = state;
  delay(20);
}