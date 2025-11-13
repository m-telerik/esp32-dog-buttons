// lib/Buttons/Buttons.cpp
#include "Buttons.h"
#include "Audio.h"

ButtonConfig ButtonManager::_buttons[ButtonManager::MAX_BUTTONS];
uint8_t ButtonManager::_count = 0;

int ButtonManager::_buttonStates[ButtonManager::MAX_BUTTONS];
int ButtonManager::_lastButtonStates[ButtonManager::MAX_BUTTONS];
unsigned long ButtonManager::_lastDebounceTimes[ButtonManager::MAX_BUTTONS];

ButtonCallback ButtonManager::_callback = nullptr;

void ButtonManager::init() {
    _count = 0;
    _callback = nullptr;
    
    for (uint8_t i = 0; i < MAX_BUTTONS; i++) {
        _buttonStates[i] = HIGH;
        _lastButtonStates[i] = HIGH;
        _lastDebounceTimes[i] = 0;
    }
    
    Serial.println("[Buttons] Initialized");
}

void ButtonManager::addButton(ButtonConfig config) {
    if (_count >= MAX_BUTTONS) {
        Serial.printf("[Buttons] Error: Maximum %d buttons reached!\n", MAX_BUTTONS);
        return;
    }
    
    _buttons[_count] = config;
    pinMode(config.pin, INPUT_PULLUP);
    
    _buttonStates[_count] = HIGH;
    _lastButtonStates[_count] = HIGH;
    _lastDebounceTimes[_count] = 0;
    
    Serial.printf("[Buttons] Added button #%d: pin=%d, word='%s', webhookId='%s'\n",
                  _count, config.pin, config.word, config.webhookId);
    
    _count++;
}

void ButtonManager::setCallback(ButtonCallback callback) {
    _callback = callback;
}

void ButtonManager::update() {
    for (uint8_t i = 0; i < _count; i++) {
        // Читаем текущее состояние кнопки
        int reading = digitalRead(_buttons[i].pin);
        
        // Если состояние изменилось, сбрасываем таймер антидребезга
        if (reading != _lastButtonStates[i]) {
            _lastDebounceTimes[i] = millis();
        }
        
        // Если прошло достаточно времени после последнего изменения
        if ((millis() - _lastDebounceTimes[i]) > _buttons[i].debounce) {
            // Если состояние стабилизировалось и отличается от текущего
            if (reading != _buttonStates[i]) {
                _buttonStates[i] = reading;
                
                // Если кнопка нажата (переход HIGH -> LOW)
                if (_buttonStates[i] == LOW) {
                    Serial.printf("[Buttons] Button #%d pressed: '%s' (webhookId: '%s')\n",
                                  i, _buttons[i].word, _buttons[i].webhookId);
                    
                    // Играем звук
                    Audio::playSound(_buttons[i].sound);
                    
                    // Вызываем callback если установлен
                    if (_callback != nullptr) {
                        _callback(_buttons[i].webhookId, _buttons[i].word);
                    }
                }
            }
        }
        
        // Сохраняем последнее считанное значение
        _lastButtonStates[i] = reading;
    }
}

uint8_t ButtonManager::getCount() {
    return _count;
}

void ButtonManager::printAll() {
    Serial.println("\n=== Button Configuration ===");
    for (uint8_t i = 0; i < _count; i++) {
        Serial.printf("Button #%d:\n", i);
        Serial.printf("  Pin: GPIO%d\n", _buttons[i].pin);
        Serial.printf("  Word: '%s'\n", _buttons[i].word);
        Serial.printf("  WebhookId: '%s'\n", _buttons[i].webhookId);
        Serial.printf("  Sound: %s\n", Sounds::getName(_buttons[i].sound));
        Serial.printf("  Debounce: %lu ms\n", _buttons[i].debounce);
    }
    Serial.println("============================\n");
}