# include "StationModule.hpp"

StationModule::StationModule(){
    IndoorModule();
}

StationModule::StationModule(JsonObject stationData){
    IndoorModule();

    init(stationData);
}

bool StationModule::init(JsonObject stationData){
    if(stationData.isNull()){
        return false ;
    }
    IndoorModule::init(stationData);

    noise_level_dB_ = stationData["dashboard_data"]["Noise"].as<uint8_t>();
    pressure_mbar_ =  stationData["dashboard_data"]["Pressure"].as<float>();
    absolute_pressure_mbar_ = stationData["dashboard_data"]["AbsolutePressure"].as<float>();
    pressure_trend_ = stationData["dashboard_data"]["pressure_trend"].as<String>();
    return true ;
}

bool StationModule::update(JsonObject stationData){
    if(stationData.isNull()){
        return false ;
    }

    noise_level_dB_ = stationData["dashboard_data"]["Noise"].as<uint8_t>();
    pressure_mbar_ =  stationData["dashboard_data"]["Pressure"].as<float>();
    absolute_pressure_mbar_ = stationData["dashboard_data"]["AbsolutePressure"].as<float>();
    pressure_trend_ = stationData["dashboard_data"]["pressure_trend"].as<String>();

    return IndoorModule::update(stationData); ;
}

uint8_t StationModule::getNoiseLeveldB()const{return(noise_level_dB_);}
String StationModule::getLast12hrsPressureTrend() const{return(pressure_trend_);}
float StationModule::getSurfacePressurembar()const{return(pressure_mbar_);}
float StationModule::getSeaLevelPressurembar()const{return(absolute_pressure_mbar_);}

String StationModule::generateStatusReport(){
    String generalStatus = IndoorModule::generateStatusReport();
    generalStatus += "\n Noise level in dB : " + (String) noise_level_dB_;
    generalStatus += "\n surface pressure in mbar : " + (String) pressure_mbar_;
    generalStatus += "\n sea level pressure in mbar: " + (String) absolute_pressure_mbar_;
    generalStatus += "\n pressure trend for the last 12hrs : " + pressure_trend_;
    return generalStatus ;
}

StationModule::~StationModule(){}