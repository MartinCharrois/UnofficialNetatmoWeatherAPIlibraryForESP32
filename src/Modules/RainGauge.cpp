#include "RainGauge.hpp"

RainGauge::RainGauge(){Module();}

RainGauge::RainGauge(JsonObject rainGaugeData){
    Module();

    init(rainGaugeData);
}

bool RainGauge::init(JsonObject rainGaugeData){
    if(rainGaugeData.isNull()){
        return false ;
    }

    Module::init(rainGaugeData);

    measure_timestamp_local_epoch_ = rainGaugeData["dashboard_data"]["time_utc"].as<uint32_t>();
    rain_mm_  = rainGaugeData["dashboard_data"]["Rain"].as<float>();
    last_1hr_total_rain_mm_ = rainGaugeData["dashboard_data"]["sum_rain_1"].as<float>();
    last_24hr_total_rain_mm_ = rainGaugeData["dashboard_data"]["sum_rain_24"].as<float>();
    return true ;
}

bool RainGauge::update(JsonObject rainGaugeData){
    if(rainGaugeData.isNull()){
        return false ;
    }

    measure_timestamp_local_epoch_ = rainGaugeData["dashboard_data"]["time_utc"].as<uint32_t>();
    rain_mm_  = rainGaugeData["dashboard_data"]["Rain"].as<float>();
    last_1hr_total_rain_mm_ = rainGaugeData["dashboard_data"]["sum_rain_1"].as<float>();
    last_24hr_total_rain_mm_ = rainGaugeData["dashboard_data"]["sum_rain_24"].as<float>();

    return Module::update(rainGaugeData); ;
}

uint32_t RainGauge::getMeasureTimestamp() const {return(measure_timestamp_local_epoch_); }
float RainGauge::getRainMM() const {return(rain_mm_); }
float RainGauge::getLast24hrTotalRainMM() const {return(last_24hr_total_rain_mm_); }
float RainGauge::getLast1hrTotalRainMM() const {return(last_1hr_total_rain_mm_); }

String RainGauge::generateStatusReport() {
    String rainGaugeGeneralStatus = Module::generateStatusReport();
    rainGaugeGeneralStatus += "\n Timestamp of latest Data availlable (local epoch Time) : " + (String) measure_timestamp_local_epoch_;
    rainGaugeGeneralStatus += "\n Rain level in millimeters : " + (String) rain_mm_;
    rainGaugeGeneralStatus += "\n Cumulated rain in the last hour before the timestamp (mm) : " + (String) last_1hr_total_rain_mm_;
    rainGaugeGeneralStatus += "\n Cumulated rain in the last 24 hour before the timestamp (mm) : " + (String) last_24hr_total_rain_mm_;
    return(rainGaugeGeneralStatus);
}

RainGauge::~RainGauge(){}