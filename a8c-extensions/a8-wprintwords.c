// --------------------------------------------------
// Library: a8-wprintwords.c
// Desc...: Atari 8 Bit Menu Library extension
// Author.: LarsImNetz
// Date...: 2024.01
// License: GNU General Public License v3.0
// Note...: Requires: a8defines.c
//        :           a8-wput2.c
//        :           string.h
// Function: byte WPrintWords(byte bN, unsigned char* chars)
// Desc....: print a whole string into the given handle
//           will not overwrite the window frame and will insert a newline
//           if the word for current line is too long.
// Param...: byte handle = window handle number
//           unsigned char *pS = ATASCII list of bytes (chars)
// --------------------------------------------------

void WPrintWords(byte handle, unsigned char *pS) {
    byte bLen;
    byte i,j;
    byte chr;
    byte charInWord;
    byte wordLength;

    // Set working var
    bLen = strlen(pS);

    // Only if handle is used
    if (baW.bU[handle] == WON) {
        // If window is inverse, flip string
        for (i=0;i<bLen;) {
            chr = pS[i];

            if (chr != ' ') {
                // search next word, count length
                wordLength = 0;
                for (j=i; j<bLen; j++) {
                    charInWord = pS[j];
                    if (charInWord == ' ') {
                      // found end of word
                      break;
                    }
                    wordLength++;
                }
                if (baW.bW[handle] < wordLength) {
                    // word longer then the window width, simple print
                }
                else if ((vCur.vX + wordLength) > (baW.bX[handle] + baW.bW[handle] - 1) ) {
                    // word too long, goto next line
                    NewLine(handle);
                }
                for (j=0;j<wordLength;j++) {
                    WPut2(handle, pS[i+j]);
                }
                i += wordLength;
            }
            else {
                // write a space into screen, but not if the cursor is at position 1.
                if (i > 0 && (vCur.vX > (baW.bX[handle] + 1)) ) {
                    WPut2(handle, ' ');
                }
                i++;
            }
        }
    }
}
