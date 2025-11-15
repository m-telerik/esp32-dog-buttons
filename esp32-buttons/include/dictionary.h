// include/dictionary.h
#pragma once
#include "Sounds.h"

// Структура слова в словаре
struct ButtonWord {
    uint8_t pin;               // GPIO пин (для прямого подключения)
    const char* word;          // Слово/фраза (на английском или русском)
    const char* webhookId;     // ID для отправки в webhook (латиница, без пробелов)
    SoundType sound;           // Какой звук играть
    bool enabled;              // Включена ли кнопка
};

// ============================================
// СЛОВАРЬ КНОПОК
// ============================================
// Измените слова, пины и звуки под свои нужды
// webhookId должен быть на латинице, без пробелов

const ButtonWord DICTIONARY[] = {
    // === Пример: 2 кнопки на прямых пинах ===
    
    // Кнопка 1: "tug-o-war"
    {
        .pin = 1,                  // GPIO пин
        .word = "tug-o-war",         // Слово
        .webhookId = "tug-o-war",    // ID для webhook
        .sound = SOUND_TUG,       // Звук
        .enabled = true            // Включена
    },
    
    // Кнопка 2: "ball"
    {
        .pin = 2,                  // GPIO пин
        .word = "ball",            // Слово
        .webhookId = "ball",       // ID для webhook
        .sound = SOUND_BALL,       // Звук
        .enabled = true            // Включена
    },

    // Кнопка 3: "puzzle"
    {
        .pin = 3,                  // GPIO пин
        .word = "puzzle",            // Слово
        .webhookId = "puzzle",       // ID для webhook
        .sound = SOUND_PUZZLE,       // Звук
        .enabled = true            // Включена
    },
    
    // Кнопка 4: "play"
    {
        .pin = 4,                  // GPIO пин
        .word = "play",            // Слово
        .webhookId = "play",       // ID для webhook
        .sound = SOUND_PLAY,       // Звук
        .enabled = true            // Включена
    },

    // Кнопка 5: "catch"
    {
        .pin = 5,                  // GPIO пин
        .word = "catch",            // Слово
        .webhookId = "catch",       // ID для webhook
        .sound = SOUND_CATCH,       // Звук
        .enabled = true            // Включена
    },
    
};

// Количество кнопок в словаре
const uint8_t DICTIONARY_SIZE = sizeof(DICTIONARY) / sizeof(ButtonWord);

// ============================================
// СПРАВКА ПО ДОСТУПНЫМ ЗВУКАМ:
// ============================================
// SOUND_PLAY       - для игры
// SOUND_CATCH      - для ловли
// SOUND_TUG        - для перетягивания каната
// SOUND_BALL       - для мяча
// SOUND_PUZZLE    - для головоломки
// SOUND_BEEP_SHORT - короткий сигнал
// SOUND_BEEP_LONG  - длинный сигнал
// SOUND_SUCCESS    - успех
// SOUND_ERROR      - ошибка
// ============================================