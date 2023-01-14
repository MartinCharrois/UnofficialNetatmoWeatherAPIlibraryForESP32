#include <unity.h>
#include <Modules/StationModule.hpp>
#include "../modules_tests_datas.h"

StationModule stationModule;

void setUp(void){}
void tearDown(void){}

void test_init_method(void){
    JsonObject nonDefinedJson;
    TEST_ASSERT(!stationModule.init(nonDefinedJson));

    DynamicJsonDocument doc(2048);
    deserializeJson(doc, module_data_reachable_string);
    JsonObject indoor_module_datas = doc.as<JsonObject>();
    TEST_ASSERT(stationModule.init(indoor_module_datas));
}

void test_getMeasureTimestamp_method(void){
    TEST_ASSERT_EQUAL_UINT32(1668718779, stationModule.getMeasureTimestamp());
}

void test_getTemperatureCelsius_method(void){
    TEST_ASSERT_EQUAL_FLOAT(20.6,stationModule.getTemperatureCelsius());
}

void test_getMaxTemperatureCelsius_method(void){
    TEST_ASSERT_EQUAL_FLOAT(21,stationModule.getMaxTemperatureCelsius());
}

void test_getMinTemperatureCelsius_method(void){
    TEST_ASSERT_EQUAL_FLOAT(19.1,stationModule.getMinTemperatureCelsius());
}

void test_getDateMaxTemperature_method(void){
    TEST_ASSERT_EQUAL_UINT32(1668711493, stationModule.getDateMaxTemperature());
}

void test_getDateMinTemperature_method(void){
    TEST_ASSERT_EQUAL_UINT32(1668678374, stationModule.getDateMinTemperature());
}

void test_getHumidityPercentage_method(void){
    TEST_ASSERT_EQUAL_UINT8(64, stationModule.getHumidityPercentage());
}

void test_getCO2ppm_method(void){
    TEST_ASSERT_EQUAL_UINT16(664, stationModule.getCO2ppm());
}

void test_getNoiseLeveldB_method(void){
    TEST_ASSERT_EQUAL_UINT8(36, stationModule.getNoiseLeveldB());
}

void test_getLast12hrsPressureTrend_method(void){
    String trend = stationModule.getLast12hrsPressureTrend();
    char testTrend[trend.length()+1];
    trend.toCharArray(testTrend, trend.length()+1);
    TEST_ASSERT_EQUAL_STRING("up",testTrend);
}

void test_getSurfacePressurembar_method(void){
    TEST_ASSERT_EQUAL_FLOAT(1001.1, stationModule.getSurfacePressurembar());
}

void test_getSeaLevelPressurembar(void){
    TEST_ASSERT_EQUAL_FLOAT(991.5, stationModule.getSeaLevelPressurembar());
}
void test_generateStatusReport_method(void){
    String generalStatus = stationModule.generateStatusReport();
    char stationModuleStatus[generalStatus.length()+1];
    generalStatus.toCharArray(stationModuleStatus, generalStatus.length()+1);
    TEST_ASSERT_EQUAL_STRING(stationModuleRefGeneralStatus,stationModuleStatus);
}

void setup(void){
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();
    RUN_TEST(test_init_method);
    RUN_TEST(test_getMeasureTimestamp_method);
    RUN_TEST(test_getTemperatureCelsius_method);
    RUN_TEST(test_getMaxTemperatureCelsius_method);
    RUN_TEST(test_getMinTemperatureCelsius_method);
    RUN_TEST(test_getDateMaxTemperature_method);
    RUN_TEST(test_getDateMinTemperature_method);
    RUN_TEST(test_getHumidityPercentage_method);
    RUN_TEST(test_getCO2ppm_method);
    RUN_TEST(test_getNoiseLeveldB_method);
    RUN_TEST(test_getLast12hrsPressureTrend_method);
    RUN_TEST(test_getSurfacePressurembar_method);
    RUN_TEST(test_getSeaLevelPressurembar);
    RUN_TEST(test_generateStatusReport_method);
    UNITY_END();
}

void loop(void){
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(500);
}