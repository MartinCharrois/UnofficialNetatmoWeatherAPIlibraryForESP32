# include "WindModule.hpp"

WindModule::WindModule(){Module();}

WindModule::WindModule(JsonObject windModuleData){
    Module();

    init(windModuleData);
}

bool WindModule::init(JsonObject windModuleData){
    if(windModuleData.isNull()){
        return false ;
    }

    Module::init(windModuleData);

    measure_timestamp_local_epoch_ = windModuleData["dashboard_data"]["time_utc"].as<uint32_t>();
    wind_strength_kph_ = windModuleData["dashboard_data"]["WindStrength"].as<uint16_t>();
    wind_angle_degree_ = windModuleData["dashboard_data"]["WindAngle"].as<int16_t>();
    gust_strength_kph_ = windModuleData["dashboard_data"]["GustStrength"].as<uint16_t>();
    gust_angle_degree_ = windModuleData["dashboard_data"]["GustAngle"].as<int16_t>();
    max_wind_strength_kph_ = windModuleData["dashboard_data"]["max_wind_str"].as<uint16_t>();
    max_wind_angle_degree_ = windModuleData["dashboard_data"]["max_wind_angle"].as<int16_t>();
    date_max_wind_strength_local_epoch_ = windModuleData["dashboard_data"]["date_max_wind_str"].as<uint32_t>();
    return true ;
}

bool WindModule::update(JsonObject windModuleData){
    if(windModuleData.isNull()){
        return false ;
    }

    measure_timestamp_local_epoch_ = windModuleData["dashboard_data"]["time_utc"].as<uint32_t>();
    wind_strength_kph_ = windModuleData["dashboard_data"]["WindStrength"].as<uint16_t>();
    wind_angle_degree_ = windModuleData["dashboard_data"]["WindAngle"].as<int16_t>();
    gust_strength_kph_ = windModuleData["dashboard_data"]["GustStrength"].as<uint16_t>();
    gust_angle_degree_ = windModuleData["dashboard_data"]["GustAngle"].as<int16_t>();
    max_wind_strength_kph_ = windModuleData["dashboard_data"]["max_wind_str"].as<uint16_t>();
    max_wind_angle_degree_ = windModuleData["dashboard_data"]["max_wind_angle"].as<int16_t>();
    date_max_wind_strength_local_epoch_ = windModuleData["dashboard_data"]["date_max_wind_str"].as<uint32_t>();

    return Module::update(windModuleData); ;
}

uint32_t WindModule::getMeasureTimestamp() const {return(measure_timestamp_local_epoch_);}
uint16_t WindModule::getWindStrengthKPH() const {return(wind_strength_kph_);}
int16_t WindModule::getWindAngleDegree() const {return(wind_angle_degree_);}
uint16_t WindModule::getGustStrengthKPH() const {return(gust_strength_kph_);}
int16_t WindModule::getGustAngleDegree() const {return(gust_angle_degree_);}
uint16_t WindModule::getMaxWindStrengthKPH() const {return(max_wind_strength_kph_);}
int16_t WindModule::getMaxWindAngleDegree() const {return(max_wind_angle_degree_);}
uint32_t WindModule::getDateMaxWindStrength() const {return(date_max_wind_strength_local_epoch_);}

String WindModule::generateStatusReport() {
    String windModuleGeneralStatus = Module::generateStatusReport();
    windModuleGeneralStatus += "\n Timestamp of latest Data availlable (local epoch Time) : " + (String) measure_timestamp_local_epoch_;
    windModuleGeneralStatus += "\n Wind strength in KpH : " + (String) wind_strength_kph_;
    windModuleGeneralStatus += "\n Wind angle in degrees : " + (String) wind_angle_degree_;
    windModuleGeneralStatus += "\n Date of the maximal wind strength (local epoch Time) : " + (String) date_max_wind_strength_local_epoch_;
    windModuleGeneralStatus += "\n Maximal wind strength measured in Kph : " + (String) max_wind_strength_kph_;
    windModuleGeneralStatus += "\n Maximal wind angle measured in Degrees : " + (String) max_wind_angle_degree_;
    windModuleGeneralStatus += "\n Gust strength in KpH : " + (String) gust_strength_kph_;
    windModuleGeneralStatus += "\n Gust Angle in KpH : " + (String) gust_angle_degree_;
    return windModuleGeneralStatus ;
}

WindModule::~WindModule(){}
