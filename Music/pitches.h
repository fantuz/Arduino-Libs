/*
 *  Modified and updated by Enrico Formenti
 *  from an original file by Tom Igoe
 *
 *  BSD license, check license.txt for more information
 *  All text above must be included in any redistribution.
 *
 *  See macduino.blogspot.com for more details.
 *
 *  NB: recall that here all the notes are 1 octave superior
 *  to the normal since we started from 0 and not from -1
 *  to count octaves.
 */


/*************************************************
 * Public Constants
 *************************************************/

#ifndef PITCHES_H
#define PITCHES_H


#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

#define NOTE_DO0 16
#define NOTE_DOd0 17
#define NOTE_RE0 18
#define NOTE_REd0 19
#define NOTE_MI0 20
#define NOTE_FA0 22
#define NOTE_FAd0 23
#define NOTE_SOL0 24
#define NOTE_SOLd0 26
#define NOTE_LA0 27
#define NOTE_LAd0 29
#define NOTE_SI0 31

#define NOTE_DO1  33
#define NOTE_DOd1 35
#define NOTE_RE1  37
#define NOTE_REd1 39
#define NOTE_MI1  41
#define NOTE_FA1  44
#define NOTE_FAd1 46
#define NOTE_SOL1  49
#define NOTE_SOLd1 52
#define NOTE_LA1  55
#define NOTE_LAd1 58
#define NOTE_SI1  62

#define NOTE_DO2  65
#define NOTE_DOd2 69
#define NOTE_RE2  73
#define NOTE_REd2 78
#define NOTE_MI2  82
#define NOTE_FA2  87
#define NOTE_FAd2 93
#define NOTE_SOL2  98
#define NOTE_SOLd2 104
#define NOTE_LA2  110
#define NOTE_LAd2 117
#define NOTE_SI2  123

#define NOTE_DO3  131
#define NOTE_DOd3 139
#define NOTE_RE3  147
#define NOTE_REd3 156
#define NOTE_MI3  165
#define NOTE_FA3  175
#define NOTE_FAd3 185
#define NOTE_SOL3  196
#define NOTE_SOLd3 208
#define NOTE_LA3  220
#define NOTE_LAd3 233
#define NOTE_SI3  247

#define NOTE_DO4  262
#define NOTE_DOd4 277
#define NOTE_RE4  294
#define NOTE_REd4 311
#define NOTE_MI4  330
#define NOTE_FA4  349
#define NOTE_FAd4 370
#define NOTE_SOL4  392
#define NOTE_SOLd4 415
#define NOTE_LA4  440
#define NOTE_LAd4 466
#define NOTE_SI4  494

#define NOTE_DO5  523
#define NOTE_DOd5 554
#define NOTE_RE5  587
#define NOTE_REd5 622
#define NOTE_MI5  659
#define NOTE_FA5  698
#define NOTE_FAd5 740
#define NOTE_SOL5  784
#define NOTE_SOLd5 830
#define NOTE_LA5  880
#define NOTE_LAd5 932
#define NOTE_SI5  988

#define NOTE_DO6  1047
#define NOTE_DOd6 1109
#define NOTE_RE6  1175
#define NOTE_REd6 1245
#define NOTE_MI6  1319
#define NOTE_FA6  1397
#define NOTE_FAd6 1480
#define NOTE_SOL6  1568
#define NOTE_SOLd6 1661
#define NOTE_LA6  1760
#define NOTE_LAd6 1865
#define NOTE_SI6  1976

#define NOTE_DO7  2093
#define NOTE_DOd7 2217
#define NOTE_RE7  2349
#define NOTE_REd7 2489
#define NOTE_MI7  2637
#define NOTE_FA7  2794
#define NOTE_FAd7 2960
#define NOTE_SOL7 3136
#define NOTE_SOLd7 3322
#define NOTE_LA7  3520
#define NOTE_LAd7 3729
#define NOTE_SI7  3951

#define NOTE_DO8  4186
#define NOTE_DOd8 4435
#define NOTE_RE8  4699
#define NOTE_REd8 4978
#define NOTE_MI8  5274
#define NOTE_FA8  5588
#define NOTE_FAd8 5920
#define NOTE_SOL8 6272
#define NOTE_SOLd8 6645
#define NOTE_LA8  7040
#define NOTE_LAd8 7459
#define NOTE_SI8 7902

#define NOTE_DO9  8372
#define NOTE_DOd9 8870
#define NOTE_RE9  9397
#define NOTE_REd9 9956
#define NOTE_MI9  10548
#define NOTE_FA9  11175
#define NOTE_FAd9 11840
#define NOTE_SOL9 12544
#define NOTE_SOLd9 13290
#define NOTE_LA9  14080
#define NOTE_LAd9 14917
#define NOTE_SI9  15804

#endif
