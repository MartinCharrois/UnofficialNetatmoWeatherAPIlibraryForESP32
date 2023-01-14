#pragma once

#ifndef MODULE
    #include "Module.hpp"
    #define MODULE
#endif

class WindModule: public Module    //Note thati personally don't own a wind module so I couldn't test this class
{
public:
    WindModule();
    WindModule(JsonObject windModuleData);
    bool init(JsonObject windModuleData);
    bool update(JsonObject windModuleData);

    uint32_t getMeasureTimestamp() const;
    uint16_t getWindStrengthKPH() const;
    int16_t getWindAngleDegree() const;
    uint16_t getGustStrengthKPH() const;
    int16_t getGustAngleDegree() const;
    uint16_t getMaxWindStrengthKPH() const;
    int16_t getMaxWindAngleDegree() const;
    uint32_t getDateMaxWindStrength() const;
    String generateStatusReport();
    ~WindModule();
private:
    uint32_t measure_timestamp_local_epoch_;
    uint16_t wind_strength_kph_;
    int16_t wind_angle_degree_;
    uint16_t gust_strength_kph_;
    int16_t gust_angle_degree_;
    uint16_t max_wind_strength_kph_;
    int16_t max_wind_angle_degree_;
    uint32_t date_max_wind_strength_local_epoch_;
};