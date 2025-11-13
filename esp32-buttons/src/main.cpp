#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "driver/i2s.h"
#include <math.h>
#include "config.h" // WIFI_SSID, WIFI_PASSWORD, WEBHOOK_URL

const int I2S_BCLK = 9;
const int I2S_LRC = 10;
const int I2S_DIN = 8;
const int BUTTON_PIN = 6;

int lastButtonState = HIGH;
int buttonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

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
        .ws_io_num = I2S_LRC,
        .data_out_num = I2S_DIN,
        .data_in_num = I2S_PIN_NO_CHANGE
    };
    
    i2s_driver_install((i2s_port_t)0, &cfg, 0, NULL);
    i2s_set_pin((i2s_port_t)0, &pins);
    i2s_zero_dma_buffer((i2s_port_t)0);
}

void beep(uint32_t f = 1200, uint32_t ms = 250, uint32_t sr = 22050) {
    const size_t N = 256;
    int16_t buf[N];
    double ph = 0;
    double step = 2.0 * M_PI * f / sr;
    size_t total = (sr * ms) / 1000;
    size_t sent = 0;
    
    while (sent < total) {
        size_t n = (N < (total - sent)) ? N : (total - sent);
        for (size_t i = 0; i < n; i++) {
            buf[i] = (int16_t)(sin(ph) * 16000);
            ph += step;
            if (ph > 2 * M_PI) ph -= 2 * M_PI;
        }
        size_t w = 0;
        i2s_write((i2s_port_t)0, buf, n * sizeof(int16_t), &w, portMAX_DELAY);
        sent += n;
    }
}

void connectWiFi() {
    Serial.printf("Connecting to WiFi: %s\n", WIFI_SSID);
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        Serial.print(".");
        attempts++;
    }
    Serial.println();
    
    if (WiFi.status() == WL_CONNECTED) {
        Serial.printf("WiFi Connected! IP: %s\n", WiFi.localIP().toString().c_str());
    } else {
        Serial.println("WiFi connection failed!");
    }
}

void sendWebhook(String buttonId) {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi not connected, skipping webhook");
        return;
    }
    
    HTTPClient http;
    http.begin(WEBHOOK_URL);
    http.addHeader("Content-Type", "application/json");
    http.setTimeout(5000);
    
    String payload = "{\"event\":\"button_pressed\",\"button\":\"" + buttonId + "\"}";
    int httpCode = http.POST(payload);
    
    if (httpCode > 0) {
        Serial.printf("Webhook sent! HTTP code: %d\n", httpCode);
    } else {
        Serial.printf("Webhook failed: %s\n", http.errorToString(httpCode).c_str());
    }
    
    http.end();
}

void setup() {
    Serial.begin(115200);
    delay(3000);
    
    Serial.println("\n\n=================================");
    Serial.println(" ESP32-C3 Button Controller");
    Serial.println("=================================");
    
    Serial.println("[1/3] Initializing I2S...");
    i2sInit();
    Serial.println(" I2S OK!");
    
    Serial.println("[2/3] Setting up button...");
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    Serial.printf(" Button: GPIO%d\n", BUTTON_PIN);
    
    Serial.println("[3/3] Testing beep...");
    beep(1000, 300);
    delay(400);
    beep(600, 300);
    
    Serial.println("[4/4] Connecting to WiFi...");
    connectWiFi();
    
    Serial.println("=================================");
    Serial.println(" READY!");
    Serial.println("=================================");
    Serial.println("Press button to hear beep...\n");
}

void loop() {
    static unsigned long lastPrint = 0;
    
    // Heartbeat каждые 5 секунд
    if (millis() - lastPrint > 5000) {
        Serial.printf("[%lu sec] WiFi: %s, Button: %d\n",
                     millis() / 1000,
                     WiFi.status() == WL_CONNECTED ? "OK" : "FAIL",
                     digitalRead(BUTTON_PIN));
        lastPrint = millis();
    }
    
    // Читаем текущее состояние кнопки
    int reading = digitalRead(BUTTON_PIN);
    
    // Если состояние изменилось, сбрасываем таймер антидребезга
    if (reading != lastButtonState) {
        lastDebounceTime = millis();
    }
    
    // Если прошло достаточно времени после последнего изменения
    if ((millis() - lastDebounceTime) > debounceDelay) {
        // Если состояние стабилизировалось и отличается от текущего
        if (reading != buttonState) {
            buttonState = reading;
            // Если кнопка нажата (переход HIGH -> LOW)
            if (buttonState == LOW) {
                Serial.println(">>> BUTTON PRESSED <<<");
                beep(1000, 300);
                sendWebhook("button_1");
                Serial.println("Done!");
            }
        }
    }
    
    // Сохраняем последнее считанное значение
    lastButtonState = reading;
    delay(10);
}