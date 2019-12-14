
# Viessmann Heizungen mit Loxone Steuern und das für unter 10€...

Mit diesem Gerät kann man aus Viessmann-Heizungen auslesen: 
- Abgastemperatur
- Außentemperatur
- Eingestellte Raumtemperatur
- Vorlauftemperatur
...und steuern:
- Raumtemperatur

Diese Datenpunkte werden später erweitert. 

Hardware:
- NodeMCU (reichelt: https://www.reichelt.de/nodemcu-esp8266-wifi-modul-debo-jt-esp8266-p219900.html)
- Widerstand 10 kOhm (reichelt: https://www.reichelt.de/widerstand-kohleschicht-10-kohm-axial-500-mw-5-arc-rcc050-10k-j-p237477.html?r=1)
- Widerstand 180 Ohm (reichelt: https://www.reichelt.de/widerstand-kohleschicht-180-ohm-0207-250-mw-5-1-4w-180-p1362.html?r=1)
- IR-LED 880nm 3mm (reichelt: https://www.reichelt.de/ir-led-880-nm-3-mm-t1-l-7104sf4bt-kb-p216819.html?r=1)
- IR-Fototransistor SFH 309 FA (reichelt: https://www.reichelt.de/fototransistor-npn-35v-165ma-0-165w-bedrahtet-sfh-309-fa-p60553.html?r=1)

Hinweis:
Es empfiehlt sich von den Kleinteilen mehr als nur 1 zu bestellen, denn bricht ein Beinchen ab oder ähnliches, trauert man um die paar Cent nicht... Ein passendes Netzteil hat man meist noch rumliegen, ansonsten gibt es dieses hier: https://www.reichelt.de/usb-ladegeraet-5-v-2500-ma-schwarz-microusb-otb-8012053-p263200.html?&trstct=pos_7

Software:
- Basierend auf der Bibliothek von @bertmelis https://github.com/bertmelis/VitoWiFi
- Außerdem noch auf ESP8266WiFi.h, WiFiUdp.h und natürlich der Arduino.h

Hinweis: Der String MiniserverIP funktioniert noch nicht richtig... im Code gibt es zwei Stellen, bei denen man diese ändern muss, bei WLAN und dem Port klappt das aber schon (Java ist eher meins). Die Software ist nicht schön geschrieben, das wird in späteren Versionen noch erledit.

Drumherum: 
- 3D-gedruckter V-Halter... dort kann man die Dioden per Feuerzeug oder Lötkolben einbrennen... Das wird noch verbessert... 

Programmierung:
- Dateien für Virtuelle Ausgänge / Eingänge in der Repo... In Loxone unter Vordefinierte... importieren... und IP ersetzen...


Bei Fragen bin ich über das loxforum (https://www.loxforum.com/member/8211-loxcat) erreichbar... 

Disclaimer: Keine Haftung für Schäden an Heizungsanlagen (getestet mit der Vitodens 200-W 19kW 2013)
