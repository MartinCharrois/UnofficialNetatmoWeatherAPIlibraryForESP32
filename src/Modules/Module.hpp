#pragma once

#ifndef ARDUINO_JSON
    #include <ArduinoJson.h>
    #define ARDUINO_JSON
#endif


typedef enum{
    UP,
    DOWN,
    STABLE
} temperature_trend;

class Module
{
public:
    Module();
    Module(JsonObject moduleData);
    bool init(JsonObject moduleData);
    bool update(JsonObject moduleData);
    //get module parameters/status
    String getMacAddress() const;
    String getModuleName() const;
    uint32_t getLastSetupLocalEpochTime() const;
    bool wasConnectedWithinLast4hr() const;
    uint8_t getFirmwareVersion() const;
    uint32_t getLastMessageLocalEpochTime() const;
    uint32_t getLastStatusUpdateLocalEpochTime() const;
    uint8_t getSignalStrength() const;
    uint16_t getBatteryStatus() const;
    uint8_t getBatteryPercentage() const;
    String generateStatusReport();

    ~Module();
protected:
    String id_mac_address_;
    String type_; //I'm not sure of this data relevance, I kept it just in case someone have use of i_t
    String module_name_;
    uint32_t date_last_setup_local_epoch_;
    bool connected_to_cloud_within_last_4hr_;
    uint8_t firmware_version_;
    uint32_t date_last_message_local_epoch_;
    uint32_t date_last_status_update_local_epoch_;
    uint8_t rf_status_;
    uint16_t battery_status_;
    uint8_t battery_percentage_;
};