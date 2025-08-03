#pragma once

#define DEBUGING 1 // Switch debug output on and off by 1 or 0

#define HTML_TITLE "MOODLAMP with WS2812FX</br><small>MOODnPARTY edition</small>"
#define CSS_BTTN_STYLE  "font-size:1.6rem;min-height:4rem;padding:1rem;margin:3px;border:2px solid #404040;border-radius:5px;"
#define CSS_BTTN_DW_STYLE String(CSS_BTTN_STYLE) + "color:#999;background-color: #222;"
#define CSS_BTTN_UP_STYLE String(CSS_BTTN_STYLE) + "color:#222;background-color: #bbb;"
#define CSS_TEXT_STYLE  "height:26px;width:180px;"
#define CSS_TEXT_LABEL_STYLE  "margin-bottom: 0;font-size: 1.2em; background-color: unset; vertical-align: middle; text-align: left; width:55%"
#define CSS_SELECT_STYLE  "width:60px;"
#define CSS_SELECT_LABEL_STYLE  "font-size: 1.2em; background-color: unset; vertical-align: bottom; text-align: left; width:80%;margin-bottom: 3;"
#define CSS_NUMBER_STYLE  "width:60px;"
#define CSS_NUMBER_LABEL_STYLE  "font-size: 1.2em; background-color: unset; vertical-align: middle; text-align: left; width:80%"
#define CSS_STATUS_STYLE  "font-size: 22px; font-variant-caps: small-caps; background-color: unset; color: #c4f0bb; "//-webkit-text-stroke: 1px black;
#define CSS_STATUS_PANEL_STYLE  "margin-left: auto; margin-right: auto;float: none;"
#define CSS_COLOR_STYLE   "min-height:40px;"
#define CSS_CONTROL_LABEL_STYLE   "align-items: center; font-size: 1.2em; background-color: unset; vertical-align: middle; text-align: left; width:80%"
//#define CSS_CONTROL_SWITCH_STYLE   "align-items: center; text-align: right;"
#define CSS_SLIDER_LABEL_STYLE "font-size:1.2rem;font-weight:400;width:18%; background-color: unset;"//border: 1px solid black;
#define CSS_SAVEBUTTON_STYLE  "margin:0 2rem 1rem;width:200px;outline:0; border:0; border-radius:4px; border-bottom:4px solid #2b6cb0;background-color:#4299e1; color:white;"
#define CSS_NO_BG_STYLE "background-color: unset;"

// - - D E F A U L T S - - 
#define LED_COUNT 30
#define LED_PIN 27
#define LED_TYPE NEO_GRB + NEO_KHZ800

#define WIFI_AP_SSID "MOODLAMP-%08X"  // default AP WiFi Name
#define WIFI_AP_PASS  "" // default AP WiFi Password
#define HOSTNAME "moodlamp"
#define TTC 60000 // Time_To_Connect to WiFi


#include <WS2812FX.h>
//#include <WS2812FX_MnP_edition.h>

#define MAX_CLIENTS 4 
#define WIFI_CHANNEL 6

#include <AsyncTCP.h>
#include <DNSServer.h>
#include <ESPAsyncWebServer.h>
#include <ESPUI.h>
#include <EEPROM.h>

const byte DNS_PORT = 53;
const IPAddress localIP(4, 3, 2, 1);       // the IP address the web server, Samsung requires the IP to be in public space
const IPAddress gatewayIP(4, 3, 2, 1);       // IP address of the network should be the same as the local IP for captive portals
const IPAddress subnetMask(255, 255, 255, 0);  // no need to change: https://avinetworks.com/glossary/subnet-mask/

#if defined(WS2812FX_MNP_EDITION_h)
const uint8_t monoModes[] = {
  FX_MODE_STATIC,
  FX_MODE_BREATH,
  FX_MODE_SCAN,
  FX_MODE_MOOD_SWING,
  FX_MODE_THEATER_CHASE,
  FX_MODE_WAVES,
  FX_MODE_TWINKLE_FADE,
  FX_MODE_SPARKLE,
  FX_MODE_LARSON_SCANNER,
  FX_MODE_FIREWORKS,
  FX_MODE_XMAS_TWINKLE,
  FX_MODE_RAIN,
  FX_MODE_DISSOLVE,
  FX_MODE_COMETS,
  FX_MODE_POPCORN,
  FX_MODE_FIREFLY,
  FX_MODE_OCEAN,
  FX_MODE_FIRE2012,
  FX_MODE_ORBITA,
  FX_MODE_PARTYSKY,
  FX_MODE_DISCO,
  FX_MODE_METEOR,
  FX_MODE_FLYING_SPIRIT,
  FX_MODE_PORTAL
};
const uint8_t duoModes[] =  {
  FX_MODE_STATIC,
  FX_MODE_MOOD_CLICK,
  FX_MODE_BREATH,
  FX_MODE_SCAN,
  FX_MODE_DUAL_SCAN,
  FX_MODE_MOOD_SWING,
  FX_MODE_WAVES,
  FX_MODE_TWINKLE_FADE,
  FX_MODE_SPARKLE,
  FX_MODE_RUNNING_COLOR,
  FX_MODE_LARSON_SCANNER,
  FX_MODE_FIREWORKS,
  FX_MODE_XMAS_TWINKLE,
  FX_MODE_RAIN,
  FX_MODE_DISSOLVE,
  FX_MODE_DUAL_LARSON,
  FX_MODE_COMETS,
  FX_MODE_POPCORN,
  FX_MODE_PARTYSKY,
  FX_MODE_DISCO,
  FX_MODE_METEOR,
  FX_MODE_FLYING_SPIRIT,
  FX_MODE_PORTAL
};
const uint8_t rgbModes[] =  {
  FX_MODE_STATIC,
  FX_MODE_MOOD_CLICK,
  FX_MODE_MOOD_TRAIN,
  FX_MODE_MOOD_SHIFT,
  FX_MODE_MOOD_FLOW,
  FX_MODE_XMAS_GLANCE,
  FX_MODE_XMAS_TICK,
  FX_MODE_XMAS_TWINKLE,
  FX_MODE_XMAS_GLITTER,
  FX_MODE_TWINKLE_FADE,
  FX_MODE_SCAN,
  FX_MODE_DUAL_SCAN,
  FX_MODE_MOOD_SWING,
  FX_MODE_THEATER_CHASE,
  FX_MODE_WAVES,
  FX_MODE_SPARKLE,
  FX_MODE_LARSON_SCANNER,
  FX_MODE_DUAL_LARSON,
  FX_MODE_FIREWORKS,
  FX_MODE_RAIN,
  FX_MODE_DISSOLVE,
  FX_MODE_RUNNING_TAILS,
  FX_MODE_COMETS,
  FX_MODE_POPCORN,
  FX_MODE_FIREFLY,
  FX_MODE_FIRE2012,
  FX_MODE_ORBITA,
  FX_MODE_PARTYSKY,
  FX_MODE_OCEAN,
  FX_MODE_MACHINA,
  FX_MODE_DISCO,
  FX_MODE_METEOR,
  FX_MODE_COLORFALL,
  FX_MODE_SPLIT,
  FX_MODE_FLYING_SPIRIT,
  FX_MODE_PORTAL,
  FX_MODE_ROCKING
};
const uint8_t specModes[] =  {
  FX_MODE_STROBE,
  FX_MODE_MULTI_STROBE,
  FX_MODE_PARTY_STROBE,
  FX_MODE_ICU,
  FX_MODE_RAINBOW_FIREWORKS,
  FX_MODE_FILLER_UP,
  FX_MODE_VU_METER,
  FX_MODE_VU_METER_PEAK,
  FX_MODE_HEARTBEAT,
  FX_MODE_FIREFLY,
  FX_MODE_FIRE2012,
  FX_MODE_OCEAN,
  FX_MODE_ORBITA,
  FX_MODE_MACHINA
};

#else
#pragma message("- = = = = = = = = = = = = = = = -")
#pragma message("Designed for WS2812FX_MNP_EDITION")
#pragma message("- = = = = = = = = = = = = = = = -")
const uint8_t monoModes[] = {0, 1, 2, 3, 4, 5, 6, 13, 14, 15, 16, 18, 19, 21, 23, 24, 25, 26, 28, 30, 31, 34, 36, 37, 40, 43, 44, 48, 49, 50, 65, 66, 68, 70, 71 };
const uint8_t duoModes[] =  {45, 53, 54, 55, 56, 57, 64 };
const uint8_t rgbModes[] =  {7, 8, 9, 10, 11, 12, 17, 20, 22, 27, 29, 32, 33, 35, 38, 39, 42, 46, 56, 60, 62, 63, 67, 70 };
const uint8_t specModes[] =  {41, 47, 51, 52, 58, 59, 61  };
#endif


// - = = = No  user adjustment beyond this point = = = -

#if defined(ESP32)
#include <WiFi.h>
#else
// esp8266
#include <ESP8266WiFi.h>
#include <umm_malloc/umm_heap_select.h>
#ifndef CORE_MOCK
#ifndef MMU_IRAM_HEAP
#warning Try MMU option '2nd heap shared' in 'tools' IDE menu (cf. https://arduino-esp8266.readthedocs.io/en/latest/mmu.html#option-summary)
#warning use decorators: { HeapSelectIram doAllocationsInIRAM; ESPUI.addControl(...) ... } (cf. https://arduino-esp8266.readthedocs.io/en/latest/mmu.html#how-to-select-heap)
#warning then check http://<ip>/heap
#endif // MMU_IRAM_HEAP
#ifndef DEBUG_ESP_OOM
#error on ESP8266 and ESPUI, you must define OOM debug option when developping
#endif
#endif
#endif

DNSServer dnsServer;

WS2812FX lamp = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

const char * const AUTOPLAY_STATE[] PROGMEM
{
  "NONE",
  "ALL",
  "MONO",
  "DUO",
  "RGB",
  "ALL_RANDOM",
  "MONO_RANDOM",
  "DUO_RANDOM",
  "RGB_RANDOM",
};

struct WiFiData {
  char wifiSSID[34];
  char wifiPass[64];
  char wifiSSID_Ap[20];
  char wifiPass_Ap[20];
} wifidata;

typedef enum {
  P_NONE,
  P_ALL,
  P_MONO,
  P_DUO,
  P_RGB,
  P_ALL_RANDOM,
  P_MONO_RANDOM,
  P_DUO_RANDOM,
  P_RGB_RANDOM,
} MODES;

struct LampParameters {
  uint32_t  MAGIC;
  uint32_t  COLOR0;
  uint32_t  COLOR1;
  uint32_t  COLOR2;
  uint8_t   MODE;
  uint8_t   COLORMODE;
  uint16_t  SPEED;
  uint8_t   OPTION;
  uint8_t   BRI;
  uint8_t   PLAYMODE;
  uint16_t  PLAYTIME;
  uint8_t   LEDPIN;
  uint16_t  LEDCOUNT;
  uint8_t   LEDTYPE;
  uint8_t   FLAGS;
} lampParam;

// Default parameters for Initiation after reset
const LampParameters paramsDefault = {
  0,              // magic number
  MAGENTA,        // main color
  BLACK,          // background
  BLUE,           // second color
  FX_MODE_STATIC, //static
  3,              // color mode 1-MONO; 2-DUO 3-RGB  TODO: 4-Palette
  1000,           // speed
  0b00110010,     // options: X00000000 - rev?; 0XXX0000 - FADE_RATE; 0000X000 - GAMMA; 00000XX0 - SIZE_OPTION
  16,             // min bri
  5,              // auto play mode: random all
  60,             // auto play time: 1 min
  LED_PIN,        // LED Pin
  LED_COUNT,      // LED Count
  LED_TYPE,       // LED Type
  0               // additional flags
};

#define COLORMODE_MONO 1
#define COLORMODE_DUO 2
#define COLORMODE_RGB 3
#define COLORMODE_PALETTE 4 // todo

boolean auto_cycle = false;
uint8_t playMode = 0;
unsigned long auto_last_change = 0;


/* - = = = D E B U G I N G = = = - */
#if DEBUGING
#define DEBUG(s)     { Serial.print(F(s)); }
#define DEBUG2(s,v)  { Serial.print(F(s)); Serial.print(v); }
#define DEBUG2X(s,v) { Serial.print(F(s)); Serial.print(v, HEX); }
#define DEBUGN(s)     { Serial.println(F(s)); }
#define DEBUG2N(s,v)  { Serial.print(F(s)); Serial.println(v); }
#define DEBUGVN(v)    {Serial.println(v); }
#define DEBUG2XN(s,v) { Serial.print(F(s)); Serial.println(v, HEX); }
#else
#define DEBUG(s)
#define DEBUG2(s,v)
#define DEBUG2X(s,v)
#define DEBUGN(s)
#define DEBUG2N(s,v)
#define DEBUG2XN(s,v)
#endif
