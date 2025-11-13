// lib/Audio/Audio.cpp
#include "Audio.h"
#include <math.h>

uint32_t Audio::_sampleRate = 22050;
bool Audio::_initialized = false;

void Audio::init(int bclk, int lrc, int din, uint32_t sampleRate) {
    _sampleRate = sampleRate;
    
    i2s_config_t cfg = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
        .sample_rate = sampleRate,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,
        .intr_alloc_flags = 0,
        .dma_buf_count = 6,
        .dma_buf_len = 256,
        .use_apll = false,
        .tx_desc_auto_clear = true,
        .fixed_mclk = 0
    };
    
    i2s_pin_config_t pins = {
        .bck_io_num = bclk,
        .ws_io_num = lrc,
        .data_out_num = din,
        .data_in_num = I2S_PIN_NO_CHANGE
    };
    
    i2s_driver_install((i2s_port_t)0, &cfg, 0, NULL);
    i2s_set_pin((i2s_port_t)0, &pins);
    i2s_zero_dma_buffer((i2s_port_t)0);
    
    _initialized = true;
    Serial.println("[Audio] Initialized");
}

void Audio::playTone(uint32_t frequency, uint32_t duration) {
    if (!_initialized) {
        Serial.println("[Audio] Not initialized!");
        return;
    }
    generateTone(frequency, duration);
}

void Audio::playMelody(const Note* notes, uint8_t length) {
    if (!_initialized) {
        Serial.println("[Audio] Not initialized!");
        return;
    }
    
    for (uint8_t i = 0; i < length; i++) {
        generateTone(notes[i].frequency, notes[i].duration);
        delay(50); // Небольшая пауза между нотами
    }
}

void Audio::playSound(SoundType type) {
    uint8_t length;
    const Note* notes = Sounds::getNotes(type, &length);
    playMelody(notes, length);
}

void Audio::generateTone(uint32_t frequency, uint32_t duration) {
    const size_t bufSize = 256;
    int16_t buffer[bufSize];
    
    double phase = 0;
    double phaseStep = 2.0 * M_PI * frequency / _sampleRate;
    size_t totalSamples = (_sampleRate * duration) / 1000;
    size_t sentSamples = 0;
    
    while (sentSamples < totalSamples) {
        size_t samplesToGenerate = min(bufSize, totalSamples - sentSamples);
        
        for (size_t i = 0; i < samplesToGenerate; i++) {
            buffer[i] = (int16_t)(sin(phase) * 16000);
            phase += phaseStep;
            if (phase > 2 * M_PI) phase -= 2 * M_PI;
        }
        
        size_t bytesWritten = 0;
        i2s_write((i2s_port_t)0, buffer, samplesToGenerate * sizeof(int16_t), 
                  &bytesWritten, portMAX_DELAY);
        sentSamples += samplesToGenerate;
    }
}

void Audio::silence() {
    if (_initialized) {
        i2s_zero_dma_buffer((i2s_port_t)0);
    }
}