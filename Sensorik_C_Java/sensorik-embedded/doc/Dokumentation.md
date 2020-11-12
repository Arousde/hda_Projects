# Projektübersicht
Wir haben das Board CY8CKIT-149 PsoC 4100S Plus Prototyping Kit benutzt, um Umweltdaten zu erfassen und diese dann per BLE an ein mobiles Endgerät weiterzuleiten. Auf diesem hat dann die Frontend-Gruppe eine Auswertung und Ansicht der Daten ermöglicht.

> Git Link: https://code.fbi.h-da.de/pse_mayer_ss19/sensorik/tree/master

# Sensoren

> Git Link: https://code.fbi.h-da.de/pse_mayer_ss19/sensorik/tree/master/sensorik.cydsn

## VOCSens

Das [VOCSens board](https://www.glyn.de/Produkte/Sensoren/VOCSens) vereint die zwei Sensoren [SHT31](https://www.sensirion.com/en/environmental-sensors/humidity-sensors/digital-humidity-sensors-for-various-applications/) und [SGP30](https://www.sensirion.com/de/umweltsensoren/gassensoren/multipixel-gassensoren/) auf einem Board. Beide wurden hegestellt von [Sensirion](https://www.sensirion.com/en/).

## SHT31 Sensor

[Der benutzte Treiber](https://github.com/Sensirion/embedded-sht) ist von Sensirion erstellt.

Initialisiere den SHT31 Sensor.  
Erst initialisiert man zwei Floats, einen für die Temperatur und einen für die Luftfeuchtigkeit.  
Dann initialisiert man entweder zwei Pointer auf diese Variablen und übergibt diese an die Messfunktion, oder übergibt deren Adressen direkt.  
Man hat die Wahl zwischen einer blockierenden und einer nicht blockierenden Funktion während der Messung. Im zweiten Fall muss man sichergehen genug Zeit verstreichen zu lassen, so dass der Sensor die Messung fertigstellen kann (in dem Fall 15ms).

Die UART nutzt eine baud rate von 115200.  
Das ° Symbol der Temperatur könnte im Terminal nicht richtig dargestellt werden.

Die Terminalausgabe sollte folgendermaßen aussehen:
```
Measured temperature: 24.152°C
Measured humidity:    50.531%
Measured temperature: 24.165°C
Measured humidity:    50.521%
Measured temperature: 24.136°C
Measured humidity:    50.543%
Measured temperature: 24.152°C
Measured humidity:    50.531%
...
```
### Kombinierung mit einem anderen Projekt

- Die \*.c und \*.h Dateien in das neue Projekt kopieren, **nicht** aber die main.c
- Beide Elemente des **TopDesign** in das neue Projekt kopieren
- Die Pins entsprechend der Anwendungen belegen (Dieses Projekt nutzt 3.0 für I2C scl, 3.1 für I2C sda; 7.0 für UART rx und 7.1 für UART tx)  
- SHT31.h in die main.c inkludieren
- Den Sensor mit  `GY_SHT31_Init()` einmalig initialisieren 

Um eine Messung durchzuführen die Funktion `GY_SHT31_Measure(double* temperature_, double* humidity_, bool console_out)` wie folgt aufrufen:  
```C++
double temperature;
double humidity;

GY_SHT31_Measure(&temperature, &humidity, true);
```

Info: Die Funktion blockiert während der Messung.
Man kann daher auch die Funktion `GY_SHT31_Ready_Measurement();` und `GY_SHT31_Read_Measurement(double* temperature_, double* humidity_, bool console_out);` als eine nicht-blockierende Alternative verwenden:  
```C++
double temperature;
double humidity;

GY_SHT31_Ready_Measurement();
CyDelay(15);
GY_SHT31_Read_Measurement(&temperature, &humidity, true);
```

> Git Link: https://code.fbi.h-da.de/pse_mayer_ss19/sensorik/tree/master/sensorik.cydsn/SHT31

## Adafruit SGP30
Dieser Sensor misst eCO2  und TVOC.
### eCO2  (equivalent calculated carbon-dioxide)
Äquivalentes CO2  ist die Konzentration von CO2 , die den gleichen Strahlungsantrieb verursachen würde wie eine bestimmte Art und Konzentration von Treibhausgas. Beispiele für solche Treibhausgase sind Methan, Perfluorkohlenwasserstoffe und Lachgas. eCO2  wird als parts per million by volume ausgedrückt, ppmv.

### TVOC (Total Volatile Organic Compound)
Die englische Abkürzung VOC (Volatile Organic Compounds) bezeichnet die Gruppe der flüchtigen organischen Verbindungen. VOC umschreibt gas- und dampfförmige Stoffe organischen Ursprungs in der Luft. Dazu gehören zum Beispiel Kohlenwasserstoffe, Alkohole, Aldehyde und organische Säuren. Viele Lösemittel, Flüssigbrennstoffe und synthetisch hergestellte Stoffe können als VOC auftreten, aber auch zahlreiche organische Verbindungen, die in biologischen Prozessen gebildet werden. Viele hundert verschiedene Einzelverbindungen können in der Luft gemeinsam auftreten.
  
Konzentrationen, die gesundheitliche Beeinträchtigungen bewirken, können unmittelbar nach Bau- und umfangreichen Renovierungsmaßnahmen auftreten, sowie bei unsachgemäßer Verarbeitung und massivem Einsatz wenig geeigneter Produkte. Geruchsbelästigungen, Reizungen und Symptome, die nicht unmittelbar einer Krankheit zugeordnet werden können, wurden als akute Wirkungen auf Menschen beschrieben. Diese Effekte müssen vermieden werden, ebenso mögliche chronische Wirkungen, die Wissenschaftlerinnen und Wissenschaftler aus toxikologischen Beurteilungen abgeleitet haben; besonders natürlich krebserzeugende, erbgutverändernde und fortpflanzungsgefährdende Wirkungen.[1]

[1] https://www.umweltbundesamt.de/themen/gesundheit/umwelteinfluesse-auf-den-menschen/chemische-stoffe/fluechtige-organische-verbindungen

> Git Link: https://code.fbi.h-da.de/pse_mayer_ss19/sensorik/tree/master/sensorik.cydsn/SGP30

## SPS30

Dieser Sensor misst den Feinstaubgehalt in der Luft für Partikel einer bestimmten Größenordnung.

```C++
struct sps30_measurement{
    // Mass concentration in μg/m^3 (Microgram per cubic meter);  μ = 10^-6
    float32_t mc_1p0;  // PM1.0  < 1.0 μm (Micrometer)
    float32_t mc_2p5;  // PM2.5  < 2.5 μm
    float32_t mc_4p0;  // PM4.0  < 4.0 μm
    float32_t mc_10p0; // PM10.0 < 10.0 μm
    // Amount per cm^3
    float32_t nc_0p5;  // PM0.5  < 0.5 μm
    float32_t nc_1p0;  // PM1.0  < 1.0 μm
    float32_t nc_2p5;  // PM2.5  < 2.5 μm
    float32_t nc_4p0;  // PM4.0  < 4.0 μm
    float32_t nc_10p0; // PM10.0 < 10.0 μm
    float32_t typical_particle_size;
};
```
> Git Link: https://code.fbi.h-da.de/pse_mayer_ss19/sensorik/tree/master/sensorik.cydsn/SPS30

# Event Struktur

In der main.c des Sensorik Projektes werden im Code Abschnitte definiert, die Eventstrukturen gebrauchen um Daten möglichst effektiv weiterzuleiten und darzustellen.


# Projekt-Taler
Wir haben uns für eine äquivalente Verteilung der Projekt-Taler entschieden. Sprich: Jeder bekommt 16.67 Taler für die geleistete Arbeit.

# Autoren
Nima Esmaeepour  
Timo Kautzmann  
Lennard Niesig  
Felix Ohms  
Maximilian Reinheimer  
Lucas Schürrmann  