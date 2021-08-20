#include <Wire.h>

void setup_ArduinoI2C() {
    Serial.begin(115200);

    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);

    Wire.begin(0x02);
    Wire.setClock(400000);
}

static void loop_ArduinoI2C() {
    heartbeat();
}

uint8_t Wire_readBytes(uint8_t *buffer, uint8_t size) {
    uint8_t i;

    for (i = 0; i < size; i++) {
        *buffer++ = Wire.read();
    }

    return i;
}

void receiveEvent(int bytes) {
    uint8_t Buffer[32];

    Wire_readBytes((uint8_t*)&Buffer, bytes);

    for(uint8_t i = 0; i < bytes; ++i) {
        Serial.print((char)Buffer[i]);
    }
}

void requestEvent(void) {

}
