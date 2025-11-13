// lib/Buttons/Buttons.h
#pragma once
#include <Arduino.h>
#include "Sounds.h"

// Конфигурация одной кнопки
struct ButtonConfig {
    uint8_t pin;               // GPIO пин
    const char* word;          // Слово (для отладки)
    const char* webhookId;     // ID для webhook
    SoundType sound;           // Какой звук играть
    unsigned long debounce;    // Время антидребезга (мс)
};

// Callback функция при нажатии кнопки
typedef void (*ButtonCallback)(const char* webhookId, const char* word);

class ButtonManager {
public:
    // Инициализация
    static void init();
    
    // Добавить кнопку
    static void addButton(ButtonConfig config);
    
    // Установить callback для обработки нажатий
    static void setCallback(ButtonCallback callback);
    
    // Обновление состояния (вызывать в loop)
    static void update();
    
    // Получить количество добавленных кнопок
    static uint8_t getCount();
    
    // Распечатать все кнопки (для отладки)
    static void printAll();
    
private:
    static const uint8_t MAX_BUTTONS = 32;
    static ButtonConfig _buttons[MAX_BUTTONS];
    static uint8_t _count;
    
    // Состояния кнопок
    static int _buttonStates[MAX_BUTTONS];
    static int _lastButtonStates[MAX_BUTTONS];
    static unsigned long _lastDebounceTimes[MAX_BUTTONS];
    
    static ButtonCallback _callback;
};