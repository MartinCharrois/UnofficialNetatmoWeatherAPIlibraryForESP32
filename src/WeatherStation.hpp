#pragma once
#ifndef Arduino
    #include "Arduino.h"
    #define Arduino
#endif
#ifndef EXTERNAL_LIBRARIES
    #include <HTTPClient.h>
    #include "time.h"
    #ifndef ARDUINO_JSON
        #include "ArduinoJson.h"
        #define ARDUINO_JSON
    #endif
    #define EXTERNAL_LIBRARIES
#endif

#include "Modules/IndoorModule.hpp"
#include "Modules/StationModule.hpp"
#include "Modules/OutdoorModule.hpp"
#include "Modules/RainGauge.hpp"
#include "modules/WindModule.hpp"
#include "Token.hpp"
#include <vector>

using namespace std;

class WeatherStation{
public:
    WeatherStation();
    WeatherStation(Token* token);

    bool init(JsonObject WeatherStationData);
    bool init(Token* token);
    bool update();
    bool update(JsonObject WeatherStationData);
    String makeRequestGetStationsData(bool getFavoriteStationData = false, String StationMacAddress = "");

    StationModule* getStationModulePointer();
    IndoorModule* getIndoorModulePointer();
    OutdoorModule* getOutdoorModulePointer();
    RainGauge* getRainGaugePointer();
    WindModule* getWindModulePointer();
    Token* getTokenPointer();
    uint8_t getWifiStatus();
    bool isCalibratingCO2Sensor();
    String getTimezone();
    String getCountry();
    String getCity();
    String getStreet();
    uint16_t getAltitude();
    float getLatitude();
    float getLongitude();
    String getStationHomeName();
    uint16_t getHardwareVersion();

    String generateStationStatusReport();
    String generateFullStatusReport();
    ~WeatherStation();
private:
    Token* token_;
    StationModule* stationModule_;
    vector<IndoorModule*> indoorModules_;
    vector<OutdoorModule*> outdoorModules_;
    RainGauge* rainGauge_;
    WindModule* windModule_;

    uint8_t Wifi_status_;
    bool calibrating_CO2_sensor_;
    String timezone_;
    String country_;
    String city_;
    String street_;
    uint16_t altitude_;
    float latitude_;
    float longitude_;
    String home_name_;
};