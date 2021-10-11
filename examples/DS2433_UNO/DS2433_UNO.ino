/*
*  Maxim DS2433 Emulation with Arduino Uno using OneWire-Hub
*/

#include <EEPROMex.h>
#include "OneWireHub.h"
#include "DS2433.h"

//#define _DEBUG

constexpr uint8_t pin_onewire   { 8 };

auto hub = OneWireHub(pin_onewire);
auto ds2433 = DS2433(DS2433::family_code, 0x00, 0x00, 0x33, 0x24, 0x00, 0x00);

void setup()
{
#ifdef _DEBUG
    Serial.begin(115200);
    Serial.println("Maxim DS2433 Emulation with Arduino Uno using OneWire-Hub");

    constexpr uint8_t mem_write[] = {
        0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
        0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF,
        0xDE, 0xAD, 0xBE, 0xEF, 0xCA, 0xFE, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0xFA, 0xCE, 0x00, 0xFF
    };

    Serial.print("Test Write page 0");

    int16_t startMillis = millis();
    int16_t endMillis;
    ds2433.writeMemory(mem_write, sizeof(mem_write), 0); // page 0
    endMillis = millis(); 
    Serial.print("Time to write 32 byte (1 page) (ms): ");    
    Serial.println(endMillis-startMillis); 

    Serial.println("Test Read page 2");

    uint8_t mem_read[32];
    startMillis = millis();
    ds2433.readMemory(mem_read, sizeof(mem_read), 2*32); // page 2
    endMillis = millis(); 
    Serial.print("Time to read 32 byte (1 page) (ms): ");    
    Serial.println(endMillis-startMillis); 

    for (uint8_t i = 0; i < 32; ++i)
    {
        Serial.print(mem_read[i],HEX); 
        i % 16 == 15 ?  Serial.println() : Serial.print(" ");
    }

    Serial.println("config done");
#endif

    // Setup OneWire
    hub.attach(ds2433);
}

void loop()
{
    // following function must be called periodically
    hub.poll();
} 
