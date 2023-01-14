#pragma once

#ifndef MODULE
    #include "Module.hpp"
    #define MODULE
#endif

class RainGauge: public Module
{
public:
    RainGauge();
    RainGauge(JsonObject rainGaugeData);
    bool init(JsonObject rainGaugeData);
    bool update(JsonObject rainGaugeData);

    uint32_t getMeasureTimestamp() const;
    float getRainMM() const;
    float getLast24hrTotalRainMM() const;
    float getLast1hrTotalRainMM() const;
    String generateStatusReport();
    ~RainGauge();
private:
    uint32_t measure_timestamp_local_epoch_;
    float rain_mm_;
    float last_24hr_total_rain_mm_;
    float last_1hr_total_rain_mm_;
};