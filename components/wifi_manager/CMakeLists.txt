idf_component_register(
    SRCS "wifi.c"
    INCLUDE_DIRS "include"
    REQUIRES
        mdns 
        esp_http_server  
        nvs_flash 
        esp_wifi 
        esp_http_client 
        driver
      EMBED_FILES
        "html/favicon.ico"
        "html/app.css"
        "html/index.html"
)
