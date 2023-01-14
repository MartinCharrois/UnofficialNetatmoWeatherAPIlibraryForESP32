#include <Arduino.h>
#include <unity.h>
#include "../modules_tests_datas.h"
#include "Modules/Module.hpp"

Module module;

void setUp(){}
void tearDown(){}

void test_init_method(void){
    JsonObject nonDefinedJson;
    TEST_ASSERT(!module.init(nonDefinedJson));

    DynamicJsonDocument doc(1024);
    deserializeJson(doc, module_data_reachable_string);
    JsonObject module_data_reachable = doc.as<JsonObject>();

    TEST_ASSERT(module.init(module_data_reachable));
}

void test_getMacAddress_method(void){
    String macAddress = module.getMacAddress();
    char actual[macAddress.length()+1];
    macAddress.toCharArray(actual, macAddress.length()+1);
    TEST_ASSERT_EQUAL_STRING("05:00:00:01:97:b8",actual);
}

void test_getModuleName_method(void){
    String name = module.getModuleName();
    char actual[name.length()];
    name.toCharArray(actual, name.length()+1);
    TEST_ASSERT_EQUAL_STRING("Pluviom\u00e8tre",actual);
}

void test_getLastSetupLocalEpochTime_method(void){
    ulong lastMessage = module.getLastSetupLocalEpochTime();
    TEST_ASSERT_EQUAL_UINT32(1440229449,lastMessage);
}

void test_wasConnectedWithinLast4hr_method(void){
    TEST_ASSERT(module.wasConnectedWithinLast4hr());

    String unreachableJson = "{\"reachable\":false}";
    DynamicJsonDocument doc(48);
    deserializeJson(doc, unreachableJson);
    JsonObject unreachableJsonObject = doc.as<JsonObject>();
    Module unreachableModule(unreachableJsonObject);
    TEST_ASSERT(!unreachableModule.wasConnectedWithinLast4hr());
}

void test_getFirmwareVersion_method(void){
    TEST_ASSERT_EQUAL_UINT8(12, module.getFirmwareVersion());
}

void test_getLastMessageLocalEpochTime_method(void){
    TEST_ASSERT_EQUAL_UINT32(1668718798, module.getLastMessageLocalEpochTime());
}

void test_getLastStatusUpdateLocalEpochTime(void){
    TEST_ASSERT_EQUAL_UINT32(1668718792, module.getLastStatusUpdateLocalEpochTime());
}

void test_getSignalStrength_method(void){
    TEST_ASSERT_EQUAL_UINT8(56, module.getSignalStrength());
}
void test_getBatteryStatus_method(void){
    TEST_ASSERT_EQUAL_UINT16(6004, module.getBatteryStatus());
}

void test_getBAtteryPercentage_method(void){
    TEST_ASSERT_EQUAL_UINT8(100, module.getBatteryPercentage());
}

void test_generateStatusReport_method(){
    String generalStatus = module.generateStatusReport();
    char normalStatus[generalStatus.length()];
    generalStatus.toCharArray(normalStatus, generalStatus.length()+1);
    TEST_ASSERT_EQUAL_STRING(refGeneralStatus,normalStatus);

    String unreachableJson = "{\"reachable\":false}";
    DynamicJsonDocument doc(48);
    deserializeJson(doc, unreachableJson);
    JsonObject unreachableJsonObject = doc.as<JsonObject>();
    Module unreachableModule(unreachableJsonObject);

    String unreachableGeneralStatus = unreachableModule.generateStatusReport();
    char unreachableStatus[unreachableGeneralStatus.length()+1];
    unreachableGeneralStatus.toCharArray(unreachableStatus, unreachableGeneralStatus.length()+1);
    TEST_ASSERT_EQUAL_STRING(refUnreachableGeneralStatus,unreachableStatus);
}

void setup() {
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();
    RUN_TEST(test_init_method);
    RUN_TEST(test_getMacAddress_method);
    RUN_TEST(test_getModuleName_method);
    RUN_TEST(test_getLastSetupLocalEpochTime_method);
    RUN_TEST(test_wasConnectedWithinLast4hr_method);
    RUN_TEST(test_getFirmwareVersion_method);
    RUN_TEST(test_getLastMessageLocalEpochTime_method);
    RUN_TEST(test_getLastStatusUpdateLocalEpochTime);
    RUN_TEST(test_getSignalStrength_method);
    RUN_TEST(test_getBatteryStatus_method);
    RUN_TEST(test_getBAtteryPercentage_method);
    RUN_TEST(test_generateStatusReport_method);
    UNITY_END();
}

void loop() {
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(500);
}