/*
 * Get JST.
 */

#include "NectisCellularBG96.h"

#define INTERVAL  (5000)

NectisCellularBG96 BG96;


void setup() {
  Serial.begin(115200);
  delay(4000);
  Serial.println("");
  Serial.println("--- START ---------------------------------------------------");

  Serial.println("### I/O Initialize.");
  BG96.Init();
  delay(100);
  Serial.println("### Power supply cellular ON.");
  BG96.PowerSupplyCellular(true);
  delay(100);

  BG96.Bg96Begin();
  BG96.InitLteM();

  Serial.println("### Setup completed.");
}

void loop() {
  Serial.println("### Get time.");

  //    Get the current time.
  struct tm currentTime;
  char currentTimeStr[64];

  BG96.GetCurrentTime(&currentTime, true);
  strftime(currentTimeStr, sizeof(currentTimeStr), "%Y/%m/%d %H:%M:%S", &currentTime);

  Serial.print("JST=");
  Serial.println(currentTimeStr);

  Serial.flush();
  delay(1);

  delay(INTERVAL);
}
