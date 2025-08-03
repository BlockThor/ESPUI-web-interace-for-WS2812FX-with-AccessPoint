//UI handles
uint16_t wifi_ssid_text, wifi_pass_text, wifi_ip_text, wifiap_ssid_text, wifiap_pass_text, ap_timeout;
uint16_t switchAutoPlay[10];
uint16_t statusLine, mainColour1, mainColour2, bgColor1, bgColor2, ledNumber, pinNumber, resetBttn;


void WebUI_StartUp() {
#ifdef ESP8266
  { HeapSelectIram doAllocationsInIRAM;
#endif

    // shown above all tabs
    statusLine = ESPUI.addControl(Label, "Status:", "-", Wetasphalt);
    ESPUI.setPanelStyle(statusLine, CSS_STATUS_PANEL_STYLE);
    ESPUI.setElementStyle(statusLine, CSS_STATUS_STYLE);

    uint16_t tab6 = ESPUI.addControl(ControlType::Tab, "", "Auto Play");
    uint16_t tab2 = ESPUI.addControl(ControlType::Tab, "", "Mono");
    uint16_t tab3 = ESPUI.addControl(ControlType::Tab, "", "Duo");
    uint16_t tab4 = ESPUI.addControl(ControlType::Tab, "", "RGB");
    uint16_t tab5 = ESPUI.addControl(ControlType::Tab, "", "Spec");
    uint16_t tab7 = ESPUI.addControl(ControlType::Tab, "", "Control");
    uint16_t tab8 = ESPUI.addControl(ControlType::Tab, "", "Settings");
    //    uint16_t tab1 = ESPUI.addControl(ControlType::Tab, "", "About");

    // COLORS
    static char hexcolor[10];
    sprintf(hexcolor, "#%06X", (unsigned int) lampParam.COLOR0);
    mainColour1 = ESPUI.addControl(Text, "Main Colour", hexcolor, Wetasphalt, tab2, colorCall, (void*)0);
    ESPUI.setInputType(mainColour1, "color");
    ESPUI.setElementStyle(mainColour1, CSS_COLOR_STYLE);
    //
    mainColour2 = ESPUI.addControl(Text, "Duo Colours", hexcolor, Wetasphalt, tab3, colorCall, (void*)0);
    ESPUI.setInputType(mainColour2, "color");
    ESPUI.setElementStyle(mainColour2, CSS_COLOR_STYLE);
    sprintf(hexcolor, "#%06X", (unsigned int) lampParam.COLOR2);
    auto colorElement = ESPUI.addControl(Text, "", hexcolor, Wetasphalt, mainColour2, colorCall, (void*)2);
    ESPUI.setInputType(colorElement, "color");
    ESPUI.setElementStyle(colorElement, CSS_COLOR_STYLE);

    // SHOW BUTTONS
    auto mono_label_show = ESPUI.addControl(ControlType::Label, "MONO COLOR LED SHOW:", "", Wetasphalt, tab2);
    ESPUI.setElementStyle(mono_label_show, "background-color: unset;");
    auto duo_label_show = ESPUI.addControl(ControlType::Label, "DUO COLORS LED SHOW:", "", Wetasphalt, tab3);
    ESPUI.setElementStyle(duo_label_show, "background-color: unset;");
    auto rgb_label_show = ESPUI.addControl(ControlType::Label, "RAINBOW COLORS LED SHOW:", "", Wetasphalt, tab4);
    ESPUI.setElementStyle(rgb_label_show, "background-color: unset;");
    auto spc_label_show = ESPUI.addControl(ControlType::Label, "SPECIAL LED SHOW:", "", Wetasphalt, tab5);
    ESPUI.setElementStyle(spc_label_show, "background-color: unset;");

    // BG COLORS
    sprintf(hexcolor, "#%06X", (unsigned int) lampParam.COLOR1);
    bgColor1 = ESPUI.addControl(Text, "BG Colour", hexcolor, Wetasphalt, tab2, colorCall, (void*)1);
    ESPUI.setInputType(bgColor1, "color");
    ESPUI.setElementStyle(bgColor1, CSS_COLOR_STYLE);
    bgColor2 = ESPUI.addControl(Text, "BG Colour", hexcolor, Wetasphalt, tab3, colorCall, (void*)1);
    ESPUI.setInputType(bgColor2, "color");
    ESPUI.setElementStyle(bgColor2, CSS_COLOR_STYLE);


    uint8_t num_modes = sizeof(monoModes);
    for (uint8_t i = 0; i < num_modes; i++) {
      ESPUI.setElementStyle(ESPUI.addControl(ControlType::Button, "", lamp.getModeName(monoModes[i]), Dark, mono_label_show, &monoModeCall, (void*)monoModes[i]), CSS_BTTN_UP_STYLE);
    }
    num_modes = sizeof(duoModes);
    for (uint8_t i = 0; i < num_modes; i++) {
      ESPUI.setElementStyle(ESPUI.addControl(ControlType::Button, "", lamp.getModeName(duoModes[i]), Dark, duo_label_show, &duoModeCall, (void*)duoModes[i]), CSS_BTTN_UP_STYLE);
    }
    num_modes = sizeof(rgbModes);
    for (uint8_t i = 0; i < num_modes; i++) {
      ESPUI.setElementStyle(ESPUI.addControl(ControlType::Button, "", lamp.getModeName(rgbModes[i]), Dark, rgb_label_show, &rgbModeCall, (void*)rgbModes[i]), CSS_BTTN_UP_STYLE);
    }
    num_modes = sizeof(specModes);
    for (uint8_t i = 0; i < num_modes; i++) {
      ESPUI.setElementStyle(ESPUI.addControl(ControlType::Button, "", lamp.getModeName(specModes[i]), Dark, spc_label_show, &specModeCall, (void*)specModes[i]), CSS_BTTN_UP_STYLE);
    }
    auto styleBttn = ESPUI.addControl(ControlType::Button, "Very Special Mode", "From UA with Love", Peterriver, tab5, &specModeCall, (void*)59);

    ESPUI.setPanelStyle(styleBttn, "background: linear-gradient(170deg, rgba(22,22,222,1) 0%, rgba(22,22,222,1) 33%, white 50%, rgba(176,176,0,1) 66%, rgba(176,176,0,1) 100%); border-bottom: #000;");
    //    ESPUI.setElementStyle(styleBttn, "border-radius: 2em; border: 3px solid black; width: 90%; background-color: #8df;");



    // Tab - AutoPlay - tab6
    auto autoplay_1_panel = ESPUI.addControl(Label, "Start Auto Play One-by-One:", "", Wetasphalt, tab6);
    ESPUI.setElementStyle(autoplay_1_panel, "background-color: unset;");


    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "Play All Show", Dark, autoplay_1_panel), CSS_CONTROL_LABEL_STYLE);
    switchAutoPlay[1] = ESPUI.addControl(Switcher, "", (lampParam.PLAYMODE == P_ALL ? "1" : "0"), Dark, autoplay_1_panel, &switchAutoCall);
    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "Play Mono Color Show", Dark, autoplay_1_panel), CSS_CONTROL_LABEL_STYLE);
    switchAutoPlay[2] = ESPUI.addControl(Switcher, "", (lampParam.PLAYMODE == P_MONO ? "1" : "0"), Dark, autoplay_1_panel, &switchAutoCall);
    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "Play Two Colors Show", Dark, autoplay_1_panel), CSS_CONTROL_LABEL_STYLE);
    switchAutoPlay[3] = ESPUI.addControl(Switcher, "", (lampParam.PLAYMODE == P_DUO ? "1" : "0"), Dark, autoplay_1_panel, &switchAutoCall);
    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "Play Rainbow Color Show", Dark, autoplay_1_panel), CSS_CONTROL_LABEL_STYLE);
    switchAutoPlay[4] = ESPUI.addControl(Switcher, "", (lampParam.PLAYMODE == P_RGB ? "1" : "0"), Dark, autoplay_1_panel, &switchAutoCall);

    auto autoplay_2_panel = ESPUI.addControl(Label, "Start Auto Play Random Order:", "", Wetasphalt, tab6);
    ESPUI.setElementStyle(autoplay_2_panel, "background-color: unset;");

    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "Play Random All Show", Dark, autoplay_2_panel), CSS_CONTROL_LABEL_STYLE);
    switchAutoPlay[5] = ESPUI.addControl(Switcher, "", (lampParam.PLAYMODE == P_ALL_RANDOM ? "1" : "0"), Dark, autoplay_2_panel, &switchAutoCall);
    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "Play Random Mono Color Show", Dark, autoplay_2_panel), CSS_CONTROL_LABEL_STYLE);
    switchAutoPlay[6] = ESPUI.addControl(Switcher, "", (lampParam.PLAYMODE == P_MONO_RANDOM ? "1" : "0"), Dark, autoplay_2_panel, &switchAutoCall);
    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "Play Random Two Colors Show", Dark, autoplay_2_panel), CSS_CONTROL_LABEL_STYLE);
    switchAutoPlay[7] = ESPUI.addControl(Switcher, "", (lampParam.PLAYMODE == P_DUO_RANDOM ? "1" : "0"), Dark, autoplay_2_panel, &switchAutoCall);
    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "Play Random Rainbow Color Show", Dark, autoplay_2_panel), CSS_CONTROL_LABEL_STYLE);
    switchAutoPlay[8] = ESPUI.addControl(Switcher, "", (lampParam.PLAYMODE == P_RGB_RANDOM ? "1" : "0"), Dark, autoplay_2_panel, &switchAutoCall);


    auto autoplayTimeoutSlider = ESPUI.addControl(Slider, "Next Show every _ mins", String(lampParam.PLAYTIME / 60), Wetasphalt, tab6, autoplayTimeoutSliderCall);
    ESPUI.addControl(Min, "", "1", None, autoplayTimeoutSlider);
    ESPUI.addControl(Max, "", "240", None, autoplayTimeoutSlider);
    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "00:20", None, autoplayTimeoutSlider), CSS_SLIDER_LABEL_STYLE);
    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "|", None, autoplayTimeoutSlider), CSS_SLIDER_LABEL_STYLE);
    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "02:20", None, autoplayTimeoutSlider), CSS_SLIDER_LABEL_STYLE);
    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "|", None, autoplayTimeoutSlider), CSS_SLIDER_LABEL_STYLE);
    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "03:30", None, autoplayTimeoutSlider), CSS_SLIDER_LABEL_STYLE);
    ESPUI.setElementStyle(ESPUI.addControl(Label, "", " ", None, autoplayTimeoutSlider), String(CSS_SLIDER_LABEL_STYLE) + "width:8%;");

    auto autoplay_3_panel = ESPUI.addControl(Label, "Stop Auto Play", "", Wetasphalt, tab6);
    ESPUI.setElementStyle(autoplay_3_panel, "background-color: unset;");
    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "AutoPlay disable", Dark, autoplay_3_panel), CSS_CONTROL_LABEL_STYLE);
    switchAutoPlay[0] = ESPUI.addControl(Switcher, "", (lampParam.PLAYMODE == P_NONE ? "1" : "0"), Dark, autoplay_3_panel, &switchAutoCall);

    ESPUI.updateVisibility(ESPUI.addControl(Label, "1", "1", None, autoplay_3_panel), false);

    // CONTROLS    - tab7
    // Control Panel
    auto control_panel = ESPUI.addControl(Label, "Power:", "", Wetasphalt, tab7);
    ESPUI.setElementStyle(control_panel, "background-color: unset;");
    // Power switch
    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "Power (on/off)", Dark, control_panel), CSS_CONTROL_LABEL_STYLE);
    ESPUI.addControl(Switcher, "", "1", Dark, control_panel, &switchPowerCall);

    // Bri slider
    auto briSlider = ESPUI.addControl(Slider, "Brightness", String(lamp.getBrightness()), Wetasphalt, tab7, briSliderCall);
    ESPUI.addControl(Min, "", "8", None, briSlider);
    ESPUI.addControl(Max, "", "254", None, briSlider);
    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "Min", None, briSlider), CSS_SLIDER_LABEL_STYLE);
    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "Light", None, briSlider), CSS_SLIDER_LABEL_STYLE);
    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "Norm", None, briSlider), CSS_SLIDER_LABEL_STYLE);
    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "Good", None, briSlider), CSS_SLIDER_LABEL_STYLE);
    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "Max", None, briSlider), CSS_SLIDER_LABEL_STYLE);
    ESPUI.setElementStyle(ESPUI.addControl(Label, "", " ", None, briSlider), String(CSS_SLIDER_LABEL_STYLE) + "width:8%;");

    // Speed slider
    auto speedSlider = ESPUI.addControl(Slider, "Speed", String(lamp.getSpeed() / 10), Wetasphalt, tab7, speedSliderCall);
    ESPUI.addControl(Min, "", "5", None, speedSlider);
    ESPUI.addControl(Max, "", "200", None, speedSlider);
    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "Faster", None, speedSlider), CSS_SLIDER_LABEL_STYLE);
    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "Fast", None, speedSlider), CSS_SLIDER_LABEL_STYLE);
    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "Norm", None, speedSlider), CSS_SLIDER_LABEL_STYLE);
    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "Slow", None, speedSlider), CSS_SLIDER_LABEL_STYLE);
    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "Slower", None, speedSlider), CSS_SLIDER_LABEL_STYLE);
    ESPUI.setElementStyle(ESPUI.addControl(Label, "", " ", None, speedSlider), String(CSS_SLIDER_LABEL_STYLE) + "width:8%;");

    //tab8

    ESPUI.setElementStyle(tab8, "color: red;");
    ESPUI.setPanelStyle(tab8, "color: blue;");
    //     WiFi Credentials (in case should be connected to exist WiFi - removed for this moment
    //    ESPUI.addControl(Separator, "WiFi Credentials ", "", None, tab8);
    //    auto wifi_web = ESPUI.addControl(Label, "WiFi Credentials (left empty for ignore WiFi)", "", Wetasphalt, tab8);
    //    ESPUI.setElementStyle(wifi_web, "background-color: unset;");
    //    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "SSID (WiFi Name)", Dark, wifi_web), CSS_TEXT_LABEL_STYLE);
    //    wifi_ssid_text = ESPUI.addControl(Text, "", String(wifidata.wifiSSID), Wetasphalt, wifi_web, textCall);
    //    ESPUI.setElementStyle(wifi_ssid_text, CSS_TEXT_STYLE);
    //    ESPUI.addControl(Max, "", "32", None, wifi_ssid_text);
    //    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "Password", Dark, wifi_web), CSS_TEXT_LABEL_STYLE);
    //    wifi_pass_text = ESPUI.addControl(Text, "", String(wifidata.wifiPass), Dark, wifi_web, textCall);
    //    ESPUI.setElementStyle(wifi_pass_text, CSS_TEXT_STYLE);
    //    ESPUI.addControl(Max, "", "64", None, wifi_pass_text);
    //    ESPUI.setElementStyle(ESPUI.addControl(Button, "", "Save & Apply", Dark, wifi_web, enterWifiDetailsCallback), CSS_SAVEBUTTON_STYLE);

    // WiFi AP Credentials
    ESPUI.addControl(Separator, "WiFi Access Point Credentials ", "", None, tab8);
    auto wifiap_web = ESPUI.addControl(Label, "WiFi Access Point Credentials", "", Wetasphalt, tab8);
    ESPUI.setElementStyle(wifiap_web, "background-color: unset;");

    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "SSID ", Dark, wifiap_web), CSS_TEXT_LABEL_STYLE);
    wifiap_ssid_text = ESPUI.addControl(Text, "", String(wifidata.wifiSSID_Ap), Wetasphalt, wifiap_web, textCall);
    ESPUI.setElementStyle(wifiap_ssid_text, CSS_TEXT_STYLE);
    ESPUI.addControl(Max, "", "20", None, wifiap_ssid_text);

    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "Password AP", Wetasphalt, wifiap_web), CSS_TEXT_LABEL_STYLE);
    wifiap_pass_text = ESPUI.addControl(Text, "", String(wifidata.wifiPass_Ap), Wetasphalt, wifiap_web, textCall);
    ESPUI.setElementStyle(wifiap_pass_text, CSS_TEXT_STYLE);
    ESPUI.addControl(Max, "", "20", None, wifiap_pass_text);

    //    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "IP Adress", Dark, wifiap_web), CSS_TEXT_LABEL_STYLE);
    //    wifi_ip_text = ESPUI.addControl(Text, "", apIP.toString(), Dark, wifiap_web, textCall);
    //    ESPUI.setElementStyle(wifi_ip_text, CSS_TEXT_STYLE);
    //    ESPUI.addControl(Max, "", "16", None, wifi_ip_text);

    //    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "AP Timeout:", Dark, wifiap_web), CSS_TEXT_LABEL_STYLE);
    //    ap_timeout = ESPUI.addControl(Text, "", "00:20", Dark, wifiap_web, textCall);
    //    ESPUI.setElementStyle(ap_timeout, CSS_TEXT_STYLE);
    //    ESPUI.setInputType(ap_timeout, "time");
    ESPUI.setElementStyle(ESPUI.addControl(Button, "", "Save & Apply", Dark, wifiap_web, enterWifiAPDetailsCallback), CSS_SAVEBUTTON_STYLE);

    // Soft panel
    ESPUI.addControl(Separator, "Sofware settings:", "", Wetasphalt, tab8);
    auto soft_panel = ESPUI.addControl(Label, "Software Settings:", "", Wetasphalt, tab8);
    ESPUI.setElementStyle(soft_panel, "background-color: unset;");
    // Direction switch
    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "Reversed", Dark, soft_panel), CSS_CONTROL_LABEL_STYLE);
    ESPUI.addControl(Switcher, "", (lamp.getOptions(0) & 128  == 128) ? "1" : "0" , Dark, soft_panel, &switchReversCall);

    // ELEMENT_SIZE
    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "ELEMENT_SIZE", Dark, soft_panel), CSS_SELECT_LABEL_STYLE);
    static String optionSIZE[] {"0", "0", "2", "4", "6"};
    optionSIZE[0] = String(lamp.getOptions(0)&SIZE_XLARGE);
    auto sizeSelector = ESPUI.addControl(Select, "", "ELS", Dark, soft_panel, selectSizeCall);
    ESPUI.setElementStyle(sizeSelector, CSS_NUMBER_STYLE);
    for (auto const& v : optionSIZE) {
      ESPUI.addControl(Option, v.c_str(), v, None, sizeSelector);
    }
    // FADE_RATE
    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "FADE_RATE", Dark, soft_panel), CSS_SELECT_LABEL_STYLE);
    static String optionFADE[] {"0", "1", "2", "3", "4", "5"};
    optionFADE[0] = String((lamp.getOptions(0)&FADE_GLACIAL) / 16);
    auto fadeSelector = ESPUI.addControl(Select, "", "FR", Dark, soft_panel, selectFadeCall);
    ESPUI.setElementStyle(fadeSelector, CSS_NUMBER_STYLE);
    for (auto const& v : optionFADE) {
      ESPUI.addControl(Option, v.c_str(), v, None, fadeSelector);
    }


    // Hard panel
    ESPUI.addControl(Separator, "Hardware settings, save to apply", "", None, tab8);
    auto hard_panel = ESPUI.addControl(Label, "Hardware Settings:", "", Wetasphalt, tab8);
    ESPUI.setElementStyle(hard_panel, "background-color: unset;");
    // Number of LEDs
    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "Number of LEDs", Dark, hard_panel), CSS_NUMBER_LABEL_STYLE);
    ledNumber = ESPUI.addControl(Number, "", String(lamp.getLength()), Dark, hard_panel, &numberCall);
    ESPUI.setElementStyle(ledNumber, CSS_NUMBER_STYLE);
    // Pin number
    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "Pin number", Dark, hard_panel), CSS_NUMBER_LABEL_STYLE);
    pinNumber = ESPUI.addControl(Number, "", String(lampParam.LEDPIN), Dark, hard_panel, &numberCall);
    ESPUI.setElementStyle(pinNumber, CSS_NUMBER_STYLE);
    // Type of LEDs
    //    ESPUI.setElementStyle(ESPUI.addControl(Label, "", "Type of LEDs", Dark, hard_panel), CSS_NUMBER_LABEL_STYLE);
    //    static String optionValues[] {"RGB", "RBG", "GRB", "GBR", "BRG", "BGR"};
    //    auto mainselector = ESPUI.addControl(Select, "Selector", "Selector", Wetasphalt, hard_panel, selectSizeCall);
    //    ESPUI.addControl(Option, "ToDo", "na", None, mainselector);
    //    ESPUI.setElementStyle(mainselector, CSS_NUMBER_STYLE);
    //    for (auto const& v : optionValues) {
    //      ESPUI.addControl(Option, v.c_str(), v, None, mainselector);
    //    }
    //Save Button
    ESPUI.setElementStyle(ESPUI.addControl(Button, "", "Save & Apply", Dark, hard_panel, &saveHardCall), CSS_SAVEBUTTON_STYLE);

    ESPUI.addControl(Separator, "Restart / Reset section</br>(be caution)", "", None, tab8);
    ESPUI.setElementStyle(ESPUI.addControl(Button, "Restart System", "Restart Now", Dark, tab8, &restartCall), CSS_SAVEBUTTON_STYLE);
    resetBttn = ESPUI.addControl(Button, "Reset Settings to default</br>(hold 5+ sec)", "Reset Now", Dark, tab8, &resetCall);
    ESPUI.setElementStyle(resetBttn, CSS_SAVEBUTTON_STYLE);

    //    ESPUI.updateVisibility(ESPUI.addControl(Label, "3", "Plug", Wetasphalt), false);

    ESPUI.begin(HTML_TITLE);
    updateStatusLine();
#ifdef ESP8266
  } // HeapSelectIram
#endif
}



void updateStatusLine() {
  String statusString = "[ " + (String)lamp.getModeName(lamp.getMode());
  if (lampParam.COLORMODE == COLORMODE_MONO) {
    statusString += " / Mono ]";
  } else if (lampParam.COLORMODE == COLORMODE_DUO) {
    statusString += " / Duo ]";
  } else if (lampParam.COLORMODE == COLORMODE_RGB) {
    statusString += " / RGB ]";
  }
  if (lampParam.PLAYMODE) {
    statusString += (String("<br><small>AutoPlay: ") + AUTOPLAY_STATE[lampParam.PLAYMODE]);
    statusString += (String("; Every: ") + lampParam.PLAYTIME / 60) + " mins</small>";
  }
  ESPUI.updateText(statusLine, statusString);
  saveParameters();
  DEBUGVN(statusString);
}
void disableAutoPlay() {
  for (uint8_t i = 1; i < 10; i++) {
    ESPUI.updateControlValue(switchAutoPlay[i], "0" );
  }
  ESPUI.updateControlValue(switchAutoPlay[0], "1" );
  lampParam.MODE = lamp.getMode();
  lampParam.PLAYMODE = P_NONE;
  saveParameters();
}
