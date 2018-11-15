
/*
 *  SilentNight
 *  Music by Franz Gruber (1787-1863)
 *  http://en.wikipedia.org/wiki/Franz_Xaver_Gruber
 *
 *  Written by Enrico Formenti.
 *  BSD license, check license.txt for more information
 *  All text above must be included in any redistribution.
 *
 */

#include "pitches.h"
#include "durations.h"

//const int melody_len = 46;
const uint16_t melody_len = 46;

//const int melody[] = {
const uint16_t melody[] = {
    NOTE_SOL4, NOTE_LA4, NOTE_SOL4,  // 3
    NOTE_MI4,                        // 4
    NOTE_SOL4, NOTE_LA4, NOTE_SOL4,  // 7
    NOTE_MI4,                        // 8
    NOTE_RE5, NOTE_RE5,              // 10
    NOTE_SI4,                        // 11
    NOTE_DO5, NOTE_DO5, NOTE_SOL4,   // 14
    NOTE_LA4, NOTE_LA4,              // 16
    NOTE_DO5, NOTE_SI4, NOTE_LA4,    // 19
    NOTE_SOL4, NOTE_LA4, NOTE_SOL4,  // 22
    NOTE_MI4,                        // 23
    NOTE_LA4, NOTE_LA4,              // 25
    NOTE_DO5, NOTE_SI4, NOTE_LA4,    // 28
    NOTE_SOL4, NOTE_LA4, NOTE_SOL4,  // 31
    NOTE_MI4,                        // 32
    NOTE_RE5, NOTE_RE5,              // 34
    NOTE_FA5, NOTE_RE5, NOTE_SI4,    // 37
    NOTE_DO5,                        // 38
    NOTE_MI5,                        // 39
    NOTE_DO5, NOTE_SOL4, NOTE_RE4,   // 42
    NOTE_SOL4, NOTE_FA4, NOTE_RE4,   // 45
    NOTE_DO4                         // 46
};

//uint16_t noteDurations
//const int noteDurations[] = {
const uint16_t noteDurations[] = {
    DUR_SEMIMINIMA+DUR_CROMA, DUR_CROMA, DUR_SEMIMINIMA, // 3
    DUR_MINIMA+DUR_SEMIMINIMA,               // 4
    DUR_SEMIMINIMA+DUR_CROMA, DUR_CROMA, DUR_SEMIMINIMA,     // 7
    DUR_MINIMA+DUR_SEMIMINIMA,               // 8
    DUR_MINIMA, DUR_SEMIMINIMA,          // 10
    DUR_MINIMA+DUR_SEMIMINIMA,               // 11
    DUR_MINIMA, DUR_SEMIMINIMA,          // 13
    DUR_MINIMA+DUR_SEMIMINIMA,               // 14
    DUR_MINIMA, DUR_SEMIMINIMA,          // 16
    DUR_SEMIMINIMA+DUR_CROMA, DUR_CROMA, DUR_SEMIMINIMA,     // 19
    DUR_SEMIMINIMA+DUR_CROMA, DUR_CROMA, DUR_SEMIMINIMA,     // 22
    DUR_MINIMA+DUR_SEMIMINIMA,               // 23
    DUR_MINIMA, DUR_SEMIMINIMA,          // 25
    DUR_SEMIMINIMA+DUR_CROMA, DUR_CROMA, DUR_SEMIMINIMA,     // 28
    DUR_SEMIMINIMA+DUR_CROMA, DUR_CROMA, DUR_SEMIMINIMA,     // 31
    DUR_MINIMA+DUR_SEMIMINIMA,               // 32
    DUR_MINIMA, DUR_SEMIMINIMA,          // 34
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA,     // 37
    DUR_MINIMA+DUR_SEMIMINIMA,               // 38
    DUR_MINIMA+DUR_SEMIMINIMA,               // 39
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA,     // 42
    DUR_SEMIMINIMA+DUR_CROMA, DUR_CROMA, DUR_SEMIMINIMA,     // 45
    DUR_MINIMA+DUR_SEMIMINIMA                // 46
};
