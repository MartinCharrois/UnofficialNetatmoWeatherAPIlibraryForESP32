#include <unity.h>
#include <WeatherStation.hpp>
#include "testData.hpp"

WeatherStation test_station;


void setUp(void){}
void tearDown(void){}

void test_init_method(void){
    JsonObject wheatherStationData;
    TEST_ASSERT_FALSE(test_station.init(wheatherStationData));

    DynamicJsonDocument doc(8192);
    deserializeJson(doc, rawWeatherStationData);
    wheatherStationData = doc.as<JsonObject>()["body"]["devices"][0];
    TEST_ASSERT_TRUE(test_station.init(wheatherStationData));
}

void test_getWifiStatus_method(void){
    TEST_ASSERT_EQUAL_UINT8(52,test_station.getWifiStatus());
}

void test_isCalibratingCO2Sensor_method(void){
    TEST_ASSERT_FALSE(test_station.isCalibratingCO2Sensor());
}

void test_getTimezone_method(void){
    String timezoneStr = test_station.getTimezone();
    char timezone[timezoneStr.length()+1];
    timezoneStr.toCharArray(timezone, timezoneStr.length()+1);
    TEST_ASSERT_EQUAL_STRING("Europe/Paris",timezone);
}

void test_getCountry_method(void){
    String CountryStr = test_station.getCountry();
    char Country[CountryStr.length()+1];
    CountryStr.toCharArray(Country, CountryStr.length()+1);
    TEST_ASSERT_EQUAL_STRING("FR",Country);
}

void test_getCity_method(void){
    String CityStr = test_station.getCity();
    char City[CityStr.length()+1];
    CityStr.toCharArray(City, CityStr.length()+1);
    TEST_ASSERT_EQUAL_STRING("test city",City);
}

void test_getStreet_method(void){
    String StreetStr = test_station.getStreet();
    char Street[StreetStr.length()+1];
    StreetStr.toCharArray(Street, StreetStr.length()+1);
    TEST_ASSERT_EQUAL_STRING("test street",Street);
}

void test_getAltitude_method(void){
    TEST_ASSERT_EQUAL_UINT16(100, test_station.getAltitude());
}

void test_getLatitude_method(void){
    TEST_ASSERT_EQUAL_FLOAT(2.335128500000, test_station.getLatitude());
}

void test_getLongitude_method(void){
    TEST_ASSERT_EQUAL_FLOAT(48.85889370000000, test_station.getLongitude());
}

void test_getStationHomeName_method(void){
    String StationHomeNameStr = test_station.getStationHomeName();
    char StationHomeName[StationHomeNameStr.length()+1];
    StationHomeNameStr.toCharArray(StationHomeName, StationHomeNameStr.length()+1);
    TEST_ASSERT_EQUAL_STRING("test home",StationHomeName);
}

void test_getStationModulePointer_method(void){
    StationModule* stationModule = test_station.getStationModulePointer();
    String generalStatus = stationModule->generateStatusReport();
    char stationModuleStatus[generalStatus.length()+1];
    generalStatus.toCharArray(stationModuleStatus, generalStatus.length()+1);
    TEST_ASSERT_EQUAL_STRING(stationModuleRefGeneralStatus,stationModuleStatus);
}

void test_getOutdoorModulePointer_method(void){
    OutdoorModule* OutdoorModule = test_station.getOutdoorModulePointer();
    String generalStatus = OutdoorModule->generateStatusReport();
    char OutdoorModuleStatus[generalStatus.length()+1];
    generalStatus.toCharArray(OutdoorModuleStatus, generalStatus.length()+1);
    TEST_ASSERT_EQUAL_STRING(outdoorModuleRefGeneralStatus,OutdoorModuleStatus);
}

void test_getIndoorModulePointer_method(void){
    IndoorModule* IndoorModule = test_station.getIndoorModulePointer();
    String generalStatus = IndoorModule->generateStatusReport();
    char IndoorModuleStatus[generalStatus.length()+1];
    generalStatus.toCharArray(IndoorModuleStatus, generalStatus.length()+1);
    TEST_ASSERT_EQUAL_STRING(indoorModuleRefGeneralStatus,IndoorModuleStatus);
}

void test_getRainGaugePointer_method(void){
    RainGauge* RainGauge = test_station.getRainGaugePointer();
    String generalStatus = RainGauge->generateStatusReport();
    char RainGaugeStatus[generalStatus.length()+1];
    generalStatus.toCharArray(RainGaugeStatus, generalStatus.length()+1);
    TEST_ASSERT_EQUAL_STRING(rainGaugeRefGeneralStatus,RainGaugeStatus);
}

void test_getWindModulePointer_method(void){
    WindModule* WindModule = test_station.getWindModulePointer();
    String generalStatus = WindModule->generateStatusReport();
    char WindModuleStatus[generalStatus.length()+1];
    generalStatus.toCharArray(WindModuleStatus, generalStatus.length()+1);
    TEST_ASSERT_EQUAL_STRING(windModuleRefGeneralStatus,WindModuleStatus);
}

void test_generateStationStatusReport_method(void){
    String generalStatus = test_station.generateStationStatusReport();
    char stationStatus[generalStatus.length()+1];
    generalStatus.toCharArray(stationStatus, generalStatus.length()+1);
    TEST_ASSERT_EQUAL_STRING(refStationStatus,stationStatus);
}

void test_generateFullStatusReport_method(void){
    String generalStatus = test_station.generateFullStatusReport();
    char fullStatus[generalStatus.length()+1];
    generalStatus.toCharArray(fullStatus, generalStatus.length()+1);
    TEST_ASSERT_EQUAL_STRING(refFullStatus,fullStatus);
}

void test_update_method(void){
    JsonObject wheatherStationDataForUpdate;
    TEST_ASSERT_FALSE(test_station.update(wheatherStationDataForUpdate));

    DynamicJsonDocument doc(4096);
    deserializeJson(doc, rawWeatherStationDataForUpdate);
    wheatherStationDataForUpdate = doc.as<JsonObject>()["body"]["devices"][0];
    TEST_ASSERT_TRUE(test_station.update(wheatherStationDataForUpdate));

    String generalStatus = test_station.generateFullStatusReport();
    char fullStatusUpdated[generalStatus.length()+1];
    generalStatus.toCharArray(fullStatusUpdated, generalStatus.length()+1);
    TEST_ASSERT_EQUAL_STRING(refFullStatusUpdated,fullStatusUpdated);
}

void setup(void){
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();
    RUN_TEST(test_init_method);
    RUN_TEST(test_getWifiStatus_method);
    RUN_TEST(test_isCalibratingCO2Sensor_method);
    RUN_TEST(test_getTimezone_method);
    RUN_TEST(test_getCountry_method);
    RUN_TEST(test_getCity_method);
    RUN_TEST(test_getStreet_method);
    RUN_TEST(test_getAltitude_method);
    RUN_TEST(test_getLatitude_method);
    RUN_TEST(test_getLongitude_method);
    RUN_TEST(test_getStationHomeName_method);

    RUN_TEST(test_getStationModulePointer_method);
    RUN_TEST(test_getOutdoorModulePointer_method);
    RUN_TEST(test_getIndoorModulePointer_method);
    RUN_TEST(test_getRainGaugePointer_method);
    RUN_TEST(test_getWindModulePointer_method);
    RUN_TEST(test_generateStationStatusReport_method);
    RUN_TEST(test_generateFullStatusReport_method);
    RUN_TEST(test_update_method);
    UNITY_END();
}

void loop(void){
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(500);
}