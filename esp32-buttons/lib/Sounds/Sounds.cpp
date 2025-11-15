// lib/Sounds/Sounds.cpp
#include "Sounds.h"

// Определения мелодий
static const Note MELODY_BEEP_SHORT[] = {{1000, 100}};
static const Note MELODY_BEEP_LONG[] = {{800, 300}};
static const Note MELODY_SUCCESS[] = {{1000, 150}, {1200, 150}, {1500, 200}};
static const Note MELODY_ERROR[] = {{400, 200}, {300, 300}};

// HextileRed звуки
static const Note MELODY_TUG[] = {{500, 200}, {700, 200}, {900, 300}};
static const Note MELODY_BALL[] = {{800, 150}, {1000, 150}, {1200, 200}};
static const Note MELODY_PLAY[] = {{1500, 100}, {1200, 100}, {1500, 100}, {1800, 200}};
static const Note MELODY_PUZZLE[] = {{600, 200}, {800, 200}, {1000, 300}};
static const Note MELODY_CATCH[] = {{1300, 150}, {1100, 150}, {900, 200}};


const Note* Sounds::getNotes(SoundType type, uint8_t* length) {
    switch (type) {
        case SOUND_BEEP_SHORT:
            *length = sizeof(MELODY_BEEP_SHORT) / sizeof(Note);
            return MELODY_BEEP_SHORT;
        
        case SOUND_BEEP_LONG:
            *length = sizeof(MELODY_BEEP_LONG) / sizeof(Note);
            return MELODY_BEEP_LONG;
        
        case SOUND_SUCCESS:
            *length = sizeof(MELODY_SUCCESS) / sizeof(Note);
            return MELODY_SUCCESS;
        
        case SOUND_ERROR:
            *length = sizeof(MELODY_ERROR) / sizeof(Note);
            return MELODY_ERROR;

        case SOUND_TUG:
            *length = sizeof(MELODY_TUG) / sizeof(Note);
            return MELODY_TUG;

        case SOUND_BALL:
            *length = sizeof(MELODY_BALL) / sizeof(Note);
            return MELODY_BALL;

        case SOUND_PUZZLE:
            *length = sizeof(MELODY_PUZZLE) / sizeof(Note);
            return MELODY_PUZZLE;
        
        case SOUND_PLAY:
            *length = sizeof(MELODY_PLAY) / sizeof(Note);
            return MELODY_PLAY;

        case SOUND_CATCH:
            *length = sizeof(MELODY_CATCH) / sizeof(Note);
            return MELODY_CATCH;
        
        default:
            *length = 1;
            return MELODY_BEEP_SHORT;
    }
}

const char* Sounds::getName(SoundType type) {
    switch (type) {
        case SOUND_NONE: return "NONE";
        case SOUND_BEEP_SHORT: return "BEEP_SHORT";
        case SOUND_BEEP_LONG: return "BEEP_LONG";
        case SOUND_SUCCESS: return "SUCCESS";
        case SOUND_ERROR: return "ERROR";
        case SOUND_TUG: return "TUG";
        case SOUND_BALL: return "BALL";
        case SOUND_PUZZLE: return "PUZZLE";
        case SOUND_PLAY: return "PLAY";
        case SOUND_CATCH: return "CATCH";
        default: return "UNKNOWN";
    }
}