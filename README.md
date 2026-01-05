# ESP32 System monitor

Questo progetto permette a un ESP32 di visualizzare in tempo reale i dati di sistema di un PC (CPU, RAM, spazio su disco) su un piccolo display OLED 128×64 tramite MQTT.

---

## Scopo

- Visualizzare in tempo reale le risorse del PC su un display remoto.
- Mostrare percentuale CPU, percentuale RAM e spazio libero su disco.
- Usare ESP32 come **display “Nerd Monitor”**.
- Permettere configurazione Wi-Fi tramite una rete **Access Point** dedicata e pagina web all’indirizzo `http://esp32`.

---

## Requisiti

- **Hardware**
  - ESP32 con supporto I²C/SPI
  - Display OLED 128×64 (SSD1306 o compatibile)
  - Connessione Wi-Fi

- **Software**
  - Programma Java per inviare dati del PC tramite MQTT  
    (scaricabile dal repository GitHub: [])
  - Broker MQTT (es. Mosquitto)
  - ESP-IDF v5.x

---

## Funzionalità Wi-Fi

- Al primo avvio (o se non trova rete configurata), l’ESP32 crea una **rete Wi-Fi Access Point**.
- Collegandosi a questa rete, si può aprire la pagina web `http://esp32` per inserire:
  - SSID della rete Wi-Fi
  - Password della rete Wi-Fi
- Dopo la configurazione, l’ESP32 si collega automaticamente alla rete e al broker MQTT.


