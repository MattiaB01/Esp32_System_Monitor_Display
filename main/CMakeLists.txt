# See the build system documentation in IDF programming guide
# for more information about component CMakeLists.txt files.

idf_component_register(
    SRCS   main.c    # list the source files of this component
    #INCLUDE_DIRS      "include"  # optional, add here public include directories
    PRIV_INCLUDE_DIRS   # optional, add here private include directories
    #REQUIRES           mdns esp_http_server  nvs_flash esp_wifi esp_http_client driver
    REQUIRES			mqtt
    PRIV_REQUIRES       wifi_manager ssd1306
    
   
)
