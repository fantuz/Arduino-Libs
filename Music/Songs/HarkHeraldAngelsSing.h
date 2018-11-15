
/*
 *  Hark! The herald-angels sing
 *  Music by  Charles Wesley and adapted by various artists
 *  http://en.wikipedia.org/wiki/Hark!_The_Herald_Angels_Sing
 *
 *  Written by Enrico Formenti.
 *  BSD license, check license.txt for more information
 *  All text above must be included in any redistribution.
 *
 */

#include "pitches.h"
#include "durations.h"

const int melody_len = 76;

int melody[] = {
    NOTE_DO4, NOTE_FA4, NOTE_FA4, NOTE_MI4,   // 4
    NOTE_FA4, NOTE_LA4, NOTE_LA4, NOTE_SOL4,  // 8
    NOTE_DO5, NOTE_DO5, NOTE_DO5, NOTE_LAd4,   // 12
    NOTE_LA4, NOTE_SOL4, NOTE_LA4,            // 15
    NOTE_DO4, NOTE_FA4, NOTE_FA4, NOTE_MI4,   // 19
    NOTE_FA4, NOTE_LA4, NOTE_LA4, NOTE_SOL4,  // 23
    NOTE_DO5, NOTE_SOL4, NOTE_SOL4, NOTE_MI4, // 27
    NOTE_MI4, NOTE_RE4, NOTE_DO4,             // 30
    NOTE_DO5, NOTE_DO5, NOTE_DO5, NOTE_FA4,   // 34
    NOTE_LAd4, NOTE_LA4, NOTE_LA4, NOTE_SOL4,  // 38
    NOTE_DO5, NOTE_DO5, NOTE_DO5, NOTE_FA4,   // 42
    NOTE_LAd4, NOTE_LA4, NOTE_LA4, NOTE_SOL4,  // 46
    NOTE_RE5, NOTE_RE5, NOTE_RE5, NOTE_DO5,   // 50
    NOTE_LAd4, NOTE_LA4, NOTE_LA4,             // 53
    NOTE_SOL4, NOTE_LA4, NOTE_LAd4, NOTE_DO5, NOTE_FA4, // 58
    NOTE_FA4, NOTE_SOL4, NOTE_LA4,            // 61
    NOTE_RE5, NOTE_RE5, NOTE_RE5, NOTE_DO5,   // 65
    NOTE_LAd4, NOTE_LA4, NOTE_LAd4,             // 68
    NOTE_SOL4, NOTE_LA4, NOTE_LAd4, NOTE_RE5,  NOTE_FA4, // 73
    NOTE_FA4, NOTE_SOL4, NOTE_FA4             // 76
};


int noteDurations[] = {
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA+DUR_CROMA, DUR_CROMA, // 4
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA,      // 8
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA+DUR_CROMA, DUR_CROMA, // 12
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_MINIMA,                          // 15
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA+DUR_CROMA, DUR_CROMA, // 19
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA,      // 23
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA+DUR_CROMA, DUR_CROMA, // 27
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_MINIMA,                          // 30
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA,      // 34
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA,      // 38
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA,      // 42
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA,      // 46
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA,      // 50
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_MINIMA,                          // 53
    DUR_SEMIMINIMA, DUR_CROMA, DUR_CROMA, DUR_SEMIMINIMA+DUR_CROMA, DUR_CROMA, // 58
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_MINIMA,                          // 61
    DUR_SEMIMINIMA+DUR_CROMA, DUR_CROMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, // 65
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_MINIMA,                          // 68
    DUR_SEMIMINIMA, DUR_CROMA, DUR_CROMA, DUR_SEMIMINIMA+DUR_CROMA, DUR_CROMA, // 73
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_MINIMA                           // 76
};