
#include <ESP32libForNetatmoWeatherAPI.hpp>

Token token;
WeatherStation station;
IndoorModule* indoorModule; //a pointer to our first indoor module

//Credentials of your wifi network
const char* WiFiNetwork = "WifiName";
const char* WiFipassword =  "WifiPassword";

//for more info about registering your app, see the README, section "Create an app on Netatmo services" on https://github.com/MartinCharrois/UnofficialNetatmoWeatherAPIlibraryForESP32
const String client_id = ""; //replace with the ID of the app you registered on Netatmo dev website https://dev.netatmo.com/
const String client_secret = "" ; //replace with the secret password of the app you registered on Netatmo dev website https://dev.netatmo.com/
const String username =""; //your Netatmo Username
const String OAUTHpassword = ""; //your Netatmo password

void setup() {
    Serial.begin(115200);

    //connecting to WiFi
    delay(4000);   //Delay needed before calling the WiFi.begin
    WiFi.mode(WIFI_STA);
    WiFi.begin(WiFiNetwork, WiFipassword);
    int notConnectedCounter = 0;
    do{
        delay(1000);
        Serial.print("WiFi connection Status : ");
        Serial.print(WiFi.status());
        Serial.println(" | Connecting to WiFi..");
        notConnectedCounter++;
        if(notConnectedCounter > 15) { // Reset board if not connected after 15s
            Serial.println("Resetting due to Wifi not connecting...");
            ESP.restart();
        }
    }while (WiFi.status() != WL_CONNECTED);//Check for WiFi connection

    Serial.println("Connected to the WiFi network");
    delay(3000);

    TOKEN_REQUEST_STATUS_t status = token.init(client_id, client_secret, username, OAUTHpassword);
    if(status == REQUEST_SUCCESS){
        Serial.println("token successfully fetched");
        station.init(&token);
        indoorModule = station.getIndoorModulePointer();
    }
    else{
        Serial.println("Error while requesting token");
        Serial.println("Please verify your credentials and try again");
    }
}

void loop() {
    station.update();
    float temperatureCelsius = indoorModule->getTemperatureCelsius();
    uint32_t timestamp = indoorModule->getMeasureTimestamp();
    Serial.println("at "+ String(timestamp) + ", the temperature was "+ String(temperatureCelsius) + "°C");
    delay(10000);
}
