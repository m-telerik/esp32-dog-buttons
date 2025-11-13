// lib/Network/Network.cpp
#include "Network.h"
#include <WiFiClientSecure.h>

unsigned long Network::_lastCheckTime = 0;

bool Network::connect(const char* ssid, const char* password, int maxAttempts) {
    Serial.printf("[Network] Connecting to WiFi: %s\n", ssid);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < maxAttempts) {
        delay(500);
        Serial.print(".");
        attempts++;
    }
    Serial.println();
    
    if (WiFi.status() == WL_CONNECTED) {
        Serial.printf("[Network] WiFi Connected! IP: %s\n", WiFi.localIP().toString().c_str());
        return true;
    } else {
        Serial.println("[Network] WiFi connection failed!");
        return false;
    }
}

bool Network::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

void Network::checkConnection() {
    // Проверяем не чаще чем раз в 30 секунд
    if (millis() - _lastCheckTime < _checkInterval) {
        return;
    }
    _lastCheckTime = millis();
    
    if (!isConnected()) {
        Serial.println("[Network] Connection lost, reconnecting...");
        WiFi.reconnect();
    }
}

bool Network::sendWebhook(const char* url, const char* buttonId) {
    if (!isConnected()) {
        Serial.println("[Network] WiFi not connected, skipping webhook");
        return false;
    }
    
    // Формируем JSON payload
    String payload = "{\"event\":\"button_pressed\",\"button\":\"";
    payload += buttonId;
    payload += "\"}";
    
    return sendWebhookCustom(url, payload.c_str());
}

bool Network::sendWebhookCustom(const char* url, const char* jsonPayload) {
    if (!isConnected()) {
        Serial.println("[Network] WiFi not connected, skipping webhook");
        return false;
    }
    
    // Используем WiFiClientSecure для HTTPS
    WiFiClientSecure client;
    client.setInsecure(); // Отключаем проверку сертификата
    
    HTTPClient http;
    http.begin(client, url);
    http.addHeader("Content-Type", "application/json");
    http.setTimeout(5000);
    
    int httpCode = http.POST(jsonPayload);
    
    if (httpCode > 0) {
        Serial.printf("[Network] Webhook sent! HTTP code: %d\n", httpCode);
        http.end();
        return true;
    } else {
        Serial.printf("[Network] Webhook failed: %s\n", http.errorToString(httpCode).c_str());
        http.end();
        return false;
    }
}

String Network::getIP() {
    if (isConnected()) {
        return WiFi.localIP().toString();
    }
    return "Not connected";
}