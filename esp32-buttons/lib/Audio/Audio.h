// lib/Audio/Audio.h
#pragma once
#include <Arduino.h>
#include "driver/i2s.h"
#include "Sounds.h"

class Audio {
public:
    // Инициализация I2S
    static void init(int bclk, int lrc, int din, uint32_t sampleRate = 22050);
    
    // Играть один тон
    static void playTone(uint32_t frequency, uint32_t duration);
    
    // Играть мелодию из массива нот
    static void playMelody(const Note* notes, uint8_t length);
    
    // Играть звук по типу
    static void playSound(SoundType type);
    
    // Тишина (очистка буфера)
    static void silence();
    
private:
    static uint32_t _sampleRate;
    static bool _initialized;
    
    // Генерация синусоиды
    static void generateTone(uint32_t frequency, uint32_t duration);
};