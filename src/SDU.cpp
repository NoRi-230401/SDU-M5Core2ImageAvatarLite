// --- for SD-Updater -------
// SDU.cpp 
//    NoRi 2024-06-01
// -------------------------
#include <Arduino.h>
#include <M5Unified.h>
#include <ESP32-targz.h>
#include <M5StackUpdater.h>

#define TFCARD_CS_PIN 4
#define SDU_SKIP_TMR 5000 // skip timer : ms
#define SERVO_TXT "/servo.txt"
#define LED_TXT "/led.txt"

extern bool USE_SERVO_ST;
extern bool USE_LED_ST;
void SDU_lobby();
bool SdBegin();
bool servoTxtSDRead();
const String PROG_NAME = "Image Avater Lite";

void SDU_lobby()
{
  SDUCfg.setAppName(PROG_NAME.c_str()); // lobby screen label: application name
  SDUCfg.setLabelMenu("< Menu");        // BtnA label: load menu.bin

  checkSDUpdater(
      SD,           // filesystem (default=SD)
      MENU_BIN,     // path to binary (default=/menu.bin, empty string=rollback only)
      SDU_SKIP_TMR, // wait delay, (default=0, will be forced to 2000 upon ESP.restart() )
      TFCARD_CS_PIN // usually default=4 but your mileage may vary
  );

  Serial.println("SDU_lobby done");
}

bool SdBegin()
{
  // --- SD begin -------
  int i = 0;
  bool success = false;
  Serial.println("SD.begin Start ...");

  while (i < 3)
  { // SDカードマウント待ち
    success = SD.begin(GPIO_NUM_4, SPI, 15000000);
    if (success)
      return true;

    Serial.println("SD Wait...");
    delay(500);
    i++;
  }

  if (i >= 3)
  {
    Serial.println("SD.begin faile ...");
    return false;
  }
  else
    return true;
}


bool servoTxtSDRead()
{
  if (!SdBegin())
  {
    SD.end();
    return false;
  }

  File fs = SD.open(SERVO_TXT, FILE_READ);
  if (!fs)
  {
    SD.end();
    return false;
  }

  size_t sz = fs.size();
  char buf[sz + 1];
  fs.read((uint8_t *)buf, sz);
  buf[sz] = 0;
  fs.close();

  int y = 0;
  int z = 0;
  for (int x = 0; x < sz; x++)
  {
    if (buf[x] == 0x0a || buf[x] == 0x0d)
      buf[x] = 0;
    else if (!y && x > 0 && !buf[x - 1] && buf[x])
      y = x;
    else if (!z && x > 0 && !buf[x - 1] && buf[x])
      z = x;
  }

  String SV_ON_OFF = "";
  String SV_PORT_X = "";
  String SV_PORT_Y = "";

  SV_ON_OFF = String(buf);
  SV_PORT_X = String(&buf[y]);
  SV_PORT_Y = String(&buf[z]);

  if (SV_ON_OFF == "on" || SV_ON_OFF == "ON")
    USE_SERVO_ST = true;
  else
    USE_SERVO_ST = false;

  Serial.println("USE_SERVO_ST  = " + SV_ON_OFF);
  return true;
}


bool ledTxtSDRead()
{
  if (!SdBegin())
  {
    SD.end();
    return false;
  }

  File fs = SD.open(LED_TXT, FILE_READ);
  if (!fs)
  {
    SD.end();
    return false;
  }

  size_t sz = fs.size();
  char buf[sz + 1];
  fs.read((uint8_t *)buf, sz);
  buf[sz] = 0;
  fs.close();

  for (int x = 0; x < sz; x++)
  {
    if (buf[x] == 0x0a || buf[x] == 0x0d)
      buf[x] = 0;
  }

  String LED_STR = String(buf);
  if (LED_STR == "on" || LED_STR == "ON")
    USE_LED_ST = true;
  else
    USE_LED_ST = false;

  Serial.println("USE_LED_ST = " + LED_STR);

  return true;
}

