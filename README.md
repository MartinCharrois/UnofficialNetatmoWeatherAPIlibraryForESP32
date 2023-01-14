# Unofficial Netatmo Weather API Library for ESP32

[![Release](https://img.shields.io/github/v/release/MartinCharrois/UnofficialNetatmoWeatherAPIlibraryForESP32)](https://github.com/MartinCharrois/UnofficialNetatmoWeatherAPIlibraryForESP32/releases)
[![Esp32](https://img.shields.io/badge/platform-ESP32-green)](https://www.espressif.com/en/products/socs/esp32)

This is a library for ESP32 allowing makers to fetch data from their own Netatmo Weather Station. It was first designed to build a custom weather display.

Note : No cyber security concern was considered in the development of this library, use at your own risk! if you have some cyber security knowledge, any improvement suggestion is welcomed
note bis : this library is still in development so if you encounter bugs, don’t hesitate to create a [new issue on GitHub](https://github.com/MartinCharrois/UnofficialNetatmoWeatherAPIlibraryForESP32/issues/new)
note tierce : this library is still in development, so if you need a particular feature why don't implement it yourself?

## Features

- independent management of authentication token and weather station
- automatic refresh of the token when expired
- implementation of getStationsdata request from Netatmo weather API
- use of [ArduinoJson library by Benoit BLANCHON](https://arduinojson.org/) to deserialize Json request answer
- Generation of reports for the whole station or only modules for a quick overview of the data availlable for your station/ modules
- access to measure timestamp in local epoch time format

## Limitations

- no verification of internet connection
- take a lot of memory space
- can access only one weather station per user
- take into account only one rain gauge and one wind module per station
- only access your own weather station
- if you have multiple indoor or outdoor modules, you can only access one of each (the first in the data from the request)

## Quickstart

- install the [Unofficial Netatmo Weather API Library for ESP32](https://github.com/MartinCharrois/UnofficialNetatmoWeatherAPIlibraryForESP32) (you can use the platformIO library manager and search for Unofficial Netatmo Weather API Library for ESP32)
- look at the quickstart example

## Examples

| Example             | Description                                |
| ------------------- | ------------------------------------------ |
| [QuickStart](https://github.com/MartinCharrois/UnofficialNetatmoWeatherAPIlibraryForESP32/tree/main/examples/QuickStart/main.cpp) | generate a full report of your station and show you all the data provided by this library   |
| [Typical use](https://github.com/MartinCharrois/UnofficialNetatmoWeatherAPIlibraryForESP32/tree/main/examples/TypicalExample/main.cpp) | show you how to typically use the library     |

## Standard way to use the library

See [the typical use example](https://github.com/MartinCharrois/UnofficialNetatmoWeatherAPIlibraryForESP32/tree/main/examples/TypicalExample/main.cpp).

1. Create a global `Token` instance
2. `.init(credentials)` your token object with your app and netAtmo credentials (see. [How to register an app on Netatmo services](#create-an-app-on-netatmo-services))
3. Create a global `WeatherStation` instance
4. `.init(token pointer)` your weather station to make a request and store data
5. Use `get<module type>Pointer()` to get a pointer to the corresponding module
6. Then access the data you need using `get...()` methods (except for boolean which methods start with `is....()` or `was...()`)
7. Update the data by using `.update()` on your weather station

## Create an app on Netatmo services

In order to access the Netatmo Weather API, you need credentials. This section explains how to register your app and get those credentials.

- Go to the [Netatmo dev website](https://dev.netatmo.com/) and login with your classic Netatmo account.
- Then click on your username on the top right corner and click on **My apps**
![[figures/my-apps-menu.png]]
- Click on **Create** to register your apps. fill in the form. After completing the procedure, you'll get a client ID and a client secret key. They are used by the `Token.init(...)` method to fetch your authentication token.

## TODO List

- Add handling of multiple indoor or outdoor modules
- Implement a time management in `.update()`. as Netatmo refresh the data available on their servers every 5 minutes, it's useless to try updating more frequently
- Implement `get...Pointer()` method to return pointers to data. this way we don't have to use `get...()` methods after each `.update()`
- Add a connectivity verification before making requests
- Extend the error handling of request methods

## License

MIT, see [LICENSE](https://github.com/MartinCharrois/UnofficialNetatmoWeatherAPIlibraryForESP32/blob/main/LICENSE)
