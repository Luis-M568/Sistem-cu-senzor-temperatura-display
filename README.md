# Sistem-cu-senzor-temperatura-display
Arduino Nano + LCD I2C + HW-481 Sensor

Acest proiect utilizează un Arduino Nano împreună cu un display LCD I2C și un senzor analogic HW-481 pentru monitorizarea și afișarea valorilor citite de senzor în timp real.

Funcționalități
Citire date analogice de la senzorul HW-481
Afișare valori pe display LCD I2C
Comunicare I2C pentru reducerea numărului de pini utilizați
Compatibil cu Arduino Nano
Structură simplă pentru integrare în proiecte embedded / automation
Componente utilizate
Arduino Nano
Display LCD cu interfață I2C
Senzor HW-481
Breadboard
Fire jumper
Alimentare USB 5V
Schema conexiunilor
Componentă	Pin Componentă	Pin Arduino Nano	Rol
LCD I2C	GND	GND	Împământare
LCD I2C	VCC	5V	Alimentare
LCD I2C	SDA	A4	Linie date I2C
LCD I2C	SCL	A5	Linie clock I2C
HW-481	-	GND	Împământare
HW-481	+	5V / 3.3V	Alimentare senzor
HW-481	S	A1	Semnal analogic

Datele conexiunilor sunt bazate pe documentația hardware furnizată.

Biblioteci necesare

Pentru compilare în Arduino IDE:
Wire.h
LiquidCrystal_I2C.h

Exemplu funcționare
Senzorul HW-481 transmite un semnal analogic către pinul A1
Arduino Nano citește valoarea analogică
Valoarea este procesată
Rezultatul este afișat pe LCD prin protocolul I2C

Structura proiectului:
/main.ino
/README.md

Posibile îmbunătățiri
Adăugare praguri de alarmă
Salvare date pe SD card
Transmitere serială către PC
Integrare IoT prin ESP8266 / ESP32
Filtrare software pentru reducerea zgomotului analogic

Domenii de utilizare
Embedded systems
Monitorizare senzori
Proiecte educaționale
Automatizări
Sisteme de măsurare

Licență
Acest proiect poate fi utilizat în scop educațional și experimental.