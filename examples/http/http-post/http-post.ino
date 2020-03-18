#include <NectisCellularBG96.h>

#define WEBHOOK_URL       "http://unified.soracom.io"

NectisCellularBG96 BG96;

void setup() {
  char data[100];
  int status;

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

  delay(3000);
  
  Serial.println("### Post.");
  sprintf(data, "{\"value1\":\"uptime %lu\"}", millis() / 1000);
  Serial.print("Post:");
  Serial.print(data);
  Serial.println("");

//  if (!BG96.HttpPost(WEBHOOK_URL, data, &status)) {
//    Serial.println("### ERROR! ###");
//  }

  BG96.PostDataViaHttp(data);
  
  Serial.print("Status:");
  Serial.println(status);
}

void loop() {
}
