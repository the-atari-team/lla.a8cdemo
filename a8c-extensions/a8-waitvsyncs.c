// --------------------------------------------------
// Function: void WaitVsyncs(byte N)
// Desc....: Wait more than 1 vsync
// Param...: N = count of vsyncs to wait
// --------------------------------------------------

void WaitVsyncs(byte n) {
  byte i;
  if (i<1) return;

  for (i=0;i<n;i++) {
    waitvsync();
  }
}
