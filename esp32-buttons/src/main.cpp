// src/main.cpp
#include <Arduino.h>
#include "driver/i2s.h"
#include <math.h>
#include "config.h"
#include <Network.h>        

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
    Network::connect(WIFI_SSID, WIFI_PASSWORD);  // Используем библиотеку!
    
    Serial.println("=================================");
    Serial.println(" READY!");
    Serial.println("=================================");
    Serial.println("Press button to hear beep...\n");
}

void loop() {
    static unsigned long lastPrint = 0;
    
    // Проверяем WiFi соединение
    Network::checkConnection();
    
    // Heartbeat каждые 5 секунд
    if (millis() - lastPrint > 5000) {
        Serial.printf("[%lu sec] WiFi: %s, Button: %d\n",
                     millis() / 1000,
                     Network::isConnected() ? "OK" : "FAIL",  // Используем библиотеку!
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
                Network::sendWebhook(WEBHOOK_URL, "button_1");  // Используем библиотеку!
                Serial.println("Done!");
            }
        }
    }
    
    // Сохраняем последнее считанное значение
    lastButtonState = reading;
    delay(10);
}