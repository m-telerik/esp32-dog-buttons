// lib/Sounds/Sounds.h
#pragma once
#include <Arduino.h>

// Типы звуков
enum SoundType {
    SOUND_NONE = 0,
    
    // Базовые звуки
    SOUND_BEEP_SHORT,
    SOUND_BEEP_LONG,
    SOUND_SUCCESS,
    SOUND_ERROR,
    
    // Команды/активности
    SOUND_WALK,
    SOUND_FOOD,
    SOUND_WATER,
    SOUND_PLAY,
    SOUND_SLEEP,
    SOUND_CAR,
    
    // Эмоции
    SOUND_HAPPY,
    SOUND_SAD,
    SOUND_LOVE,
    SOUND_HELP,
    SOUND_SCARED,
    SOUND_MAD,
    
    // Вопросы/ответы
    SOUND_YES,
    SOUND_NO,
    SOUND_QUESTION,
    SOUND_LOOK,
    SOUND_COME,
    
    // Состояния
    SOUND_DONE,
    SOUND_MORE,
    SOUND_WAIT,
    SOUND_HOME,
};

// Структура ноты для мелодий
struct Note {
    uint32_t frequency;  // Частота в Гц
    uint32_t duration;   // Длительность в мс
};

class Sounds {
public:
    // Получить массив нот для звука
    static const Note* getNotes(SoundType type, uint8_t* length);
    
    // Получить название звука (для отладки)
    static const char* getName(SoundType type);
};