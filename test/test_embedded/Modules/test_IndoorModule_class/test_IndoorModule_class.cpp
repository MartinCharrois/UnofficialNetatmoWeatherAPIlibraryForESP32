#include <unity.h>
#include <Modules/IndoorModule.hpp>
#include "../modules_tests_datas.h"

IndoorModule indoorModule;

void setUp(void){}
void tearDown(void){}

void test_init_method(void){
    JsonObject nonDefinedJson;
    TEST_ASSERT(!indoorModule.init(nonDefinedJson));

    DynamicJsonDocument doc(1024);
    deserializeJson(doc, module_data_reachable_string);
    JsonObject indoor_module_datas = doc.as<JsonObject>();
    TEST_ASSERT(indoorModule.init(indoor_module_datas));
}

void test_getMeasureTimestamp_method(void){
    TEST_ASSERT_EQUAL_UINT32(1668718779, indoorModule.getMeasureTimestamp());
}

void test_getTemperatureCelsius_method(void){
    TEST_ASSERT_EQUAL_FLOAT(20.6,indoorModule.getTemperatureCelsius());
}

void test_getMaxTemperatureCelsius_method(void){
    TEST_ASSERT_EQUAL_FLOAT(21,indoorModule.getMaxTemperatureCelsius());
}

void test_getMinTemperatureCelsius_method(void){
    TEST_ASSERT_EQUAL_FLOAT(19.1,indoorModule.getMinTemperatureCelsius());
}

void test_getDateMaxTemperature_method(void){
    TEST_ASSERT_EQUAL_UINT32(1668711493, indoorModule.getDateMaxTemperature());
}

void test_getDateMinTemperature_method(void){
    TEST_ASSERT_EQUAL_UINT32(1668678374, indoorModule.getDateMinTemperature());
}

void test_getHumidityPercentage_method(void){
    TEST_ASSERT_EQUAL_UINT8(64, indoorModule.getHumidityPercentage());
}

void test_getCO2ppm_method(void){
    TEST_ASSERT_EQUAL_UINT16(664, indoorModule.getCO2ppm());
}

void test_generateStatusReport_method(void){
    String generalStatus = indoorModule.generateStatusReport();
    char indoorModuleStatus[generalStatus.length()+1];
    generalStatus.toCharArray(indoorModuleStatus, generalStatus.length()+1);
    TEST_ASSERT_EQUAL_STRING(indoorModuleRefGeneralStatus,indoorModuleStatus);
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
    RUN_TEST(test_generateStatusReport_method);
    UNITY_END();
}

void loop(void){
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(500);
}