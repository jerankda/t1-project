# Erweiterung des T1-Projekts

Dieses Projekt erweitert das bestehende T1-Projekt, indem es zusätzliche Funktionalitäten mit dem ESP32 hinzufügt. Der ESP32 erfasst Temperatur- und Bodenfeuchtigkeitswerte und sendet sie an einen Server, der die Daten live auf einer Webseite anzeigt.

## Funktionen

- **Temperaturmessung** mit einem DS18B20-Sensor
- **Bodenfeuchtigkeitsmessung** mit einem Feuchtigkeitssensor
- **Live-Datenanzeige** auf einer Webseite

## Hardware

- **ESP32**
- **DS18B20** Temperatursensor
- **Bodenfeuchtigkeitssensor**
- Kabel, Steckbrett, etc.

## Software

- **Arduino IDE** (für den ESP32-Code)
- **Python 3** mit **Flask** (für den Webserver)
- **Nginx** (falls auf einem Server eingesetzt)
- **Virtuelle Umgebung (venv)** zur Verwaltung der Python-Abhängigkeiten

## Installation

### ESP32-Code hochladen

1. **Arduino IDE einrichten**: Stelle sicher, dass die ESP32-Board-Definitionen installiert sind.
2. **Code anpassen**: Bearbeite die WLAN-Zugangsdaten im Code:

   #define EAP_ANONYMOUS_IDENTITY "BENUTZERNAME"
   #define EAP_IDENTITY "BENUTZERNAME"
   #define EAP_PASSWORD "PASSWORT"
   const char *ssid = "SSID";

3. **Code hochladen**: Schließe den ESP32 an deinen PC an und lade den Code hoch.

### Server einrichten

1. **Projektdateien hochladen**: Lade die `sensor_web`-Dateien auf deinen Server.
2. **Virtuelle Umgebung einrichten**:

   python3 -m venv sensor_venv  
   source sensor_venv/bin/activate  
   pip install -r requirements.txt

3. **Webserver starten**: Nutze Flask oder richte Nginx mit Gunicorn für den Produktionsbetrieb ein.

### Nginx (optional)

Falls du das Projekt auf einem Server laufen lassen möchtest, kannst du Nginx als Reverse Proxy einrichten.

1. **Konfiguration bearbeiten**:

   sudo nano /etc/nginx/sites-available/sensor_web

2. **Nginx neu starten**:

   sudo systemctl restart nginx

## Verwendung

Nach dem Start des Webservers kannst du die Webseite im Browser aufrufen, um die live übermittelten Sensordaten zu sehen.
