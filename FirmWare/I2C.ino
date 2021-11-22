#include <Wire.h>
#include <WireSusi.h>

/*
*   FORMATO MESSAGGIO SERIALE:
*   <c arg1 arg2 arg3>
*     c :   comando
*     arg1: argomento 1
*     arg2: ...
*     arg3: ...
*     arg4: ...
*   
*   LA RISPOSTA HA IL SEGUENTE FORMATO
*   <c arg1 arg2 arg3 esito>
*     c :   comando
*     arg1: argomento 1
*     arg2: ...
*     arg3: ...
*     arg4: ...
*     esito: 1 se l'operazione e' riuscita, -1 altrimenti
 */

#define MAX_COMMAND_LENGTH  20                                                        // Lunghezza massima del comando ricevuto via Seriale

struct SerialCommands{
    char command;
    int args[3];
};

/*  Variabili Globali */
uint8_t WireToUartBridge = true;                                                     // Identifica se e' attiva la modalita' di Bridge Wire to Serial (de Default NO : falso)

/*  Prototipi   */
int8_t  readCommand(struct SerialCommands *data);                                     // Funzione che legge i comandi ricevuti tramite Seriale
int8_t  parseCommand(struct SerialCommands *data);                                    // Decodifica il comando ricevuto
void    sendAnswer(char command, int arg1, int arg2, int arg3, int esito);            // Risponde restituendo una copia del comando e l'esito dell'Operazione

void WireToUartBridge_Handle(int nBytes) {                                            // Handle invocato quando il dispositivo diventa Slave Wire
    Serial.println(nBytes);
    if(WireToUartBridge) {                                                            // Se la Modalita' Bridge e' attiva
        while(Wire.available()) {                                                     // Se ci sono dei Byte nel Buffer Wire
            Serial.print(Wire.read());                                                // Li scrivo sulla Seriale
        }
    } 
}

void setup_ArduinoI2C() {
    Serial.begin(500000);                                                             // Avvio comunicazione Seriale con Baud: 500k
    while(!Serial) {}                                                                 // Attendo che la comunicazione sia stabilita

    Wire.begin(0x00);                                                                 // Avvio il Bus I2c con indirizzo 0
    Wire.setClock(400000);                                                            // Imposto la frequenza del Bus I2c a 400kHz
    Wire.setWireTimeout(1000, true);                                                  // Imposto un Timeout preventivo, se il bus I2c si blocca, evito il blocco dell'intero codice
    Wire.onReceive(WireToUartBridge_Handle);                                          // Handle per la ricezione di dati Wire quando il programmatore e' slave
}

void loop_ArduinoI2C() {
    struct SerialCommands commandData;                                                // Struct in cui vengono salvati i comandi ricevuti
    
    while(1) {                                                                        // Ciclo infinito
        heartbeat();                                                                  // Riscontro visivo del corretto funzionamento

        if(Serial.available()) {                                                      // Se e' disponibile un dato sulla Seriale
            if(readCommand(&commandData) == 0) {                                      // Provo ad acquisirlo come comando
                parseCommand(&commandData);                                           // Interpreto il comando
            }            
        }
    }
}

int8_t readCommand(struct SerialCommands *data) {
    String serialCommand;                                                             // Stringa in cui vengono salvati i messaggi ricevuti via Seriale
    char buffer[MAX_COMMAND_LENGTH];                                                  // Buffer per manipolazione comando

    serialCommand = Serial.readStringUntil('>');                                      // Leggo fino al terminatore
    serialCommand.toCharArray(buffer, MAX_COMMAND_LENGTH);                            // Converto la Stringa in un tipo semplice

    if(buffer[0] == '<') {                                                            // Controllo che il comando inizi con il carattere corretto
        sscanf(buffer, "<%c %d %d %d>", &data->command, &data->args[0], &data->args[1], &data->args[2]);       // Acquisisco il comando
        return 0;                                                                     // Restituisco il valore di corretta operazione
    }
    else {                                                                            // In caso di carattere iniziale sbagliato
        return -1;                                                                    // Restituisco errore
    }
}

int8_t parseCommand(struct SerialCommands *data) {
    switch(data->command) {
        case 'v': {                                                                   // Richiesta versione FirmWare
            sendAnswer(data->command, FIRMWARE_VERSION_HIGH_VALUE, FIRMWARE_VERSION_LOW_VALUE, 0, 1);
            break;
        }
        case 's': {                                                                   // Ricerca il dispositivo con Indirizzo specificato 
            uint8_t error;
            Wire.beginTransmission(data->args[0]);
            error = Wire.endTransmission();
            if(error == 0) {                                                          // Dispositivo trovato! 
                sendAnswer(data->command, data->args[0], 0, 0, 1);                    // Restituisco risposta Affermativa
            }
            else {                                                                    // Dispositivo non trovato!
                sendAnswer(data->command, data->args[0], 0, 0, -1);                   // Restituisco risposta Negativa
            }
            break;
        }
        case 'C': {                                                                   // Invio comando SusiOverI2c
            int8_t error = sendCommandWireSusi(data->args[0], data->args[1], data->args[2]);    // Invio il comando
            sendAnswer(data->command, data->args[0], data->args[1], data->args[2], error);      // Rispondo se l'invio del comando e' avvenuta con successo o meno
            break;
        }
        case 'R': {                                                                   // Richiesta Lettura CVs
            int16_t Value = readCVsWireSusi(data->args[0], data->args[1]);            // Leggo la CV
            if(Value != -1) {                                                         // Controllo che la comunicazione sia andata a Buon fine
                sendAnswer(data->command, data->args[0], data->args[1], Value, 1);    // Invio il dato Letto come risposta
            }
            else {                                                                    // Se ci sono stati problemi
                sendAnswer(data->command, data->args[0], data->args[1], -1, -1);      // Invio -1 come esisto operazione
            }
            break;
        }
        case 'W': {                                                                   // Richiesta Scrittura CVs
            int16_t Value = writeCVsWireSusi(data->args[0], data->args[1], data->args[2]);      // Scrivo la CV
            if(Value != -1) {                                                         // Controllo che la comunicazione sia andata a Buon fine
                sendAnswer(data->command, data->args[0], data->args[1], Value, 1);    // Invio il dato Letto come risposta
            }
            else {                                                                    // Se ci sono stati problemi
                sendAnswer(data->command, data->args[0], data->args[1], -1, -1);      // Invio -1 come esisto operazione
            }
            break;
        }
        case 'b': {                                                                   // 'Trasparenza' : riporto sulla Seriale ciò che leggo sul bus Wire
            ((data->args[0]) ? WireToUartBridge = 1 : WireToUartBridge = 0);          // Imposto la 'trasparenza'
            sendAnswer(data->command, data->args[0], WireToUartBridge, 0, 1);         // Rispondo riportando lo stato del WireToUart bridge
            break;
        }
        default: {                                                                    // Comando ricevuto NON valido
            sendAnswer(data->command, -1, -1, -1, -1);                                // Informo del Comando non valido
            return -1;                                                                // Restituisco errore
        }
    }

    return 0;
}

void sendAnswer(char command, int arg1, int arg2, int arg3, int esito) {
    char buffer[MAX_COMMAND_LENGTH + 5];                                              // Buffer per manipolazione risposta

    sprintf(buffer, "<%c %d %d %d %d>", command, arg1, arg2, arg3, esito);            // Imposto la risposta
    
    Serial.print(buffer);                                                             // La invio tramite Seriale
}
