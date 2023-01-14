#include <unity.h>
#include <Modules/WindModule.hpp>
#include "../modules_tests_datas.h"

WindModule windModule;
//JsonObject rain_gauge_datas;

void setUp(){}
void tearDown(){}

void test_init_method(void){
    JsonObject nonDefinedJson;
    TEST_ASSERT(!windModule.init(nonDefinedJson));

    DynamicJsonDocument doc(1024);
    deserializeJson(doc, module_data_reachable_string);
    JsonObject wind_module_datas = doc.as<JsonObject>();
    TEST_ASSERT(windModule.init(wind_module_datas));
}

void test_getWindStrength_method(void){
    TEST_ASSERT_EQUAL_UINT16(2, windModule.getWindStrengthKPH());
}

void test_getMeasureTimestamp_method(void){
    TEST_ASSERT_EQUAL_UINT32(1668718779, windModule.getMeasureTimestamp());
}

void test_getWindStrengthKPH_method(void){
    TEST_ASSERT_EQUAL_UINT16(2,windModule.getWindStrengthKPH());
}

void test_getWindAngleDegree_method(void){
    TEST_ASSERT_EQUAL_INT16(75, windModule.getWindAngleDegree());
}

void test_getGustStrengthKPH_method(void){
    TEST_ASSERT_EQUAL_UINT16(3, windModule.getGustStrengthKPH());
}

void test_getGustAngleDegree(void){
    TEST_ASSERT_EQUAL_INT16(75, windModule.getGustAngleDegree());
}

void test_getMaxWindStrengthKPH(void){
    TEST_ASSERT_EQUAL_UINT16(4, windModule.getMaxWindStrengthKPH());
}

void test_getMaxWindAngleDegree(void){
    TEST_ASSERT_EQUAL_INT16(100, windModule.getMaxWindAngleDegree());
}

void test_getDateMaxWindStrength(void){
    TEST_ASSERT_EQUAL_UINT32(1555673190, windModule.getDateMaxWindStrength());
}

void test_generateStatusReport_method(void){
    String generalStatus = windModule.generateStatusReport();
    char windModuleStatus[generalStatus.length()+1];
    generalStatus.toCharArray(windModuleStatus, generalStatus.length()+1);
    TEST_ASSERT_EQUAL_STRING(windModuleRefGeneralStatus,windModuleStatus);
}

void setup(void){
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();
    RUN_TEST(test_init_method);
    RUN_TEST(test_getMeasureTimestamp_method);
    RUN_TEST(test_getWindStrength_method);
    RUN_TEST(test_getWindAngleDegree_method);
    RUN_TEST(test_getGustStrengthKPH_method);
    RUN_TEST(test_getGustAngleDegree);
    RUN_TEST(test_getMaxWindStrengthKPH);
    RUN_TEST(test_getMaxWindAngleDegree);
    RUN_TEST(test_getDateMaxWindStrength);
    RUN_TEST(test_generateStatusReport_method);
    UNITY_END();
}

void loop(void){
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(500);
}

