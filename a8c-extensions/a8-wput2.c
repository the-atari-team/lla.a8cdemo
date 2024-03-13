// --------------------------------------------------
// Library: a8-wput2.c
// Desc...: Atari 8 Bit Menu Library extension
// Author.: LarsImNetz
// Date...: 2024.01
// License: GNU General Public License v3.0
// Note...: Requires: a8defines.h
//                    a8libstr.c
//          -Better replacement for WPut(...)
// --------------------------------------------------

void NewLine(byte handle);

// --------------------------------------------------
// Function: byte WPut2(byte handle, byte x)
// Desc....: Puts byte x in window at virtual curs coord
//           Use StrAI() to convert from ASCII to Atari Screen
//           Use memcpy to insert the single byte into the screen
//           Will not leave the Window frame
// Param...: handle = window handle number
//            x = ATASCII byte to display (char)
// Returns.: WON (in use)
//           WOFF (not used)
// --------------------------------------------------
byte WPut2(byte handle, byte x) {
    byte bR = WENOPN;
    byte bT;

    word cS;
    unsigned char cL[2];

    // Set working var
    bT = x;

    // Only if handle is used
    if (baW.bU[handle] == WON) {
        // If window is inverse, flip string
        if (baW.bI[handle] == WON) {
            bT ^= 128;
        }

        // Put byte to screen at current virtual cursor coord
        // cputc(bT);

        cL[0] = CharAI(bT);
//        cL[0] = bT;
//        cL[1] = '\0';
//        StrAI(cL, 1);
//        if ((baW.bI[handle] == WON)) {
//            StrInv(cL, 1);
//        }
        cS = iSMr[vCur.vY] + vCur.vX;

        // Move byte to screen
        // memcpy(cS, cL, 1);
        *(unsigned char*)cS = cL[0]; // there are days I hate C!

        // Increment virtual cursor by 1
        vCur.vX += 1;

        // primitive Cursorsteuerung, damit wir die Ränder nicht überschreiben
        // Scrolling ist nicht vorgesehen!
        if (handle != WPABS) {
            if (vCur.vX >= (baW.bX[handle] + baW.bW[handle] - 1)) {
              NewLine(handle);
            }
        }
        // Set return code
        bR = 0;
    }

    return(bR);
}

// Move Cursor to a new line at the beginning of the line.
void NewLine(byte handle) {
    vCur.vX = baW.bX[handle] + 1;
    vCur.vY += 1;
    if (vCur.vY >= (baW.bY[handle] + baW.bH[handle] - 1)) {
        // TODO scrolling!
        vCur.vY -= 1;
    }
    // gotoxy(vCur.vX, vCur.vY);
}
