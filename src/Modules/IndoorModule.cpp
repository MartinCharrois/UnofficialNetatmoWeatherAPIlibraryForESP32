#include "IndoorModule.hpp"

IndoorModule::IndoorModule(){Module();}

IndoorModule::IndoorModule(JsonObject indoorModuleData){
    Module();
    init(indoorModuleData);
}

bool IndoorModule::init(JsonObject indoorModuleData){
    if(indoorModuleData.isNull()){
        return false ;
    }

    Module::init(indoorModuleData);

    measure_timestamp_local_epoch_ = indoorModuleData["dashboard_data"]["time_utc"].as<uint32_t>();
    temperature_Celsius_ = indoorModuleData["dashboard_data"]["Temperature"].as<float>();
    CO2_ppm_ = indoorModuleData["dashboard_data"]["CO2"].as<uint16_t>();
    humidity_percentage_ = indoorModuleData["dashboard_data"]["Humidity"].as<uint8_t>();
    min_temperature_Celsius_ = indoorModuleData["dashboard_data"]["min_temp"].as<float>();
    date_min_temperature_local_epoch_ = indoorModuleData["dashboard_data"]["date_min_temp"].as<uint32_t>();
    max_temperature_Celsius_ = indoorModuleData["dashboard_data"]["max_temp"].as<float>();
    date_max_temperature_local_epoch_ = indoorModuleData["dashboard_data"]["date_max_temp"].as<uint32_t>();

    return true ;
}

bool IndoorModule::update(JsonObject indoorModuleData){
    if(indoorModuleData.isNull()){
        return false ;
    }

    measure_timestamp_local_epoch_ = indoorModuleData["dashboard_data"]["time_utc"].as<uint32_t>();
    temperature_Celsius_ = indoorModuleData["dashboard_data"]["Temperature"].as<float>();
    CO2_ppm_ = indoorModuleData["dashboard_data"]["CO2"].as<uint16_t>();
    humidity_percentage_ = indoorModuleData["dashboard_data"]["Humidity"].as<uint8_t>();
    min_temperature_Celsius_ = indoorModuleData["dashboard_data"]["min_temp"].as<float>();
    date_min_temperature_local_epoch_ = indoorModuleData["dashboard_data"]["date_min_temp"].as<uint32_t>();
    max_temperature_Celsius_ = indoorModuleData["dashboard_data"]["max_temp"].as<float>();
    date_max_temperature_local_epoch_ = indoorModuleData["dashboard_data"]["date_max_temp"].as<uint32_t>();

    return Module::update(indoorModuleData); ;
}

uint32_t IndoorModule::getMeasureTimestamp() const {return(measure_timestamp_local_epoch_);}
float IndoorModule::getTemperatureCelsius() const {return(temperature_Celsius_);}
float IndoorModule::getMaxTemperatureCelsius() const {return(max_temperature_Celsius_);}
float IndoorModule::getMinTemperatureCelsius() const {return(min_temperature_Celsius_);}
uint32_t IndoorModule::getDateMaxTemperature() const {return(date_max_temperature_local_epoch_);}
uint32_t IndoorModule::getDateMinTemperature() const {return(date_min_temperature_local_epoch_);}
uint8_t IndoorModule::getHumidityPercentage() const {return(humidity_percentage_);}
uint16_t IndoorModule::getCO2ppm() const {return(CO2_ppm_);}

String IndoorModule::generateStatusReport(){
    String generalStatus = Module::generateStatusReport();
    generalStatus += "\n Timestamp of latest Data availlable (local epoch Time) : " + (String) measure_timestamp_local_epoch_;
    generalStatus += "\n Indoor CO2 concentration in the air (ppm) : " + (String) CO2_ppm_;
    generalStatus += "\n Indoor Humidity percentage : " + (String) humidity_percentage_;
    generalStatus += "\n Indoor temperature (Celsius) : " + (String) temperature_Celsius_;
    generalStatus += "\n Indoor minimal temperature (Celsius) : " + (String) min_temperature_Celsius_;
    generalStatus += "\n Timestamp of the minimal temperature (local epoch time): " + (String) date_min_temperature_local_epoch_;
    generalStatus += "\n Indoor maximal temperature (Celsius) : " + (String) max_temperature_Celsius_;
    generalStatus += "\n Timestamp of the maximal temperature (local epoch time) : " + (String) date_max_temperature_local_epoch_;
    return generalStatus ;
}

IndoorModule::~IndoorModule(){}