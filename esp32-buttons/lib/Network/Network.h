// lib/Network/Network.h
#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

class Network {
public:
    // Подключение к WiFi
    static bool connect(const char* ssid, const char* password, int maxAttempts = 20);
    
    // Проверка статуса подключения
    static bool isConnected();
    
    // Переподключение если соединение потеряно
    static void checkConnection();
    
    // Отправка webhook
    static bool sendWebhook(const char* url, const char* buttonId);
    
    // Отправка кастомного JSON payload
    static bool sendWebhookCustom(const char* url, const char* jsonPayload);
    
    // Получить IP адрес
    static String getIP();
    
private:
    static unsigned long _lastCheckTime;
    static const unsigned long _checkInterval = 30000; // 30 секунд
};