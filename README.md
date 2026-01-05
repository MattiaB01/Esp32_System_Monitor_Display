Wifi Manager ESP-IDF
====================

This is a simple wifi manager. It's a pure C esp-idf component.
It enables easy management of wifi networks through a web page.

To init the library:
```
startWifi();
```

### How to add the library to your project

The only thing to do is add the files 
wifi.c and wifi.h to your project

To manage your credentials you have to connect via wifi to the SSID:
**MyESP32AP**
than you have to connect to the address:
```
http://esp32
```
Your credentials will be permanently stored in flash memory (NVS - Non-Volatile Storage).

At the next startup the esp32 will try to connect with the previously saved credentials.

The library also includes a wifi scanner. 

![screen](https://github.com/MattiaB01/Wifi_Manager_EspIDF/assets/104713814/ff005a4a-0c36-4aec-aef9-421d178e1be6)






