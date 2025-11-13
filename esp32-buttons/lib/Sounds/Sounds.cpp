// lib/Sounds/Sounds.cpp
#include "Sounds.h"

// Определения мелодий
static const Note MELODY_BEEP_SHORT[] = {{1000, 100}};
static const Note MELODY_BEEP_LONG[] = {{800, 300}};
static const Note MELODY_SUCCESS[] = {{1000, 150}, {1200, 150}, {1500, 200}};
static const Note MELODY_ERROR[] = {{400, 200}, {300, 300}};

// Команды/активности
static const Note MELODY_WALK[] = {{600, 150}, {800, 150}, {1000, 200}};
static const Note MELODY_FOOD[] = {{1200, 100}, {1200, 100}, {1200, 200}};
static const Note MELODY_WATER[] = {{800, 200}, {600, 200}};
static const Note MELODY_PLAY[] = {{1500, 100}, {1200, 100}, {1500, 100}, {1800, 200}};
static const Note MELODY_SLEEP[] = {{600, 300}, {500, 300}, {400, 400}};
static const Note MELODY_CAR[] = {{500, 150}, {700, 150}, {900, 150}};

// Эмоции
static const Note MELODY_HAPPY[] = {{1200, 100}, {1400, 100}, {1600, 100}, {1800, 200}};
static const Note MELODY_SAD[] = {{800, 200}, {700, 200}, {600, 300}};
static const Note MELODY_LOVE[] = {{1000, 150}, {1200, 150}, {1000, 150}, {1400, 250}};
static const Note MELODY_HELP[] = {{1500, 100}, {1000, 100}, {1500, 100}, {1000, 200}};
static const Note MELODY_SCARED[] = {{700, 100}, {500, 100}, {700, 100}, {500, 200}};
static const Note MELODY_MAD[] = {{600, 150}, {500, 150}, {400, 200}};

// Вопросы/ответы
static const Note MELODY_YES[] = {{1200, 150}, {1500, 200}};
static const Note MELODY_NO[] = {{800, 150}, {600, 200}};
static const Note MELODY_QUESTION[] = {{1000, 150}, {1200, 150}, {1400, 150}};
static const Note MELODY_LOOK[] = {{1300, 200}, {1300, 200}};
static const Note MELODY_COME[] = {{1000, 150}, {1300, 150}};

// Состояния
static const Note MELODY_DONE[] = {{1200, 150}, {1000, 150}, {800, 200}};
static const Note MELODY_MORE[] = {{1000, 150}, {1200, 150}, {1400, 150}};
static const Note MELODY_WAIT[] = {{900, 300}};
static const Note MELODY_HOME[] = {{800, 200}, {1000, 200}, {1200, 200}};

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
        
        case SOUND_WALK:
            *length = sizeof(MELODY_WALK) / sizeof(Note);
            return MELODY_WALK;
        
        case SOUND_FOOD:
            *length = sizeof(MELODY_FOOD) / sizeof(Note);
            return MELODY_FOOD;
        
        case SOUND_WATER:
            *length = sizeof(MELODY_WATER) / sizeof(Note);
            return MELODY_WATER;
        
        case SOUND_PLAY:
            *length = sizeof(MELODY_PLAY) / sizeof(Note);
            return MELODY_PLAY;
        
        case SOUND_SLEEP:
            *length = sizeof(MELODY_SLEEP) / sizeof(Note);
            return MELODY_SLEEP;
        
        case SOUND_CAR:
            *length = sizeof(MELODY_CAR) / sizeof(Note);
            return MELODY_CAR;
        
        case SOUND_HAPPY:
            *length = sizeof(MELODY_HAPPY) / sizeof(Note);
            return MELODY_HAPPY;
        
        case SOUND_SAD:
            *length = sizeof(MELODY_SAD) / sizeof(Note);
            return MELODY_SAD;
        
        case SOUND_LOVE:
            *length = sizeof(MELODY_LOVE) / sizeof(Note);
            return MELODY_LOVE;
        
        case SOUND_HELP:
            *length = sizeof(MELODY_HELP) / sizeof(Note);
            return MELODY_HELP;
        
        case SOUND_SCARED:
            *length = sizeof(MELODY_SCARED) / sizeof(Note);
            return MELODY_SCARED;
        
        case SOUND_MAD:
            *length = sizeof(MELODY_MAD) / sizeof(Note);
            return MELODY_MAD;
        
        case SOUND_YES:
            *length = sizeof(MELODY_YES) / sizeof(Note);
            return MELODY_YES;
        
        case SOUND_NO:
            *length = sizeof(MELODY_NO) / sizeof(Note);
            return MELODY_NO;
        
        case SOUND_QUESTION:
            *length = sizeof(MELODY_QUESTION) / sizeof(Note);
            return MELODY_QUESTION;
        
        case SOUND_LOOK:
            *length = sizeof(MELODY_LOOK) / sizeof(Note);
            return MELODY_LOOK;
        
        case SOUND_COME:
            *length = sizeof(MELODY_COME) / sizeof(Note);
            return MELODY_COME;
        
        case SOUND_DONE:
            *length = sizeof(MELODY_DONE) / sizeof(Note);
            return MELODY_DONE;
        
        case SOUND_MORE:
            *length = sizeof(MELODY_MORE) / sizeof(Note);
            return MELODY_MORE;
        
        case SOUND_WAIT:
            *length = sizeof(MELODY_WAIT) / sizeof(Note);
            return MELODY_WAIT;
        
        case SOUND_HOME:
            *length = sizeof(MELODY_HOME) / sizeof(Note);
            return MELODY_HOME;
        
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
        case SOUND_WALK: return "WALK";
        case SOUND_FOOD: return "FOOD";
        case SOUND_WATER: return "WATER";
        case SOUND_PLAY: return "PLAY";
        case SOUND_SLEEP: return "SLEEP";
        case SOUND_CAR: return "CAR";
        case SOUND_HAPPY: return "HAPPY";
        case SOUND_SAD: return "SAD";
        case SOUND_LOVE: return "LOVE";
        case SOUND_HELP: return "HELP";
        case SOUND_SCARED: return "SCARED";
        case SOUND_MAD: return "MAD";
        case SOUND_YES: return "YES";
        case SOUND_NO: return "NO";
        case SOUND_QUESTION: return "QUESTION";
        case SOUND_LOOK: return "LOOK";
        case SOUND_COME: return "COME";
        case SOUND_DONE: return "DONE";
        case SOUND_MORE: return "MORE";
        case SOUND_WAIT: return "WAIT";
        case SOUND_HOME: return "HOME";
        default: return "UNKNOWN";
    }
}