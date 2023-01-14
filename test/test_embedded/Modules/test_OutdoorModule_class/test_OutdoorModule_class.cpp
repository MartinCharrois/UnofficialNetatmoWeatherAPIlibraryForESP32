#include <unity.h>
#include <Modules/OutdoorModule.hpp>
#include "../modules_tests_datas.h"

OutdoorModule outdoorModule;

void setUp(void){}
void tearDown(void){}

void test_init_method(void){
    JsonObject nonDefinedJson;
    TEST_ASSERT(!outdoorModule.init(nonDefinedJson));

    DynamicJsonDocument doc(1024);
    deserializeJson(doc, module_data_reachable_string);
    JsonObject Outdoor_module_datas = doc.as<JsonObject>();
    TEST_ASSERT(outdoorModule.init(Outdoor_module_datas));
}

void test_getMeasureTimestamp_method(void){
    TEST_ASSERT_EQUAL_UINT32(1668718779, outdoorModule.getMeasureTimestamp());
}

void test_getTemperatureCelsius_method(void){
    TEST_ASSERT_EQUAL_FLOAT(20.6,outdoorModule.getTemperatureCelsius());
}

void test_getMaxTemperatureCelsius_method(void){
    TEST_ASSERT_EQUAL_FLOAT(21,outdoorModule.getMaxTemperatureCelsius());
}

void test_getMinTemperatureCelsius_method(void){
    TEST_ASSERT_EQUAL_FLOAT(19.1,outdoorModule.getMinTemperatureCelsius());
}

void test_getDateMaxTemperature_method(void){
    TEST_ASSERT_EQUAL_UINT32(1668711493, outdoorModule.getDateMaxTemperature());
}

void test_getDateMinTemperature_method(void){
    TEST_ASSERT_EQUAL_UINT32(1668678374, outdoorModule.getDateMinTemperature());
}

void test_getHumidityPercentage_method(void){
    TEST_ASSERT_EQUAL_UINT8(64, outdoorModule.getHumidityPercentage());
}

void test_generateStatusReport_method(void){
    String generalStatus = outdoorModule.generateStatusReport();
    char outdoorModuleStatus[generalStatus.length()+1];
    generalStatus.toCharArray(outdoorModuleStatus, generalStatus.length()+1);
    TEST_ASSERT_EQUAL_STRING(outdoorModuleRefGeneralStatus,outdoorModuleStatus);
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
    RUN_TEST(test_generateStatusReport_method);
    UNITY_END();
}

void loop(void){
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(500);
}