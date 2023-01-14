#include <Arduino.h>
#include <unity.h>
#include "../modules_tests_datas.h"
#include "Modules/RainGauge.hpp"

RainGauge Rain_gauge;
//JsonObject rain_gauge_datas;

void setUp(){}
void tearDown(){}

void test_init_method(void){
    JsonObject nonDefinedJson;
    TEST_ASSERT(!Rain_gauge.init(nonDefinedJson));
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, module_data_reachable_string);
    JsonObject rain_gauge_datas = doc.as<JsonObject>();
    TEST_ASSERT(Rain_gauge.init(rain_gauge_datas));
}

void test_getMeasureTimestamp_method(void){
    TEST_ASSERT_EQUAL_UINT32(1668718779,Rain_gauge.getMeasureTimestamp());
}

void test_getRainMM_method(void){
    TEST_ASSERT_EQUAL_FLOAT(0.6,Rain_gauge.getRainMM());
}

void test_getLast1hrTotalRainMM(void){
    TEST_ASSERT_EQUAL_FLOAT(0,Rain_gauge.getLast1hrTotalRainMM());
}

void test_getLast24hrTotalRainMM(void){
    TEST_ASSERT_EQUAL_FLOAT(4.9, Rain_gauge.getLast24hrTotalRainMM());
}

void test_generateStatusReport_method(void){
    String generalStatus = Rain_gauge.generateStatusReport();
    char rainGaugeStatus[generalStatus.length()+1];
    generalStatus.toCharArray(rainGaugeStatus, generalStatus.length()+1);
    TEST_ASSERT_EQUAL_STRING(rainGaugeRefGeneralStatus,rainGaugeStatus);

}

void setup(void){
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();
    RUN_TEST(test_init_method);
    RUN_TEST(test_getMeasureTimestamp_method);
    RUN_TEST(test_getRainMM_method);
    RUN_TEST(test_getLast1hrTotalRainMM);
    RUN_TEST(test_getLast24hrTotalRainMM);
    RUN_TEST(test_generateStatusReport_method);
    UNITY_END();
}

void loop(void){
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(500);
}