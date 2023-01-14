#include "OutdoorModule.hpp"

OutdoorModule::OutdoorModule(){Module();}

OutdoorModule::OutdoorModule(JsonObject outdoorModuleData){
    Module();
    init(outdoorModuleData);
}

bool OutdoorModule::init(JsonObject outdoorModuleData){
    if(outdoorModuleData.isNull()){
        return false ;
    }

    Module::init(outdoorModuleData);

    measure_timestamp_local_epoch_ = outdoorModuleData["dashboard_data"]["time_utc"].as<uint32_t>();
    temperature_Celsius_ = outdoorModuleData["dashboard_data"]["Temperature"].as<float>();
    humidity_percentage_ = outdoorModuleData["dashboard_data"]["Humidity"].as<uint8_t>();
    min_temperature_Celsius_ = outdoorModuleData["dashboard_data"]["min_temp"].as<float>();
    date_min_temperature_local_epoch_ = outdoorModuleData["dashboard_data"]["date_min_temp"].as<uint32_t>();
    max_temperature_Celsius_ = outdoorModuleData["dashboard_data"]["max_temp"].as<float>();
    date_max_temperature_local_epoch_ = outdoorModuleData["dashboard_data"]["date_max_temp"].as<uint32_t>();

    return true ;
}

bool OutdoorModule::update(JsonObject outdoorModuleData){
    if(outdoorModuleData.isNull()){
        return false ;
    }

    measure_timestamp_local_epoch_ = outdoorModuleData["dashboard_data"]["time_utc"].as<uint32_t>();
    temperature_Celsius_ = outdoorModuleData["dashboard_data"]["Temperature"].as<float>();
    humidity_percentage_ = outdoorModuleData["dashboard_data"]["Humidity"].as<uint8_t>();
    min_temperature_Celsius_ = outdoorModuleData["dashboard_data"]["min_temp"].as<float>();
    date_min_temperature_local_epoch_ = outdoorModuleData["dashboard_data"]["date_min_temp"].as<uint32_t>();
    max_temperature_Celsius_ = outdoorModuleData["dashboard_data"]["max_temp"].as<float>();
    date_max_temperature_local_epoch_ = outdoorModuleData["dashboard_data"]["date_max_temp"].as<uint32_t>();

    return Module::update(outdoorModuleData); ;
}

uint32_t OutdoorModule::getMeasureTimestamp() const {return(measure_timestamp_local_epoch_);}
float OutdoorModule::getTemperatureCelsius() const {return(temperature_Celsius_);}
float OutdoorModule::getMaxTemperatureCelsius() const {return(max_temperature_Celsius_);}
float OutdoorModule::getMinTemperatureCelsius() const {return(min_temperature_Celsius_);}
uint32_t OutdoorModule::getDateMaxTemperature() const {return(date_max_temperature_local_epoch_);}
uint32_t OutdoorModule::getDateMinTemperature() const {return(date_min_temperature_local_epoch_);}
uint8_t OutdoorModule::getHumidityPercentage() const {return(humidity_percentage_);}

String OutdoorModule::generateStatusReport() {
    String generalStatus = Module::generateStatusReport();
    generalStatus += "\n Timestamp of latest Data availlable (local epoch Time) : " + (String) measure_timestamp_local_epoch_;
    generalStatus += "\n Outdoor Humidity percentage : " + (String) humidity_percentage_;
    generalStatus += "\n Outdoor temperature (Celsius) : " + (String) temperature_Celsius_;
    generalStatus += "\n Outdoor minimal temperature (Celsius) : " + (String) min_temperature_Celsius_;
    generalStatus += "\n Timestamp of the minimal temperature (local epoch time): " + (String) date_min_temperature_local_epoch_;
    generalStatus += "\n Outdoor maximal temperature (Celsius) : " + (String) max_temperature_Celsius_;
    generalStatus += "\n Timestamp of the maximal temperature (local epoch time) : " + (String) date_max_temperature_local_epoch_;
    return generalStatus ;
}

OutdoorModule::~OutdoorModule(){}