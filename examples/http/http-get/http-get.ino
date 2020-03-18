#include <NectisCellularBG96.h>

#define WEBURL       "https://httpbin.org/ip"

NectisCellularBG96 BG96;

void setup() {
  char data[1024];
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

  Serial.println("GET " WEBURL);
  status = BG96.HttpGet(WEBURL, data, sizeof(data));
  
  Serial.print("RecvBytes:");
  Serial.println(status);

  if(status > 0)
  {
    data[status] = 0x0;
    Serial.println(data);
  }
  Serial.print("Status:");
  Serial.println(status);
}

void loop() {
}
