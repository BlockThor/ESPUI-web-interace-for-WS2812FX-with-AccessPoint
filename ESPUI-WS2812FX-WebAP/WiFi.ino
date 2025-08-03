void WiFi_StartUp() {
  loadCredentials();

  uint8_t timeout = 10;

  WiFi.mode(WIFI_MODE_AP);
  WiFi.softAPConfig(localIP, gatewayIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(wifidata.wifiSSID_Ap, wifidata.wifiPass_Ap);

  timeout = 5;

  dnsServer.setTTL(3600);
  dnsServer.start(DNS_PORT, "*", localIP);
  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
}

void WiFi_Running() {
  dnsServer.processNextRequest();  
}

uint32_t ESP32getChipId() {
  uint32_t chipid = 0;
  for (int i = 0; i < 17; i = i + 8)
  {
    chipid |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
  }
  return chipid;
}
