/** Store WLAN credentials to EEPROM */
void saveCredentials() {
  EEPROM.put(0, wifidata);
  EEPROM.commit();
}
/** Load WLAN credentials from EEPROM */
void loadCredentials() {
  EEPROM.get(0, wifidata);
  if (String(wifidata.wifiSSID_Ap) == "") {
    DEBUGN("No Ap WiFi data stored");
  } else {
    DEBUG2("Recovered SSID_Ap:", wifidata.wifiSSID_Ap);
    DEBUG2N(" Ap Pass:", strlen(wifidata.wifiPass_Ap) > 0 ? F("********") : F("<no password>"));
  }
}
/** Save Parameters from EEPROM */
void saveParameters() {
  uint8_t addr = sizeof(wifidata) + 2;
  EEPROM.put(addr, lampParam);
  if (EEPROM.commit()) {
    Delay(10);
    //    DEBUGN("Settings saved");;
  } else {
    DEBUGN("EEPROM error");;
  }
}
/** Load Parameters from EEPROM */
void loadParameters() {
  DEBUGN("Load parameters");
  uint8_t addr = sizeof(wifidata) + 2;
  EEPROM.get(addr, lampParam);
  DEBUG2N("Loaded.  Last addr:", addr);
  DEBUG2N("MAGIC:\tHx",   lampParam.MAGIC);
  DEBUG2XN("COLOR0:\tHx", lampParam.COLOR0);
  DEBUG2XN("COLOR1:\tHx", lampParam.COLOR1);
  DEBUG2XN("COLOR2:\tHx", lampParam.COLOR2);
  DEBUG2N("Mode:\t",      lampParam.MODE);
  DEBUG2N("C_md:\t",      lampParam.COLORMODE);
  DEBUG2N("Speed:\t",     lampParam.SPEED);
  DEBUG2N("Bri:\t",       lampParam.BRI);
  DEBUG2XN("Option:\tHx", lampParam.OPTION);
  DEBUG2N("pMode:\t",     lampParam.PLAYMODE);
  DEBUG2N("pTime:\t",     lampParam.PLAYTIME);
  DEBUG2N("pL_Pin:\t",    lampParam.LEDPIN);
  DEBUG2N("pL_Count:\t",  lampParam.LEDCOUNT);
  DEBUG2N("pL_Type:\t",   lampParam.LEDTYPE);
  DEBUG2N("Revered:\t",   lampParam.OPTION  & 0x80);
  DEBUG2N("FADE:\t",   (lampParam.OPTION >> 4) & 7);
  DEBUG2N("SIZE:\t",   (lampParam.OPTION >> 1) & 3);
}

/** INIT Parameters */
void initParameters() {
  memset(wifidata.wifiSSID, 0, sizeof(wifidata.wifiSSID) - 1);
  memset(wifidata.wifiPass, 0, sizeof(wifidata.wifiPass) - 1);
#if defined(ESP32)
  uint32_t chipid = ESP32getChipId();
#else
  uint32_t chipid = ESP.getChipId();
#endif
  snprintf(wifidata.wifiSSID_Ap, 20, WIFI_AP_SSID, chipid); // default WiFi AP Name
  memset(wifidata.wifiPass_Ap, 0, sizeof(wifidata.wifiPass_Ap) - 1); // clear password

  lampParam = paramsDefault;
  lampParam.MAGIC =  chipid;

  DEBUGN("Set to default");
  saveCredentials();
  saveParameters();
}
