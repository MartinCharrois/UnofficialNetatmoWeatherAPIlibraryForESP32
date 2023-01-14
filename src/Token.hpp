#pragma once

#ifndef Arduino
    #define Arduino
    #include "Arduino.h"
#endif
#ifndef EXTERNAL_LIBRARIES
    #include <HTTPClient.h>
    #include "time.h"
    #ifndef ARDUINO_JSON
        #include "ArduinoJson.h"
        #define ARDUINO_JSON
    #endif
    #define EXTERNAL_LIBRARIES
#endif

typedef enum{
    REQUEST_SUCCESS = 0x00,
    INVALID_USERNAME_OR_PASSWORD,
    INVALID_CLIENT_ID_OR_SECRET,
    UNKNOWN_ERROR,
} TOKEN_REQUEST_STATUS_t;

class Token
{
private:
    //time management
    const char* ntpServer_ = "pool.ntp.org";
    const long  gmtOffset_sec_ = 0;
    const int   daylightOffset_sec_ = 0;

    time_t epochTime_;

    //User and client app credentials
    String client_id_;
    String client_secret_;
    String userMail_; //mail used for oauth2
    String OAUTHpassword_;

    //token specific values
    bool initializedToken_;
    String token_;
    uint16_t tokenExpirationDate_;
    String refreshToken_; //token used to refresh the user token once it expired

public:

    Token();
    TOKEN_REQUEST_STATUS_t init(String client_id, String client_secret, String userMail, String password);
    bool isExpired();
    TOKEN_REQUEST_STATUS_t UpdateToken();
    String checkAndFetchToken();
    ~Token();
};

