#pragma once

#ifndef MODULE
    #include "Module.hpp"
    #define MODULE
#endif

class OutdoorModule: public Module
{
public:
    OutdoorModule();
    OutdoorModule(JsonObject outdoorModuleData);
    bool init(JsonObject outdoorModuleData);
    bool update(JsonObject outdoorModuleData);

    uint32_t getMeasureTimestamp() const;
    float getTemperatureCelsius() const;
    float getMaxTemperatureCelsius() const;
    float getMinTemperatureCelsius() const;
    uint32_t getDateMaxTemperature() const;
    uint32_t getDateMinTemperature() const;
    uint8_t getHumidityPercentage() const;

    String generateStatusReport();
    ~OutdoorModule();
private:
    uint32_t measure_timestamp_local_epoch_;
    float temperature_Celsius_;
    uint8_t humidity_percentage_;
    float min_temperature_Celsius_;
    uint32_t date_min_temperature_local_epoch_;
    float max_temperature_Celsius_;
    uint32_t date_max_temperature_local_epoch_;
};