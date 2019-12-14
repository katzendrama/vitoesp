
Viessmann Heizungen mit Loxone Steuern und das für unter 10€...

Hardware:
- NodeMCU (reichelt: https://www.reichelt.de/nodemcu-esp8266-wifi-modul-debo-jt-esp8266-p219900.html)
- Widerstand 10 kOhm (reichelt: https://www.reichelt.de/widerstand-k...-p237477.html?)
- Widerstand 180 Ohm (reichelt: https://www.reichelt.de/widerstand-k...80-p1362.html?)
- IR-LED 880nm 3mm (reichelt: https://www.reichelt.de/ir-led-880-n...-p216819.html? )
- IR-Fototransistor SFH 309 FA (reichelt: https://www.reichelt.de/fototransist...?&trstct=pos_0)

Hinweis:
Es empfiehlt sich von den Kleinteilen mehr als nur 1 zu bestellen, denn bricht ein Beinchen ab oder ähnliches, trauert man um die paar Cent nicht... Ein passendes Netzteil hat man meist noch rumliegen, ansonsten gibt es dieses hier: https://www.reichelt.de/usb-ladegeraet-5-v-2500-ma-schwarz-microusb-otb-8012053-p263200.html?&trstct=pos_7

Software:
- Basierend auf der Bibliothek von @bertmelis https://github.com/bertmelis/VitoWiFi
- Außerdem noch auf ESP8266WiFi.h, WiFiUdp.h und natürlich der Arduino.h

Hinweis: Der String MiniserverIP funktioniert noch nicht richtig... im Code gibt es zwei Stellen, bei denen man diese ändern muss, bei WLAN und dem Port klappt das aber schon (Java ist eher meins). Die Software ist nicht schön geschrieben, das wird in späteren Versionen noch erledit.

Drumherum: 
- 3D-gedruckter V-Halter... dort kann man die Dioden per Feuerzeug oder Lötkolben einbrennen... Das wird noch verbessert... 


Bei Fragen bin ich über das loxforum (https://www.loxforum.com/member/8211-loxcat) erreichbar... 
