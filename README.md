# Programmer & Updater Shield
Questa shield e' pensata per rendere comoda l'aggiornamento dei FirmWare sulle schede di illuminazione.</br>
Mette a disposizione un connettore JST SH6 pre configurato per le schede di illuminazione, un porta ISP 'grande' per dei target generici e vari LED di informazione.</br>
Incorpora resistori di PullUp per il Bus I2C Wire disattivabili tramite interruttore.
<img src="https://github.com/TheFidax/ProgrammerUpdaterShield/blob/main/images/shield.jpg" width="1280">

------------

# Indice
* [Upload FirmWare](#Upload-FirmWare)
* [Modalita' Di Funzionamento](#Modalita-Di-Funzionamento)
* [Caratteristiche HardWare](#Caratteristiche-HardWare)
* [Metodi Manipolazione CVs](#Metodi-Manipolazione-CVs)
* [Tipi di Dati](#Tipi-di-Dati)
* [Funzionalita' Extra](#Funzionalita-Extra)

------------

# Upload FirmWare
Il Firmware pensato per la shield e' disponibile sotto la cartella [HEX](https://github.com/TheFidax/ProgrammerUpdaterShield/tree/main/HEX)</br>
Il firmware e' gia' pronto per l'upload sulla scheda Arduino tramite [AVRDUDESS](https://blog.zakkemble.net/avrdudess-a-gui-for-avrdude/)</br>
Per caricare il Firmware e' necessario inserire i seguenti parametri nel software:
- **Programmer (-c)** : *Arduino*
- **Port (-P)** : la porta COM a cui e' connessa la scheda Arduino
- **Baud rate (-b)** : 115200
- Premere **Detect** : Nel *console* verra' restituito il modello del Micro montato sulla Scheda
- **Flash** : il file FIrmWare.hex scaricato
- Infine premere **Programm**
<img src="https://github.com/TheFidax/ProgrammerUpdaterShield/blob/main/images/AVRDUDESS.jpg" width="1280">

------------

# Modalita' Di Funzionamento
La shield presenta *due modalita'* di funzionamento: **ISP** e **I2C**.</br>
Le due modalita' sono *selezionabili* tramite l'interruttore dei resistori di PullUp: se i resistori sono attivi (LED acceso) e' attiva la modalita' **I2C**, se i led e' spento e' attiva la modalita' *ISP*.

*Modalita' ISP*:</br>
La modalita' ISP e' basta sul software [ArduinoAsISP](https://www.arduino.cc/en/Tutorial/BuiltInExamples/ArduinoISP) e permette di utilizzare la scheda Arduino come programmatore ISP per target esterni, utile per scrivere bootloader o per caricare Sketch senza l'ausilio del Bootloader.</br>

*Modalita' I2C*:</br>
In sviluppo.

------------

# Caratteristiche HardWare
**Porte ISP**</br>

<img src="https://github.com/TheFidax/ProgrammerUpdaterShield/blob/main/images/isp_port.jpg" width="1280">
Le porte ISP permettono alla Shield di interfacciarsi con i target.

E' presente una porta ISP a 10 poli che segue lo schema standard degli AVR:</br>
<img src="https://www.waveshare.com/img/devkit/general/10-pin_ISP_Connector_standard.jpg" width="400"></br>
**N.B.** Il pin *VCC* e' collegato alla linea **5 volt**.

E' poi presente una porta JST SH6 che fornisce, al posto dei 5 volt, una linea *non regolata* collegata al pin **VIN** di Arduino.</br> 
<img src="https://github.com/TheFidax/ProgrammerUpdaterShield/blob/main/images/jst_scheme.jpg" width="1280"></br>

------------

**Selettore Reset**</br>

<img src="https://github.com/TheFidax/ProgrammerUpdaterShield/blob/main/images/reset_target.jpg" width="1280"></br>

Tramite questo ponticello e' possibile reindirizzare la linea di Reset delle **Porte ISP** al micro della Scheda Arduino; **e' utile** per poter utilizzare un *programmatore ISP* dotato di porta AVR a 10 pin per scrivere il BootLoader sulla scheda Arduino.</br>

------------

**ISP LED**</br>

<img src="https://github.com/TheFidax/ProgrammerUpdaterShield/blob/main/images/isp_led.jpg" width="1280"></br>

LED di stato della programmazione ISP, per maggiori informazioni leggere la seguente [pagina](https://www.arduino.cc/en/Tutorial/BuiltInExamples/ArduinoISP#load-the-sketch)</br>

------------

**LED Modalita'**</br>

<img src="https://github.com/TheFidax/ProgrammerUpdaterShield/blob/main/images/mode_led.jpg" width="1280"></br>

Questi led forniscono un riscontro visivo sulla Modalita' (I2C o ISP) attualmente in esecuzione nel Firmware.

------------

**I2C Resistori PullUp**

<img src="https://github.com/TheFidax/ProgrammerUpdaterShield/blob/main/images/i2c_pullup.jpg" width="1280"></br>