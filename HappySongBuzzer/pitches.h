/*    This header file defines periods for displaying notes
 * from C0 to B8 on a passive buzzer.
 * 
 *    For example,
 *    The frequency of C4 is 261.6Hz (261.6 s^-1)
 * Period = 1 / frequency
 *        = 1 / 261.6 Hz
 *        = 3822 microseconds
 *    This means, the passive buzzer needs to finish turning on  
 * and off in 3823 microseconds in order to display C4.
 *    In other words, in order to play C4, you need to turn the 
 * passive buzzer on for 1911 microseconds, then turn it off for
 * another 1911 microseconds, so on and so forth. (3822 / 2 = 1911)
 * 
 *    All periods in this file are the half periods. (1911 for C4)
 */


#define C2 7644
#define Cs2 7215
#define Db2 7215
#define D2 6810
#define Ds2 6428
#define Eb2 6428
#define E2 6067
#define F2 5727
#define Fs2 5405
#define Gb2 5405
#define G2 5102
#define Gs2 4816
#define Ab2 4816
#define A2 4545
#define As2 4290
#define Bb2 4290
#define B2 4050
#define C3 3822
#define Cs3 3608
#define Db3 3608
#define D3 3405
#define Ds3 3214
#define Eb3 3214
#define E3 3034
#define F3 2864
#define Fs3 2703
#define Gb3 2703
#define G3 2551
#define Gs3 2408
#define Ab3 2408
#define A3 2273
#define As3 2145
#define Bb3 2145
#define B3 2025
#define C4 1911
#define Cs4 1804
#define Db4 1804
#define D4 1703
#define Ds4 1607
#define Eb4 1607
#define E4 1517
#define F4 1432
#define Fs4 1351
#define Gb4 1351
#define G4 1276
#define Gs4 1204
#define Ab4 1204
#define A4 1136
#define As4 1073
#define Bb4 1073
#define B4 1012
#define C5 956
#define Cs5 902
#define Db5 902
#define D5 851
#define Ds5 804
#define Eb5 804
#define E5 758
#define F5 716
#define Fs5 676
#define Gb5 676
#define G5 638
#define Gs5 602
#define Ab5 602
#define A5 568
#define As5 536
#define Bb5 536
#define B5 506
#define C6 478
#define Cs6 451
#define Db6 451
#define D6 426
#define Ds6 402
#define Eb6 402
#define E6 379
#define F6 358
#define Fs6 338
#define Gb6 338
#define G6 319
#define Gs6 301
#define Ab6 301
#define A6 284
#define As6 268
#define Bb6 268
#define B6 253
#define C7 239
#define Cs7 225
#define Db7 225
#define D7 213
#define Ds7 201
#define Eb7 201
#define E7 190
#define F7 179
#define Fs7 169
#define Gb7 169
#define G7 159
#define Gs7 150
#define Ab7 150
#define A7 142
#define As7 134
#define Bb7 134
#define B7 127
