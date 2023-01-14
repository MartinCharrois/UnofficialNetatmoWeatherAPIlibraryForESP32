#pragma once

#ifndef Arduino
    #include "Arduino.h"
    #define Arduino
#endif

#ifndef EXTERNAL_LIBRARIES
    #include <HTTPClient.h>
    #include "time.h"
    #ifndef ARDUINO_JSON
        #include "ArduinoJson.h"
        #define ARDUINO_JSON
    #endif
    #define EXTERNAL_LIBRARIES
#endif

#include "WeatherStation.hpp"
#include "Token.hpp"
#include "Modules/StationModule.hpp"
#include "Modules/IndoorModule.hpp"
#include "Modules/OutdoorModule.hpp"
#include "Modules/RainGauge.hpp"
#include "modules/WindModule.hpp"
