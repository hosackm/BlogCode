//
//  tycho_colors.h
//  TychoColors
//
//  Created by Hosack, Matthew on 7/31/15.
//
//

#ifndef TychoColors_tycho_colors_h
#define TychoColors_tycho_colors_h

#define NUM_TYCHO_COLORS (7)
#define TYCHO_DOTS_ROWS  (2)
#define TYCHO_DOTS_COLS  (7)

/* Background color */
int bg = 0xdbd8c7;

/* Hex colors from triangle out to last parallelogram */
int colors[NUM_TYCHO_COLORS] = {
    0x33414d,
    0x766f83,
    0x9e6f8c,
    0xa36579,
    0xd17382,
    0xb4685f,
    0xd27867
};

/* Holds the shape of the dots on the album cover
 * true represents a dot. false represents a space
 */
/*
 *             . . . .   .
 *             . .   . . . .
 *
 */
bool dots[TYCHO_DOTS_ROWS][TYCHO_DOTS_COLS] =
{
/*    *     *     *       *            *           */
    {true, true, true,  true, false, true, false},
/*    *     *             *     *      *     *     */
    {true, true, false, true, true,  true, true }
};

#endif
