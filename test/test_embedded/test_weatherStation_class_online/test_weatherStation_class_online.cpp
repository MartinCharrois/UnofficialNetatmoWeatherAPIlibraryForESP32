#include <Arduino.h>
#include <unity.h>
#include "WeatherStation.hpp"
#include "../LoginCredentialsForTests.hpp"

WeatherStation testStation;
Token testToken;

void setUp(void){testToken.init(client_id, client_secret, netatmoUsername, netatmoPassword);}
void tearDown(void){}

void test_init_method(void){
    TEST_ASSERT_TRUE(testStation.init(&testToken));
}

void test_update_method(void){
    TEST_ASSERT_TRUE(testStation.update());
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
    RUN_TEST(test_update_method);
    UNITY_END();
}

void loop(void){
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(500);
}