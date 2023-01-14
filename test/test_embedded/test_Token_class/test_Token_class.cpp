#include <Arduino.h>
#include <unity.h>
#include "Token.hpp"
#include "../LoginCredentialsForTests.hpp"

Token testToken;

void setUp(void){}
void tearDown(void){}

void test_init_method(void){
    //first with false credentials
    TEST_ASSERT_TRUE(testToken.init(falseClient_id, client_secret, netatmoUsername, netatmoPassword) == INVALID_CLIENT_ID_OR_SECRET);
    TEST_ASSERT_TRUE(testToken.init(client_id, falseClient_secret, netatmoUsername, netatmoPassword) == INVALID_CLIENT_ID_OR_SECRET);
    TEST_ASSERT_TRUE(testToken.init(client_id, client_secret, falseNetatmoUsername, netatmoPassword) == INVALID_USERNAME_OR_PASSWORD);
    TEST_ASSERT_TRUE(testToken.init(client_id, client_secret, netatmoUsername, falseNetatmoPassword) == INVALID_USERNAME_OR_PASSWORD);
    //finally with good credentials
    TEST_ASSERT_TRUE(testToken.init(client_id, client_secret, netatmoUsername, netatmoPassword) == REQUEST_SUCCESS);
}

void test_isExpired_method(void){
    TEST_ASSERT_FALSE(testToken.isExpired());
}

void test_updateToken_method(void){
    TEST_ASSERT_TRUE(testToken.UpdateToken() == REQUEST_SUCCESS);
}

void test_checkAndFetchToken_method(void){
    //test of length (can't test equality as we don't know it)
    TEST_ASSERT_EQUAL_INT(57,testToken.checkAndFetchToken().length());
}

void setup(void){
    delay(4000);   //Delay needed before calling the WiFi.begin
    WiFi.mode(WIFI_STA);
    WiFi.begin(WifiNetworkName, Wifipassword);
    int notConnectedCounter = 0;
    do{ //Check for the connection
        delay(1000);
        TEST_MESSAGE("Connecting to WiFi..");
        notConnectedCounter++;
        if(notConnectedCounter > 15) { // Reset board if not connected after 15s
            TEST_MESSAGE("Resetting due to Wifi not connecting...");
            ESP.restart();
        }
    }while (WiFi.status() != WL_CONNECTED);//Check for WiFi connection

    TEST_MESSAGE("Connected to the WiFi network");
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();
    RUN_TEST(test_init_method);
    RUN_TEST(test_isExpired_method);
    RUN_TEST(test_updateToken_method);
    RUN_TEST(test_checkAndFetchToken_method);
    UNITY_END();
}

void loop(void){
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(500);
}