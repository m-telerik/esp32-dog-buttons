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
    
    // Кнопка 1: "outside" (гулять)
    {
        .pin = 6,                  // GPIO пин
        .word = "outside",         // Слово
        .webhookId = "outside",    // ID для webhook
        .sound = SOUND_WALK,       // Звук
        .enabled = true            // Включена
    },
    
    // Кнопка 2: "food" (еда)
    {
        .pin = 2,                  // GPIO пин
        .word = "food",            // Слово
        .webhookId = "food",       // ID для webhook
        .sound = SOUND_FOOD,       // Звук
        .enabled = true            // Включена
    },
    
    // === Добавляйте новые кнопки здесь ===
    // Копируйте блок выше и меняйте значения
    
    // Пример отключенной кнопки:
    // {
    //     .pin = 5,
    //     .word = "water",
    //     .webhookId = "water",
    //     .sound = SOUND_WATER,
    //     .enabled = false        // Отключена - не будет работать
    // },
};

// Количество кнопок в словаре
const uint8_t DICTIONARY_SIZE = sizeof(DICTIONARY) / sizeof(ButtonWord);

// ============================================
// СПРАВКА ПО ДОСТУПНЫМ ЗВУКАМ:
// ============================================
// SOUND_WALK       - для прогулки, выхода
// SOUND_FOOD       - для еды, лакомств
// SOUND_WATER      - для воды
// SOUND_PLAY       - для игры
// SOUND_SLEEP      - для сна, отдыха
// SOUND_CAR        - для поездки
// SOUND_HAPPY      - радость
// SOUND_SAD        - грусть
// SOUND_LOVE       - любовь
// SOUND_HELP       - помощь
// SOUND_SCARED     - страх
// SOUND_MAD        - злость
// SOUND_YES        - да
// SOUND_NO         - нет
// SOUND_QUESTION   - вопрос
// SOUND_LOOK       - смотри
// SOUND_COME       - иди сюда
// SOUND_DONE       - готово
// SOUND_MORE       - ещё
// SOUND_WAIT       - подожди
// SOUND_HOME       - домой
// SOUND_SUCCESS    - успех
// SOUND_ERROR      - ошибка
// ============================================