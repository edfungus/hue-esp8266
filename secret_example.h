#ifndef secret_h
#define secret_h

char WIFI_SSID[ ] = "???";
char WIFI_PASSWORD[ ] = "???";
char HUE_USERNAME[ ] = "???";

class Secret
{
  public:
    Secret();
    char* getWifiSSID();
    char* getWifiPassword();
    char* getHueUsername();
};

Secret::Secret(){}

char* Secret::getWifiSSID()
{
  return WIFI_SSID;
}
char* Secret::getWifiPassword()
{
  return WIFI_PASSWORD;
}
char* Secret::getHueUsername()
{
  return HUE_USERNAME;
}

#endif