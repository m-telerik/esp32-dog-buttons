// src/main.cpp
#include <Arduino.h>
#include "config.h"
#include "dictionary.h"
#include <Network.h>
#include <Audio.h>
#include <Buttons.h>

// Callback функция при нажатии кнопки
void onButtonPressed(const char* webhookId, const char* word) {
    Serial.printf("\n>>> BUTTON PRESSED: '%s' <<<\n", word);
    
    // Отправляем webhook
    Network::sendWebhook(WEBHOOK_URL, webhookId);
    
    Serial.println("Done!\n");
}

void setup() {
    Serial.begin(115200);
    delay(3000);
    
    Serial.println("\n\n=================================");
    Serial.println(" ESP32-C3 Dog Button System");
    Serial.println("=================================");
    
    // ========== 1. Инициализация Audio ==========
    Serial.println("[1/4] Initializing Audio...");
    Audio::init(I2S_BCLK, I2S_LRC, I2S_DIN);
    Serial.println(" Audio OK!");
    
    // ========== 2. Подключение к WiFi ==========
    Serial.println("[2/4] Connecting to WiFi...");
    Network::connect(WIFI_SSID, WIFI_PASSWORD);
    
    // ========== 3. Инициализация кнопок ==========
    Serial.println("[3/4] Setting up buttons...");
    ButtonManager::init();
    ButtonManager::setCallback(onButtonPressed);
    
    // Загружаем кнопки из словаря
    for (uint8_t i = 0; i < DICTIONARY_SIZE; i++) {
        if (DICTIONARY[i].enabled) {  // Только включенные кнопки
            ButtonManager::addButton({
                .pin = DICTIONARY[i].pin,
                .word = DICTIONARY[i].word,
                .webhookId = DICTIONARY[i].webhookId,
                .sound = DICTIONARY[i].sound,
                .debounce = BUTTON_DEBOUNCE_MS
            });
        }
    }
    
    Serial.printf(" Loaded %d buttons from dictionary\n", ButtonManager::getCount());
    
    // ========== 4. Тестовые звуки ==========
    Serial.println("[4/4] Testing audio...");
    Audio::playSound(SOUND_SUCCESS);
    delay(400);
    Audio::playSound(SOUND_BEEP_SHORT);
    
    // ========== Готово! ==========
    Serial.println("=================================");
    Serial.println(" SYSTEM READY!");
    Serial.println("=================================");
    
    // Показываем конфигурацию кнопок
    ButtonManager::printAll();
    
    Serial.println("Waiting for button press...\n");
}

void loop() {
    static unsigned long lastHeartbeat = 0;
    
    // Проверяем WiFi соединение
    Network::checkConnection();
    
    // Обновляем состояние кнопок
    ButtonManager::update();
    
    // Heartbeat каждые 5 секунд
    if (DEBUG_ENABLED && (millis() - lastHeartbeat > HEARTBEAT_INTERVAL)) {
        Serial.printf("[%lu sec] WiFi: %s, Buttons: %d\n",
                     millis() / 1000,
                     Network::isConnected() ? "OK" : "FAIL",
                     ButtonManager::getCount());
        lastHeartbeat = millis();
    }
    
    delay(10);
}