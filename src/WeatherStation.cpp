#include "WeatherStation.hpp"

WeatherStation::WeatherStation(){
    token_ = NULL;
    stationModule_ = NULL;
    rainGauge_ = NULL;
    windModule_ = NULL;
}

WeatherStation::WeatherStation(Token* token){
    init(token);
}

bool WeatherStation::init(Token* token){
    token_ = token;
    String WeatherStationRequestAnswer = makeRequestGetStationsData();

    DynamicJsonDocument doc(8192);
    deserializeJson(doc, WeatherStationRequestAnswer);
    JsonObject WeatherStationData = doc["body"]["devices"][0];

    bool isSuccessfullyInitialized = init(WeatherStationData);
    return isSuccessfullyInitialized;
}

bool WeatherStation::init(JsonObject WeatherStationData){
    if(WeatherStationData.isNull()){
        return false ;
    }
    Wifi_status_ = WeatherStationData["wifi_status"].as<uint8_t>();
    calibrating_CO2_sensor_ = (WeatherStationData["co2_calibrating"].as<String>() == "true") ;
    timezone_ = WeatherStationData["place"]["timezone"].as<String>();
    country_ = WeatherStationData["place"]["country"].as<String>();
    city_ = WeatherStationData["place"]["city"].as<String>();
    street_ = WeatherStationData["place"]["street"].as<String>();
    altitude_ = WeatherStationData["place"]["altitude"].as<uint16_t>();
    latitude_ = WeatherStationData["place"]["location"][0].as<float>();
    longitude_ = WeatherStationData["place"]["location"][1].as<float>();
    home_name_ = WeatherStationData["home_name"].as<String>();

    stationModule_ = new StationModule(WeatherStationData);

    JsonArray moduleJsonArray = WeatherStationData["modules"].as<JsonArray>();

    const String outdoorModuleType = "NAModule1";
    const String windModuleType = "NAModule2";
    const String rainGaugeType = "NAModule3";
    const String indoorModuleType = "NAModule4";

    for(JsonObject moduleData : moduleJsonArray){
        if(moduleData.isNull()){
            return false ;
        }
        if(moduleData["type"].as<String>() == outdoorModuleType){
            outdoorModules_.push_back(new OutdoorModule(moduleData));
        }
        else if(moduleData["type"].as<String>() == windModuleType){
            windModule_ = new WindModule(moduleData);
        }
        else if(moduleData["type"].as<String>() == rainGaugeType){
            rainGauge_ = new RainGauge(moduleData);
        }
        else if(moduleData["type"].as<String>() == indoorModuleType){
            indoorModules_.push_back(new IndoorModule(moduleData));
        }
    }
    return true;
}

//TODO add time management for the following udate method in order to make less request (only when data are refreshed on Netatmo servers)
bool WeatherStation::update(){
    String stationMacAddress = stationModule_->getMacAddress();
    String WeatherStationRequestAnswer = makeRequestGetStationsData(false, stationMacAddress);

    DynamicJsonDocument doc(8192);
    deserializeJson(doc, WeatherStationRequestAnswer);
    JsonObject WeatherStationData = doc["body"]["devices"][0];

    bool isSuccessfullyUpdated = update(WeatherStationData);
    return isSuccessfullyUpdated;
}

bool WeatherStation::update(JsonObject WeatherStationData){
    if(WeatherStationData.isNull()){
        return false ;
    }
    Wifi_status_ = WeatherStationData["wifi_status"].as<uint8_t>();
    calibrating_CO2_sensor_ = (WeatherStationData["co2_calibrating"].as<String>() == "true") ;

    stationModule_->update(WeatherStationData);

    JsonArray moduleJsonArray = WeatherStationData["modules"];
    for(JsonObject moduleData : moduleJsonArray){
        if(moduleData.isNull()){
            return false ;
        }
        const String outdoorModuleType = "NAModule1";
        const String windModuleType = "NAModule2";
        const String rainGaugeType = "NAModule3";
        const String indoorModuleType = "NAModule4";
        if(moduleData["type"].as<String>() == outdoorModuleType){
            for (OutdoorModule *outdoorModule : outdoorModules_){
                if( outdoorModule->getMacAddress() == moduleData["_id"].as<String>()){
                    outdoorModule->update(moduleData);
                }
            }
        }
        else if(moduleData["type"].as<String>() == windModuleType){
            windModule_->update(moduleData);
        }
        else if(moduleData["type"].as<String>() == rainGaugeType){
            rainGauge_->update(moduleData);
        }
        else if(moduleData["type"].as<String>() == indoorModuleType){
            for (IndoorModule *indoorModule : indoorModules_){
                if( indoorModule->getMacAddress() == moduleData["_id"].as<String>()){
                    indoorModule->update(moduleData);
                }
            }
        }
    }
    return true;
}

String WeatherStation::makeRequestGetStationsData(bool getFavoriteStationData, String StationMacAddress){
    String get_favorite;
    if(getFavoriteStationData){
        get_favorite = "true";
    }
    else{
        get_favorite = "false";
    }

    HTTPClient http;
    String serverPath = "https://api.netatmo.com/api/getstationsdata?get_favorites=" + get_favorite + "&access_token=" + token_->checkAndFetchToken();
    if( StationMacAddress.length() == 17){
        serverPath += "&device=" + StationMacAddress;
    }
    http.begin(serverPath);
    http.GET();
    String requestAnswer= http.getString();
    http.end();  //Free resources
    return(requestAnswer);
}

StationModule* WeatherStation::getStationModulePointer(){return(stationModule_);}
IndoorModule* WeatherStation::getIndoorModulePointer(){return(indoorModules_.front());}
OutdoorModule* WeatherStation::getOutdoorModulePointer(){return(outdoorModules_.front());}
RainGauge* WeatherStation::getRainGaugePointer(){return(rainGauge_);}
WindModule* WeatherStation::getWindModulePointer(){return(windModule_);}

Token* WeatherStation::getTokenPointer(){return(token_);}
uint8_t WeatherStation::getWifiStatus(){return(Wifi_status_);}
bool WeatherStation::isCalibratingCO2Sensor(){return(calibrating_CO2_sensor_);}
String WeatherStation::getTimezone(){return(timezone_);}
String WeatherStation::getCountry(){return(country_);}
String WeatherStation::getCity(){return(city_);}
String WeatherStation::getStreet(){return(street_);}
uint16_t WeatherStation::getAltitude(){return(altitude_);}
float WeatherStation::getLatitude(){return(latitude_);}
float WeatherStation::getLongitude(){return(longitude_);}
String WeatherStation::getStationHomeName(){return(home_name_);}

String WeatherStation::generateStationStatusReport(){
    String stationStatus = "... Station Status report ...";
    stationStatus += "\nThis is the weather station " + home_name_;
    stationStatus += "\nIt's located in "+ city_;
    stationStatus += ", "+country_;
    stationStatus += "\nlongitude : " + String(longitude_,12);
    stationStatus += ", latitude : " + String(latitude_,12);
    stationStatus += "\n... Station Module status report ...\n";
    stationStatus += stationModule_->generateStatusReport();
    return(stationStatus);
}

String WeatherStation::generateFullStatusReport(){

    String fullStatus = "\n\n\n... Complete station and modules status report ...\n";
    fullStatus += generateStationStatusReport();
    fullStatus +="\n... station module status report ...\n";
    fullStatus += stationModule_->generateStatusReport();

    if(indoorModules_.empty()){
        fullStatus += "\n<<<<< No indoor modules connected to the station >>>>>\n";
    }
    else{
        fullStatus += "\n... indoor modules status report ...";
        for(IndoorModule* indoorModule : indoorModules_){
            fullStatus += "\n--- indoor module status report ---\n";
            fullStatus += indoorModule->generateStatusReport();
        }
    }

    if(outdoorModules_.empty()){
        fullStatus += "\n<<<<< No outdoor modules connected to the station >>>>>\n";
    }
    else{
        fullStatus += "\n... outdoor modules status report ...";
        for(OutdoorModule* outdoorModule : outdoorModules_){
            fullStatus += "\n--- outdoor module status report ---\n";
            fullStatus += outdoorModule->generateStatusReport();
        }
    }

    if(rainGauge_ == NULL){
        fullStatus += "\n<<<<< No rain gauge connected to the station >>>>>\n";
    }
    else{
        fullStatus += "\n... rain gauge status report ...\n";
        fullStatus += rainGauge_->generateStatusReport();
    }

    if(windModule_ == NULL){
        fullStatus += "\n<<<<< No wind module connected to the station >>>>>\n";
    }
    else{
        fullStatus += "\n... wind module status report ...\n";
        fullStatus += windModule_->generateStatusReport();
    }

    fullStatus +="... End of report ...\n\n" ;
    return(fullStatus);
}

WeatherStation::~WeatherStation()
{
    delete stationModule_;

    delete rainGauge_;

    delete windModule_;

    while(!indoorModules_.empty()){
        delete indoorModules_.back();
        indoorModules_.pop_back();
    }
    while(!outdoorModules_.empty()){
        delete outdoorModules_.back();
        outdoorModules_.pop_back();
    }
}
