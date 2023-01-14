#include "Token.hpp"

Token::Token(): initializedToken_(false) {}

TOKEN_REQUEST_STATUS_t Token::init(String client_id, String client_secret, String userMail, String password){
    /* Make a POST http request to netatmo servers to get the specified user's token*/
    client_id_ = client_id;
    client_secret_ = client_secret;
    userMail_ = userMail;
    OAUTHpassword_ = password;

    time(&epochTime_);

    HTTPClient RequestToken;

    RequestToken.begin("https://api.netatmo.com/oauth2/token");
    RequestToken.addHeader("Content-Type", "application/x-www-form-urlencoded;charset=UTF-8");
    String httpRequestData = "grant_type=password&client_id=" + client_id;
    httpRequestData += "&client_secret=" + client_secret;
    httpRequestData += "&username=" + userMail;
    httpRequestData += "&password=" + password;

    int httpResponseCode = RequestToken.POST(httpRequestData);
    String response = RequestToken.getString();
    RequestToken.end();

    DynamicJsonDocument doc(384);
    DeserializationError deserializationStatus = deserializeJson(doc, response);

    if (httpResponseCode == 200){
        token_ = doc["access_token"].as<String>();
        refreshToken_ = doc["refresh_token"].as<String>();
        tokenExpirationDate_ = epochTime_ + doc["expires_in"].as<uint16_t>();

        initializedToken_ = true;
        return(REQUEST_SUCCESS);
    }
    else if(httpResponseCode == 400){ //TODO add errors due to empty parameters

        String error = doc["error"].as<String>();

        if(error == "invalid_grant"){
            return( INVALID_USERNAME_OR_PASSWORD);
        }
        else if(error == "invalid_client"){
            return(INVALID_CLIENT_ID_OR_SECRET);
        }
        else {
            return(UNKNOWN_ERROR);
        }
    }
    else {
            return(UNKNOWN_ERROR);
        }
}

bool Token::isExpired(){
    time(&epochTime_);
    return ( tokenExpirationDate_ < epochTime_);
}

TOKEN_REQUEST_STATUS_t Token::UpdateToken(){
    /* Make a POST http request to netatmo servers to update the token*/
    time(&epochTime_);

    HTTPClient tokenUpdateRequest;
    tokenUpdateRequest.begin("https://api.netatmo.com/oauth2/token");
    tokenUpdateRequest.addHeader("Content-Type", "application/x-www-form-urlencoded;charset=UTF-8");

    String tokenUpdateRequestData = "grant_type=refresh_token&refresh_token=" + refreshToken_;
    tokenUpdateRequestData += "&client_id=" + client_id_;
    tokenUpdateRequestData += "&client_secret=" + client_secret_;

    int httpResponseCode = tokenUpdateRequest.POST(tokenUpdateRequestData);
    String response = tokenUpdateRequest.getString();
    tokenUpdateRequest.end();  //Free resources

    DynamicJsonDocument doc(384);
    DeserializationError deserializationStatus = deserializeJson(doc, response);
    if (httpResponseCode == 200){
        token_ = doc["access_token"].as<String>();
        refreshToken_ = doc["refresh_token"].as<String>();
        tokenExpirationDate_ = epochTime_ + doc["expires_in"].as<double>();

        return(REQUEST_SUCCESS);
    }
    else if(httpResponseCode == 400){

        String error = doc["error"].as<String>();//TODO add errors handling
        return(UNKNOWN_ERROR);
    }
    else {
            return(UNKNOWN_ERROR);
        }

}

String Token::checkAndFetchToken(){
    if(isExpired()){
        UpdateToken();
    }
    return(token_);
}

Token::~Token(){}