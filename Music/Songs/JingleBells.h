
/*
 *  Jingle Bells
 *  Music by James Lord Pierpont (1822–1893)
 *  http://en.wikipedia.org/wiki/James_Pierpont_(musician)
 *
 *  Written by Enrico Formenti.
 *  BSD license, check license.txt for more information
 *  All text above must be included in any redistribution.
 *
 */

#include "pitches.h"
#include "durations.h"

const int melody_len = 93;

int melody[] = {
    NOTE_PAUSE, NOTE_MI4, NOTE_RE4, NOTE_DO4,  // 4
    NOTE_PAUSE,                                // 5
    NOTE_PAUSE, NOTE_MI4, NOTE_RE4, NOTE_DO4,  // 9
    NOTE_PAUSE,                                // 10
    NOTE_PAUSE, NOTE_FA4, NOTE_MI4, NOTE_RE4,  // 14
    NOTE_PAUSE,                                // 15
    NOTE_SOL4, NOTE_SOL4, NOTE_FA4, NOTE_RE4,  // 19
    NOTE_MI4, NOTE_PAUSE,                      // 21
    NOTE_PAUSE, NOTE_MI4, NOTE_RE4, NOTE_DO4,  // 25
    NOTE_PAUSE,                                // 26
    NOTE_PAUSE, NOTE_MI4, NOTE_RE4, NOTE_DO4,  // 30
    NOTE_PAUSE,                                // 31
    NOTE_PAUSE, NOTE_FA4, NOTE_MI4, NOTE_RE4,  // 35
    NOTE_SOL4, NOTE_SOL4, NOTE_SOL4, NOTE_SOL4,// 39
    NOTE_LA4, NOTE_SOL4, NOTE_FA4, NOTE_RE4,   // 43
    NOTE_PAUSE, NOTE_SOL4,                     // 45
    NOTE_MI4, NOTE_MI4, NOTE_MI4,              // 48
    NOTE_MI4, NOTE_MI4, NOTE_MI4,              // 51
    NOTE_MI4, NOTE_SOL4, NOTE_DO4, NOTE_RE4,   // 55
    NOTE_FA4, NOTE_FA4, NOTE_FA4, NOTE_FA4,    // 59
    NOTE_FA4, NOTE_MI4, NOTE_MI4, NOTE_MI4,    // 63
    NOTE_MI4, NOTE_RE4, NOTE_RE4, NOTE_MI4,    // 67
    NOTE_RE4, NOTE_SOL4,                       // 69
    NOTE_MI4, NOTE_MI4, NOTE_MI4,              // 72
    NOTE_MI4, NOTE_MI4, NOTE_MI4,              // 75
    NOTE_MI4, NOTE_SOL4, NOTE_DO4, NOTE_RE4,   // 79
    NOTE_MI4,                                  // 80
    NOTE_FA4, NOTE_FA4, NOTE_FA4, NOTE_FA4,    // 84
    NOTE_FA4, NOTE_MI4, NOTE_MI4, NOTE_MI4,    // 88
    NOTE_SOL4, NOTE_SOL4, NOTE_FA4, NOTE_RE4,  // 92
    NOTE_DO4                                   // 93
};


int noteDurations[] = {
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, // 4
    DUR_SEMIBREVE,                                                  // 5
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, // 9
    DUR_SEMIBREVE,                                                  // 10
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, // 14
    DUR_SEMIBREVE,                                                  // 15
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, // 19
    DUR_MINIMA+DUR_SEMIMINIMA, DUR_SEMIMINIMA,                      // 21
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, // 25
    DUR_SEMIBREVE,                                                  // 26
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, // 30
    DUR_SEMIBREVE,                                                  // 31
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, // 35
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, // 39
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, // 43
    DUR_MINIMA, DUR_MINIMA,                                         // 45
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_MINIMA,                     // 48
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_MINIMA,                     // 51
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, // 55
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, // 59
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, // 63
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, // 67
    DUR_MINIMA, DUR_MINIMA,                                         // 69
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_MINIMA,                     // 72
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_MINIMA,                     // 75
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, // 79
    DUR_SEMIBREVE,                                                  // 80
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, // 84
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, // 88
    DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, DUR_SEMIMINIMA, // 92
    DUR_SEMIBREVE                                                   // 93
};
