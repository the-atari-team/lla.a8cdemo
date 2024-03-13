// ------------------------------------------------------------
// Program: appdemo.c
// Desc...: A8 Library Demo Application
// Author.: Wade Ripkowski & Lars Langhans
// Date...: A8:20220825 Extension:20240114
// License: GNU General Public License v3.0
// Notes..: cl65 -v [-O] -t atarixl larsdemo.c -o larsdemo.xex
// ------------------------------------------------------------

// Pull in include files
#include <stdio.h>
#include <conio.h>
#include <unistd.h>
#include <string.h>
#include <atari.h>

// A8C Library in extra directory
#include "../a8clib/a8defines.h"
#include "../a8clib/a8defwin.h"
#include "../a8clib/a8libmisc.c"
#include "../a8clib/a8libstr.c"
#include "../a8clib/a8libwin.c"
#include "../a8clib/a8libmenu.c"
#include "../a8clib/a8libgadg.c"

// A8C Lib Extension
#include "../a8c-extensions/a8-wput2.c"
#include "../a8c-extensions/a8-wprintwords.c"
#include "../a8c-extensions/a8-waitvsyncs.c"

// ------------------------------------------------------------
// Func...: void About(void)
// Desc...: About Dialog
// ------------------------------------------------------------
void About(void) {
    byte handle;

    // Show about window
    handle = WOpen(1, 6, 38, 14, WOFF, WON);

    WOrn(handle, WPTOP, WPLFT, "About");

    WPrint(handle, WPCNT,  1, WOFF, "- Demo Application -");
    WPrint(handle, WPCNT,  2, WOFF, "Based on A8C Lib Version 1.00-C");
    WPrint(handle, WPCNT,  3, WOFF, "written by LarsImNetz");
    WPrint(handle, WPCNT,  5, WOFF, "Application to demonstrate");
    WPrint(handle, WPCNT,  6, WOFF, "the C library.");
    WPrint(handle, WPCNT,  7, WOFF, "With some self written extensions.");
    WPrint(handle, WPCNT, 12, WON, " Ok ");

    // Wait for key
    WaitKCX(WOFF);

    WClose(handle);

    return;
}


// ------------------------------------------------------------
// Func...: void SubMenu(void)
// Desc...: Sub menu routine
// ------------------------------------------------------------
void SubMenu(byte x, byte y) {
    byte handle, entry = 1;
    byte inLoop = TRUE;
    unsigned char *subMenuEntries[4] = {
     " Sub-Item 1 ",
     " Sub-Item 2 ",
     " Sub-Item 3 " };

    // Open window
    handle = WOpen(x, y, 14, 7, WOFF, WON);
    WOrn(handle, WPTOP, WPLFT, "Sub-Menu");

    // Loop until exit
    while (inLoop) {
        // Display menu and get choice
        entry = MenuV(handle, 1, 2, WOFF, entry, 3, subMenuEntries);

        // Process choice
        switch (entry) {
            case 1:
                GAlert(" Sub-Item 1 selected. ");
                break;

            case 2:
                GAlert(" Sub-Item 2 selected. ");
                break;

            case 3:
                GAlert(" Sub-Item 3 selected. ");
                break;

            case XESC:
                inLoop = FALSE;
                break;
        }
    }

    WClose(handle);

    return;
}

// ------------------------------------------------------------
// Func...: void showZauberlehrling()
//
// Desc...: Kleine Funktion, die ein Window oeffnet und Text zeigt
// ------------------------------------------------------------
void showZauberlehrling() {
    byte handle;

    handle = WOpen(0,4,40,16,WOFF, WON);
    WOrn(handle, WPTOP, WPLFT, "Der Zauberlehrling");
    WOrn(handle, WPTOP, WPRGT, "1.+ 2. Strophe");
    WOrn(handle, WPBOT, WPRGT, "J.W. von Goethe");
    WPos(handle,1,1);
    WPrintWords(handle, "Hat der alte Hexenmeister sich doch einmal wegbegeben! ");
    WPrintWords(handle, "Und nun sollen seine Geister auch nach meinem Willen leben. ");
    WPrintWords(handle, "Seine Wort' und Werke Merkt ich und den Brauch, und mit Geistesstaerke tu ich Wunder auch.");

    NewLine(handle);
    WPrintWords(handle, "Walle! Walle! Manche Strecke, dass, zum Zwecke, Wasser fliesse und mit reichem, vollem Schwalle zu dem Bade sich ergiesse.");

    WPrint(handle, WPCNT, 14, WON, "Press key");
    WaitKCX(WOFF);
    WClose(handle);
}

void showAllAscii() {
    byte handle;
    word i;

    handle = WOpen(1,4,34,11,WOFF, WON);
    WOrn(handle, WPTOP, WPLFT, "Zeige alle ASCII Zeichen");

    // Cursor setzen in linke obere Ecke
    WPos(handle, 1,1);

    // Alle 256 Zeichen einfach einmal ausgeben
    // dabei werden die Raender nicht ueberschrieben und es kann jedes Zeichen ausgegeben werden.
    for (i=0; i<=255;i++) {
        WPut2(handle, i);
    }

    WPrint(handle, WPCNT, baW.bH[handle]-2, WON, "Press key");
    WaitKCX(WOFF);

    // Langsames Loeschen von oben nach unten, sieht cool aus
    for (i=1;i<baW.bH[handle]-1;i++) {
        WDiv(handle, i, WOFF);
        WaitVsyncs(7);
    }

    // Close window
    WClose(handle);
}

// ------------------------------------------------------------
// Func...: void AbbucDemo(void)
//
// Desc...: Test routine, written by LarsImNetz
// ------------------------------------------------------------

// legt man in cc65 zu viele lokale Variablen an, muss das pragma static-locals gesetzt werden!
#pragma static-locals(push, on)

void AbbucDemo(void) {
    byte handle;
    byte handle2;
    byte handle3;
    byte handle4;
    word i;
    byte runLoop;
    byte value;
    int wordValue;
    unsigned char cValue[30];
    unsigned char cLines[256];

    showAllAscii();

    handle = WOpen(1,4,34,6,WOFF, WON);
    WOrn(handle, WPTOP, WPRGT, "Zahlenausgabe ist tricky");

    // Die Ausgabe von Zahlen ist noch etwas anspruchsvoll
    wordValue = 1;
    sprintf(cValue, "%5d a small value", wordValue);
    WPrint(handle, 1,  1, WOFF, cValue);

    wordValue = 32767;
    sprintf(cValue, "%5d a high value", wordValue);
    WPrint(handle, 1,  2, WOFF, cValue);

    WPrint(handle, WPCNT, baW.bH[handle]-2, WON, "Press key");
    // Wait for key
    WaitKCX(WOFF);

//    WClr(handle);
    // ---------------------------------------------------------------------------
    handle2 = WOpen(6,4,34,19,WOFF, WON);
    WOrn(handle2, WPTOP, WPLFT, "Woerter ausgeben");

    sprintf(cLines, "Dies ist eine etwas laengere Abfolge von Woertern, die nur mal zeigen sollen, wie es aussieht, wenn langer Text ausgegeben wird.");

    // Einfache Ausgabe eines langen Strings per WPrint
    // WPrint schneidet am Ende der Zeile einfach ab. Fuer die Anzeige von Text eher unbrauchbar.
    WPrint(handle2, 1, 2, WON, "Abgeschnitten:");
    WPrint(handle2, 1, 3, WOFF, cLines);

    // Ausgabe per WPut2, was die Grenzen eines Windows einhaelt und alles ausgibt, da aber
    // Wortgrenzen nicht eingehalten werden, unschoen.
    WPrint(handle2, 1, 4, WON, "Einfach hintereinander ausgeben:");
    WPos(handle2,1,5);
    for (i=0;i<strlen(cLines);i++) {
        WPut2(handle2, cLines[i]);
    }

    NewLine(handle2);

    baW.bI[handle2] = WON;
    WPrintWords(handle2, "Sauber an Wordgrenze getrennt:");
    baW.bI[handle2] = WOFF;

    // Ausgabe, was auch noch die Wordgrenzen beruecksichtigt, ließ sich leicht als Erweiterung einbinden
    WPrintWords(handle2, cLines);

    WPrint(handle2, WPCNT, baW.bH[handle2]-2, WON, "Press key");

    WaitKCX(WOFF);

    // ---------------------------------------------------------------------------
    handle3 = WOpen(1,12,32,12,WOFF, WON);
    WOrn(handle3, WPTOP, WPLFT, "Lorem ipsum dolor...");

    // Ausgabe von sehr viel Text (bis 255 Zeichen sind moeglich)
    WPos(handle3,1,1);
    WPrintWords(handle3, "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimat");

    WPrint(handle3, WPCNT, baW.bH[handle3]-2, WON, "Press key");
    WaitKCX(WOFF);


    handle4 = WOpen(0,8,40,5,WOFF, WON);
    WOrn(handle4, WPTOP, WPLFT, "Ueberlanges Wort");

    // Ausgabe eines superlangenzusammengeschriebenen Worts
    WPos(handle4,1,1);
    WPrintWords(handle4, "Supercallifragilistiexpialigetischlongersingleword");

    WPrint(handle4, WPCNT, baW.bH[handle4]-2, WON, "Press key");
    WaitKCX(WOFF);

    WClose(handle4);
    WClose(handle3);
    WClose(handle2);
    WClose(handle);

    // ---------------------------------------------------------------------------

    showZauberlehrling();

    // ---------------------------------------------------------------------------
    // Oeffne neues window
    // Mit jeder Menge Ornamenten auf dem Rahmen
    handle4 = WOpen(1, 6, 38, 14, WOFF, WON);

    WOrn(handle4, WPTOP, WPLFT, "About");
    WOrn(handle4, WPTOP, WPRGT, "Test");
    WOrn(handle4, WPBOT, WPLFT, "Left");
    WOrn(handle4, WPBOT, WPRGT, "Right");
    WOrn(handle4, WPBOT, WPCNT, "Center");

    // zentrierten Text ausgeben
    WPrint(handle4, WPCNT,  1, WOFF, "Test text");

    // Linksbuendige Ausgabe beginnt immer bei 1, die WPLFT wird nicht beruecksichtigt
    WPrint(handle4, 1,  2, WOFF, "Linksbuendig");

    // Rechtsbuendige Ausgabe funktioniert auch nicht, man muss sich selbst ausrechnen wo man beginnen moechte
    WPrint(handle4, 25,  3, WON, "Rechtsbuendig?");

    // Ueberlanger zentrierter Text buegelt die Raender ueber
    WPrint(handle4, 1, 5, WON, "Achte auf die Raender...");
    WPrint(handle4, WPCNT, 7, WOFF, "Dies ist ein etwas laengerer Text, der nicht voll angezeigt wird.");

    WPrint(handle4, WPCNT, 10, WON, "Press key for submenu");
    WaitKCX(WOFF);
    WPrint(handle4, WPCNT, 10, WOFF, "                     ");

    // Ein Submenue erscheint oben links
    SubMenu(1, 1);

    WPrint(handle4, WPCNT, 10, WON, "Press key");

    // Wait for key
    WaitKCX(WOFF);

    // Close window
    WClose(handle4);

    return;
}
#pragma static-locals(pop)

// ------------------------------------------------------------
// Func...: void main(void)
// Desc...: Main routine
// ------------------------------------------------------------
void main(void) {

    byte handle1, handle2, entry = 1;
    byte inLoop = TRUE;
    unsigned char *pcMainMenuEntries[6] = {
        " Sub-Menu     ",
        " Abbuc-Demo   ",
        " About        ",
        " Exit         "
    };

    // Setup screen
    WInit();
    WBack(14); // Screen Number of "."

    // Open header window
    handle1 = WOpen(1, 0, 38, 3, WON, WON);
    WPrint(handle1, WPCNT, 1, WOFF, "D E M O N S T R A T I O N");

    // Open menu window
    handle2 = WOpen(12, 7, 16, 7, WOFF, WON);
    WOrn(handle2, WPTOP, WPLFT, "Menu");

    // Loop until done (Exit selected)
    while (inLoop) {
        // Call menu
        entry = MenuV(handle2, 1, 2, WON, entry, 6, pcMainMenuEntries);

        // Process choice
        switch (entry) {
            case 1:
             SubMenu(16, 10);
             break;

            case 2:
             AbbucDemo();
             break;

            case 3:
             About();
             break;


            case 4:
             inLoop = FALSE;
             break;
        }

        // Exit on ESC as well
        if (entry == XESC) {
            inLoop = FALSE;
        }
    }

    // Close windows
    WClose(handle2);
    WClose(handle1);

    // Exit
    return;
}
