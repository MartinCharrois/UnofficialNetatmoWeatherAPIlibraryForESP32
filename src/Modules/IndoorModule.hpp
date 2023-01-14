#pragma once

#ifndef MODULE
    #include "Module.hpp"
    #define MODULE
#endif

class IndoorModule: public Module
{
public:
    IndoorModule();
    IndoorModule(JsonObject indoorModuleData);
    bool init(JsonObject indoorModuleData);
    bool update(JsonObject indoorModuleData);

    uint32_t getMeasureTimestamp() const;
    float getTemperatureCelsius() const;
    float getMaxTemperatureCelsius() const;
    float getMinTemperatureCelsius() const;
    uint32_t getDateMaxTemperature() const;
    uint32_t getDateMinTemperature() const;
    uint8_t getHumidityPercentage() const;
    uint16_t getCO2ppm() const;

    String generateStatusReport();
    ~IndoorModule();
private:
    uint32_t measure_timestamp_local_epoch_;
    float temperature_Celsius_;
    uint16_t CO2_ppm_;
    uint8_t humidity_percentage_;
    float min_temperature_Celsius_;
    uint32_t date_min_temperature_local_epoch_;
    float max_temperature_Celsius_;
    uint32_t date_max_temperature_local_epoch_;
};