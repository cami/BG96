/*
 * Get IMEI of a SIM.
 */

#include "NectisCellularBG96.h"

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

  char imei[16];
  char imsi[16];
  char tel[16];

  // IMEIを取得してみよう
  if(BG96.GetIMEI(imei, sizeof(imei)) > 0){
    Serial.print("imei=");
    Serial.println(imei);
  }

  // IMSIを取得してみよう
  if(BG96.GetIMSI(imsi, sizeof(imsi)) > 0){
    Serial.print("imsi=");
    Serial.println(imsi);
  }

  // 電話番号を取得してみよう
  if(BG96.GetPhoneNumber(tel, sizeof(tel)) > 0){
    Serial.print("tel=");
    Serial.println(tel);
  }

  Serial.flush();
  delay(1);
}

void loop() {
}
