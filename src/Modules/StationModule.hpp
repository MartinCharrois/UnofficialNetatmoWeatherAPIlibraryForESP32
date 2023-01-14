#pragma once

#include "IndoorModule.hpp"

class StationModule : public IndoorModule
{
public:
    StationModule();
    StationModule(JsonObject stationData);
    bool init(JsonObject stationData);
    bool update(JsonObject stationData);

    uint8_t getNoiseLeveldB()const;
    String getLast12hrsPressureTrend() const;
    float getSurfacePressurembar()const;
    float getSeaLevelPressurembar()const;

    String generateStatusReport();

    ~StationModule();
private:
    uint8_t noise_level_dB_;
    String pressure_trend_;
    float pressure_mbar_;
    float absolute_pressure_mbar_;
};