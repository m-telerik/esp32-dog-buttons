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
    
    // HextileRed
    SOUND_TUG,
    SOUND_BALL,
    SOUND_PUZZLE,
    SOUND_PLAY,
    SOUND_CATCH,
    
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