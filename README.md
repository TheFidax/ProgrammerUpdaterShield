# Programmer & Updater Shield
Questa shield e' pensata per rendere comoda l'aggiornamento dei FirmWare sulle schede di illuminazione.</br>
Mette a disposizione un connettore JST SH6 pre configurato per le schede di illuminazione, un porta ISP 'grande' per dei target generici e vari LED di informazione.</br>
Incorpora resistori di PullUp per il Bus I2C Wire disattivabili tramite interruttore, tale interruttore inoltre permette di scegleiere la modalita' ISP o I2C.</br>
<img src="https://github.com/TheFidax/ProgrammerUpdaterShield/blob/main/images/shield.jpg" width="1280">

------------

# Indice
* [FirmWare](#FirmWare)
* [Metodi Obbligatori](#Metodi-Obbligatori)
* [Metodi Facoltativi](#Metodi-Facoltativi)
* [Metodi Manipolazione CVs](#Metodi-Manipolazione-CVs)
* [Tipi di Dati](#Tipi-di-Dati)
* [Funzionalita' Extra](#Funzionalita-Extra)

------------

# FirmWare
Il Firmware pensato per la shield e' disponibile sotto la cartella [HEX](https://github.com/TheFidax/ProgrammerUpdaterShield/tree/main/HEX)</br>
Il firmware e' gia' pronto per l'upload sulla scheda Arduino tramite [AVRDUDESS](https://blog.zakkemble.net/avrdudess-a-gui-for-avrdude/)</br>
Per caricare il Firmware e' necessario inserire i seguenti parametri nel software:
- **Programmer (-c)** : *Arduino*
- **Port (-P)** : la porta COM a cui e' connessa la scheda Arduino
- **Baud rate (-b)** : 115200
- **Flahs** : il file FIrmWare.hex scaricato
- Infine premere **Programm**