#include "Module.hpp"

Module::Module(){}

Module::Module(JsonObject moduleData)
{
    init(moduleData);
}

bool Module::init(JsonObject moduleData){
    if(moduleData.isNull()){
        return false ;
    }
    id_mac_address_ = moduleData["_id"].as<String>();
    type_ = moduleData["type"].as<String>();
    module_name_ = moduleData["module_name"].as<String>();
    date_last_setup_local_epoch_ = moduleData["last_setup"].as<uint32_t>();
    connected_to_cloud_within_last_4hr_ = moduleData["reachable"].as<bool>();
    firmware_version_ = moduleData["firmware"].as<uint8_t>();
    date_last_message_local_epoch_ = moduleData["last_message"].as<uint32_t>();
    date_last_status_update_local_epoch_ = moduleData["last_seen"].as<uint32_t>();
    rf_status_ = moduleData["rf_status"].as<uint8_t>();
    battery_status_ = moduleData["battery_vp"].as<uint16_t>();
    battery_percentage_ = moduleData["battery_percent"].as<uint8_t>();
    return true ;
}

bool Module::update(JsonObject moduleData){
    if(moduleData.isNull()){
        return false ;
    }
    date_last_setup_local_epoch_ = moduleData["last_setup"].as<uint32_t>();
    connected_to_cloud_within_last_4hr_ = moduleData["reachable"].as<bool>();
    firmware_version_ = moduleData["firmware"].as<uint8_t>();
    date_last_message_local_epoch_ = moduleData["last_message"].as<uint32_t>();
    date_last_status_update_local_epoch_ = moduleData["last_seen"].as<uint32_t>();
    rf_status_ = moduleData["rf_status"].as<uint8_t>();
    battery_status_ = moduleData["battery_vp"].as<uint16_t>();
    battery_percentage_ = moduleData["battery_percent"].as<uint8_t>();
    return true ;
}

String Module::getMacAddress() const{ return(id_mac_address_);}
String Module::getModuleName() const{ return(module_name_);}
uint32_t Module::getLastSetupLocalEpochTime() const{ return(date_last_setup_local_epoch_);}
bool Module::wasConnectedWithinLast4hr() const{ return(connected_to_cloud_within_last_4hr_);}
uint8_t Module::getFirmwareVersion() const{ return(firmware_version_);}
uint32_t Module::getLastMessageLocalEpochTime() const{ return(date_last_message_local_epoch_);}
uint32_t Module::getLastStatusUpdateLocalEpochTime() const{ return(date_last_status_update_local_epoch_);}
uint8_t Module::getSignalStrength() const{ return(rf_status_);}
uint16_t Module::getBatteryStatus() const{ return(battery_status_);}
uint8_t Module::getBatteryPercentage() const{ return(battery_percentage_);}

String Module::generateStatusReport(){
    String GeneralStatus = "module name : " + module_name_;
    GeneralStatus += "\n MAC address : " + id_mac_address_;
    GeneralStatus += "\n Firmware version : " + String(firmware_version_);
    GeneralStatus += "\n Last message (local epoch time) : " + String(date_last_message_local_epoch_);
    GeneralStatus += "\n Last status update (local epoch time) : " + String(date_last_setup_local_epoch_);
    if(wasConnectedWithinLast4hr()){
        GeneralStatus += "\n Module was connected to cloud in the last 4hours";
        GeneralStatus += "\n Battery Status : " + String(battery_status_);
        GeneralStatus += "\n Battery Charge (%) : " + String(battery_percentage_);
        GeneralStatus += "\n Signal Strength : " + String(rf_status_);
    }else{
        GeneralStatus += "\n Module was not connected within last 4 hours, impossible to show status";
    }
    return(GeneralStatus);
}

Module::~Module()
{
}

