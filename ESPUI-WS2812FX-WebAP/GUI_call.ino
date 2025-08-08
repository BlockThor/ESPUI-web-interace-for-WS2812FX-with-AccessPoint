void autoplayTimeoutSliderCall(Control* sender, int type)
{

  DEBUG2("TimeoutSlider: ", sender->value);
  int sliderValue = sender->value.toInt() * 60;
  if (sliderValue < 60) sliderValue = 60;
  DEBUG2N(", Value: ", sliderValue);
  lampParam.PLAYTIME = sliderValue;
  updateStatusLine();
}
void briSliderCall(Control* sender, int type)
{
  DEBUG2("Slider: ID: ", sender->id);
  DEBUG2N(", Value: ", sender->value);
  int sliderValue = sender->value.toInt();
  lamp.setBrightness(sliderValue);
  lampParam.BRI = lamp.getBrightness();
  updateStatusLine();
}
void speedSliderCall(Control* sender, int type)
{
  DEBUG2("Slider: ID: ", sender->id);
  DEBUG2N(", Value: ", sender->value);
  int sliderValue = sender->value.toInt() * 10;
  if (sliderValue == 2000) {
    sliderValue *= 10; // when max slower make it super slow
  } else if (sliderValue > 1800) {
    sliderValue *= 2; // when slower make it very slow
  }
  lamp.setSpeed(sliderValue);
  lampParam.SPEED = lamp.getSpeed();
  updateStatusLine();
}
void saveHardCall(Control* sender, int type)
{
  if (type == B_UP) {
    lamp.stop();
    int n = ESPUI.getControl(pinNumber)->value.toInt();
    lampParam.LEDPIN = n;
    lamp.setPin(n);
    n = ESPUI.getControl(ledNumber)->value.toInt();
    lampParam.LEDCOUNT = n;
    lamp.setLength(n);
    lamp.start();
    updateStatusLine();
    ESPUI.setElementStyle(sender->id, CSS_SAVEBUTTON_STYLE);
  } else {
    ESPUI.setElementStyle(sender->id, String(CSS_SAVEBUTTON_STYLE) + CSS_SAVEBUTTON_DOWN_STYLE);
  }
}

void enterWifiDetailsCallback(Control *sender, int type) {
  if (type == B_UP) {
    DEBUGN("Saving credentials WiFi...");
    String _ssid = ESPUI.getControl(wifi_ssid_text)->value;
    DEBUG2N("SSID:", _ssid);
    String _pass = ESPUI.getControl(wifi_pass_text)->value;
    DEBUG2N("Pass:", _pass);
    if (_ssid == "") { // AP WiFi name can't be empty - set default
      DEBUGN("set credentials to default");
      memset(wifidata.wifiPass, 0, sizeof(wifidata.wifiPass) - 1); // clear name
      memset(wifidata.wifiPass, 0, sizeof(wifidata.wifiPass) - 1); // clear password

    } else {
      _ssid.toCharArray(wifidata.wifiSSID, sizeof(wifidata.wifiSSID) - 1);
      _pass.toCharArray(wifidata.wifiPass, sizeof(wifidata.wifiPass) - 1);
    }
    DEBUG2N("SSID:", wifidata.wifiSSID);
    //    DEBUG2N("Pass:",wifidata.wifiPass);
  }
  saveCredentials();
}
void enterWifiAPDetailsCallback(Control *sender, int type) {
  if (type == B_UP) {
    DEBUGN("Saving credentials WiFi AP...");
    String _ssid = ESPUI.getControl(wifiap_ssid_text)->value;
    DEBUG2N("SSID:", _ssid);
    String _pass = ESPUI.getControl(wifiap_pass_text)->value;
    DEBUG2N("Pass:", _pass);
    //    String _ip = ESPUI.getControl(wifi_ip_text)->value;
    if (_ssid == "") { // AP WiFi name can't be empty - set default
      DEBUGN("set credentials to default");
#if defined(ESP32)
      uint32_t chipid = ESP32getChipId();
#else
      uint32_t chipid = ESP.getChipId();
#endif
      snprintf(wifidata.wifiSSID_Ap, 20, WIFI_AP_SSID, chipid); // default WiFi AP Name
      memset(wifidata.wifiPass_Ap, 0, sizeof(wifidata.wifiPass_Ap) - 1); // clear password
      _ssid = String(wifidata.wifiSSID_Ap);
      ESPUI.updateControlValue(wifiap_ssid_text, _ssid);
    } else {
      _ssid.toCharArray(wifidata.wifiSSID_Ap, sizeof(wifidata.wifiSSID_Ap) - 1);
      _pass.toCharArray(wifidata.wifiPass_Ap, sizeof(wifidata.wifiPass_Ap) - 1);
    }
    DEBUG2N("SSID:", _ssid);
    //    DEBUGN(_pass);
    saveCredentials();
    ESPUI.setElementStyle(sender->id, CSS_SAVEBUTTON_STYLE);
//    ESP.restart();
  } else {
    ESPUI.setElementStyle(sender->id, String(CSS_SAVEBUTTON_STYLE) + CSS_SAVEBUTTON_DOWN_STYLE);
  }
}

void restartCall(Control * sender, int type)
{
  switch (type)
  {
    case B_DOWN:
      ESPUI.setElementStyle(sender->id, String(CSS_SAVEBUTTON_STYLE) + CSS_SAVEBUTTON_DOWN_STYLE);
      break;

    case B_UP:
      ESP.restart();
      ESPUI.setElementStyle(sender->id, CSS_SAVEBUTTON_STYLE);
      break;
  }
}

void resetCall(Control * sender, int type) {
  DEBUGN("Reset");
  unsigned long currentMillis = millis();
  static unsigned long oldMillis = 0;

  switch (type) {
    case B_DOWN:
      oldMillis = millis();
      ESPUI.setPanelStyle(sender->id, CSS_ALARM_PANEL_STYLE); // Red Panel Name.
      ESPUI.setElementStyle(sender->id, String(CSS_SAVEBUTTON_STYLE) + CSS_SAVEBUTTON_DOWN_STYLE);
      break;

    case B_UP:
      if (currentMillis > oldMillis + 5000) {
        initParameters();
        delay(500);
        ESP.restart();
      } else {
        ESPUI.setPanelStyle(sender->id, ";"); // Clear style
        ESPUI.setElementStyle(sender->id, CSS_SAVEBUTTON_STYLE);
      }
      break;
    default:
      break;
  }
}
// - - -
void numberCall(Control * sender, int type)
{
  DEBUG2N("Number", sender->value);
}

void textCall(Control * sender, int type)
{
  DEBUG2N("Text: ID: ", sender->id);
  DEBUG2N(", Value: ", sender->value);
}

void selectSizeCall(Control * sender, int value)
{
  String v = sender->value;
  uint8_t opts = lamp.getOptions(0);
  uint8_t p = (uint8_t)v.toInt();
  opts &= ~SIZE_XLARGE;
  opts |= p;
  lamp.setOptions(0, opts);
  lampParam.OPTION = lamp.getOptions(0);
  updateStatusLine();

  DEBUG2N(", Label: ", sender->label);
  DEBUG2N(", Value: ", sender->value);
  DEBUG2N(", Int: ", p);
}

void selectFadeCall(Control * sender, int value)
{
  String v = sender->value;
  uint8_t opts = lamp.getOptions(0);
  uint8_t p = (uint8_t)v.toInt() * 16;
  //  if (p == 0) p = 16;
  opts &= ~FADE_GLACIAL;
  opts |= p;
  lamp.setOptions(0, opts);
  lampParam.OPTION = lamp.getOptions(0);
  updateStatusLine();

  DEBUG2N(", Label: ", sender->label);
  DEBUG2N(", Value: ", sender->value);
  DEBUG2N(", Int: ", p);
}
// S W I T C H s
void switchReversCall(Control * sender, int value)
{
  uint8_t opts = lamp.getOptions(0);
  if (value == S_ACTIVE) {
    lamp.setOptions(0, opts | 0x80);
  } else {
    lamp.setOptions(0, opts & ~0x80);
  }
  lampParam.OPTION = lamp.getOptions(0);
  updateStatusLine();
  DEBUG2X("Reversed: ", lamp.getOptions(0) & 0x80);
  DEBUG2("  ", (((lamp.getOptions(0) & 0x80)  == 128) ? "1" : "0"));
}
void switchPowerCall(Control * sender, int value)
{
  if (value == S_ACTIVE) {
    lamp.start();
  } else {
    lamp.stop();
  }
  updateStatusLine();
}

void switchAutoCall(Control * sender, int value)
{

  if (value == S_ACTIVE) {
    for (uint8_t i = 0; i < 10; i++) {
      if (switchAutoPlay[i] != sender->id) {
        ESPUI.updateControlValue(switchAutoPlay[i], "0" );
      } else {
        lampParam.PLAYMODE = i;
        auto_last_change = 0;
      }
    }
  } else {
    if (switchAutoPlay[0] != sender->id) { // if unswitch any mode -> switch on StopAutoPlay
      ESPUI.updateControlValue(switchAutoPlay[0], "1" );
      lampParam.PLAYMODE = 0;
      auto_last_change = 0;
    } else { // if unswitch StopSutoPlay -> switch on default AutoPlayMode
      ESPUI.updateControlValue(switchAutoPlay[paramsDefault.PLAYMODE], "1");
      lampParam.PLAYMODE = paramsDefault.PLAYMODE;
      auto_last_change = 0;
    }
  }
  updateStatusLine();
}

//  MODE CALLs
void monoModeCall(Control * sender, int type, void* param)
{
  int n = (int)param;
  if (type == B_UP) {
    lamp.setMode(n);
    setColorMode(COLORMODE_MONO);
    lampParam.COLORMODE = COLORMODE_MONO;
    disableAutoPlay();
    lampParam.MODE = lamp.getMode();
    lampParam.PLAYMODE = P_NONE;
    ESPUI.setElementStyle(sender->id, CSS_SHOWBUTTON_UP_STYLE);
    updateStatusLine();
  } else {
    ESPUI.setElementStyle(sender->id, CSS_SHOWBUTTON_DW_STYLE);
  }
}
void duoModeCall(Control * sender, int type, void* param)
{
  int n = (int)param;
  if (type == B_UP) {
    lamp.setMode(n);
    setColorMode(COLORMODE_DUO);
    //    lampParam.COLORMODE = COLORMODE_DUO;
    disableAutoPlay();
    ESPUI.setElementStyle(sender->id, CSS_SHOWBUTTON_UP_STYLE);
    updateStatusLine();
  } else {
    ESPUI.setElementStyle(sender->id, CSS_SHOWBUTTON_DW_STYLE);
  }
}
void rgbModeCall(Control * sender, int type, void* param)
{
  int n = (int)param;
  if (type == B_UP) {
    lamp.setMode(n);
    setColorMode(COLORMODE_RGB);
    //    lampParam.COLORMODE = COLORMODE_RGB;
    disableAutoPlay();
    ESPUI.setElementStyle(sender->id, CSS_SHOWBUTTON_UP_STYLE);
    updateStatusLine();
  } else {
    ESPUI.setElementStyle(sender->id, CSS_SHOWBUTTON_DW_STYLE);
  }
}
void specModeCall(Control * sender, int type, void* param)
{
  int n = (int)param;
  if (type == B_UP) {
    lamp.setMode(n);
    setColorMode(COLORMODE_DUO);
    //    lampParam.COLORMODE = COLORMODE_DUO;
    disableAutoPlay();
    ESPUI.setElementStyle(sender->id, CSS_SHOWBUTTON_UP_STYLE);
    updateStatusLine();
  } else {
    ESPUI.setElementStyle(sender->id, CSS_SHOWBUTTON_DW_STYLE);
  }
}

void colorCall(Control * sender, int type, void* param)
{
  String tmpColor = sender->value;
  tmpColor.remove(0, 1);
  uint32_t rcvdColor = strtol(tmpColor.c_str(), NULL, 16);
  int n = (int)param;

  if (n == 0) {
    lampParam.COLOR0 = rcvdColor;
  }
  else if (n == 1) {
    lampParam.COLOR1 = rcvdColor;
  }
  else if (n == 2) {
    lampParam.COLOR2 = rcvdColor;
  }
  applyColors();

  if (sender->id == mainColour1) // Update color on all tabs
    ESPUI.updateText(mainColour2, sender->value);
  else if (sender->id == mainColour2)
    ESPUI.updateText(mainColour1, sender->value);
  else if (sender->id == bgColor1)
    ESPUI.updateText(bgColor2, sender->value);
  else if (sender->id == bgColor2)
    ESPUI.updateText(bgColor1, sender->value);

  DEBUG2("color is ", sender->value);
  DEBUG2N(" pos is ", n);
}
