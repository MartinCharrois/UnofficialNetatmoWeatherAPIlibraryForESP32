# include <Arduino.h>

const String module_data_reachable_string = "{\
            \"_id\": \"05:00:00:01:97:b8\",  \
            \"type\": \"NAModule3\",  \
            \"module_name\": \"Pluviom\u00e8tre\",  \
            \"last_setup\": 1440229449,  \
            \"data_type\": [\"Rain\"],  \
            \"pluvio_scale_auget_to_mm\": 0.1146752205292702,  \
            \"battery_percent\": 100,  \
            \"battery_level\": \"full\",  \
            \"reachable\": true,  \
            \"firmware\": 12,  \
            \"last_message\": 1668718798,  \
            \"last_seen\": 1668718792,  \
            \"rf_status\": 56,  \
            \"battery_vp\": 6004,  \
            \"dashboard_data\": {  \
                \"time_utc\": 1668718779,  \
                \"Rain\": 0.6,  \
                \"sum_rain_1\": 0,  \
                \"sum_rain_24\": 4.9,  \
                \"Temperature\": 20.6,  \
                \"CO2\": 664,  \
                \"Humidity\": 64,  \
                \"min_temp\": 19.1,  \
                \"max_temp\": 21,  \
                \"date_max_temp\": 1668711493,  \
                \"date_min_temp\": 1668678374,  \
                \"WindStrength\":2,  \
                \"WindAngle\":75,  \
                \"GustStrength\":3,  \
                \"GustAngle\":75,  \
                \"max_wind_str\":4,  \
                \"max_wind_angle\":100,  \
                \"date_max_wind_str\":1555673190,\
                \"Noise\":36,\
                \"Pressure\":1001.1,\
                \"AbsolutePressure\":991.5,\
                \"pressure_trend\":\"up\"\
                } \
            }";

const char refGeneralStatus[] = "module name : Pluviom\xC3\xA8tre\n MAC address : 05:00:00:01:97:b8\n Firmware version : 12\n Last message (local epoch time) : 1668718798\n Last status update (local epoch time) : 1440229449\n Module was connected to cloud in the last 4hours\n Battery Status : 6004\n Battery Charge (%) : 100\n Signal Strength : 56";

const char refUnreachableGeneralStatus[] = "module name : null\n MAC address : null\n Firmware version : 0\n Last message (local epoch time) : 0\n Last status update (local epoch time) : 0\n Module was not connected within last 4 hours, impossible to show status";

const char rainGaugeRefGeneralStatus[] = "module name : Pluviom\xC3\xA8tre\n MAC address : 05:00:00:01:97:b8\n Firmware version : 12\n Last message (local epoch time) : 1668718798\n Last status update (local epoch time) : 1440229449\n Module was connected to cloud in the last 4hours\n Battery Status : 6004\n Battery Charge (%) : 100\n Signal Strength : 56\n Timestamp of latest Data availlable (local epoch Time) : 1668718779\n Rain level in millimeters : 0.60\n Cumulated rain in the last hour before the timestamp (mm) : 0.00\n Cumulated rain in the last 24 hour before the timestamp (mm) : 4.90";

const char windModuleRefGeneralStatus[] = "module name : Pluviom\xC3\xA8tre\n MAC address : 05:00:00:01:97:b8\n Firmware version : 12\n Last message (local epoch time) : 1668718798\n Last status update (local epoch time) : 1440229449\n Module was connected to cloud in the last 4hours\n Battery Status : 6004\n Battery Charge (%) : 100\n Signal Strength : 56\n Timestamp of latest Data availlable (local epoch Time) : 1668718779\n Wind strength in KpH : 2\n Wind angle in degrees : 75\n Date of the maximal wind strength (local epoch Time) : 1555673190\n Maximal wind strength measured in Kph : 4\n Maximal wind angle measured in Degrees : 100\n Gust strength in KpH : 3\n Gust Angle in KpH : 75";

const char indoorModuleRefGeneralStatus[] = "module name : Pluviom\xC3\xA8tre\n MAC address : 05:00:00:01:97:b8\n Firmware version : 12\n Last message (local epoch time) : 1668718798\n Last status update (local epoch time) : 1440229449\n Module was connected to cloud in the last 4hours\n Battery Status : 6004\n Battery Charge (%) : 100\n Signal Strength : 56\n Timestamp of latest Data availlable (local epoch Time) : 1668718779\n Indoor CO2 concentration in the air (ppm) : 664\n Indoor Humidity percentage : 64\n Indoor temperature (Celsius) : 20.60\n Indoor minimal temperature (Celsius) : 19.10\n Timestamp of the minimal temperature (local epoch time): 1668678374\n Indoor maximal temperature (Celsius) : 21.00\n Timestamp of the maximal temperature (local epoch time) : 1668711493";

const char outdoorModuleRefGeneralStatus[] = "module name : Pluviom\xC3\xA8tre\n MAC address : 05:00:00:01:97:b8\n Firmware version : 12\n Last message (local epoch time) : 1668718798\n Last status update (local epoch time) : 1440229449\n Module was connected to cloud in the last 4hours\n Battery Status : 6004\n Battery Charge (%) : 100\n Signal Strength : 56\n Timestamp of latest Data availlable (local epoch Time) : 1668718779\n Outdoor Humidity percentage : 64\n Outdoor temperature (Celsius) : 20.60\n Outdoor minimal temperature (Celsius) : 19.10\n Timestamp of the minimal temperature (local epoch time): 1668678374\n Outdoor maximal temperature (Celsius) : 21.00\n Timestamp of the maximal temperature (local epoch time) : 1668711493";

const char stationModuleRefGeneralStatus[] = "module name : Pluviom\xC3\xA8tre\n MAC address : 05:00:00:01:97:b8\n Firmware version : 12\n Last message (local epoch time) : 1668718798\n Last status update (local epoch time) : 1440229449\n Module was connected to cloud in the last 4hours\n Battery Status : 6004\n Battery Charge (%) : 100\n Signal Strength : 56\n Timestamp of latest Data availlable (local epoch Time) : 1668718779\n Indoor CO2 concentration in the air (ppm) : 664\n Indoor Humidity percentage : 64\n Indoor temperature (Celsius) : 20.60\n Indoor minimal temperature (Celsius) : 19.10\n Timestamp of the minimal temperature (local epoch time): 1668678374\n Indoor maximal temperature (Celsius) : 21.00\n Timestamp of the maximal temperature (local epoch time) : 1668711493\n Noise level in dB : 36\n surface pressure in mbar : 1001.10\n sea level pressure in mbar: 991.50\n pressure trend for the last 12hrs : up";