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

#ifdef _DEBUG
void printOnePage(uint8_t* mem)
{
    for (uint8_t i = 0; i < 32; ++i)
    {
        Serial.print(mem[i],HEX);
        i % 16 == 15 ?  Serial.println() : Serial.print(" ");
    }
}

void readPage(uint8_t* mem, uint8_t pagenum)
{
    ds2433.readMemory(mem, 32, pagenum*32);
    printOnePage(mem);
}

void writePage(uint8_t *mem, uint8_t pagenum)
{
    int16_t startMillis = millis();
    int16_t endMillis;

    ds2433.writeMemory(mem, 32, pagenum*32);
    endMillis = millis();
    Serial.print("Time to write (ms): ");
    Serial.println(endMillis-startMillis);
}
#endif


void setup()
{
    EEPROM.setMaxAllowedWrites(1000);

#ifdef _DEBUG
    Serial.begin(115200);
    Serial.println("Maxim DS2433 Emulation with Arduino Uno using OneWire-Hub");

    uint8_t pagemem[32] = {
        0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
        0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF,
        0xDE, 0xAD, 0xBE, 0xEF, 0xCA, 0xFE, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0xFA, 0xCE, 0x00, 0xFF
    };

    Serial.println("Test Read page 2");
    readPage(pagemem, 2);

    Serial.println("Test Write page 2 without changes");
    writePage(pagemem, 2);
    readPage(pagemem, 2);

    *reinterpret_cast<float *>(&pagemem[0]) = 100.0; // set a value
    *reinterpret_cast<uint16_t *>(&pagemem[4]) = 1234; // set a value

    Serial.println("Test Write page 2 with initial values");
    writePage(pagemem, 2);
    readPage(pagemem, 2);

    // Update 1 word (2 bytes)
    Serial.println("Test Write page 2 with 1 word changed");
    *reinterpret_cast<uint16_t *>(&pagemem[4]) += 1; // modify a ushort
    writePage(pagemem, 2);
    readPage(pagemem, 2);

    // update 1 float (4 bytes)
    Serial.println("Test Write page 2 with 1 float changed");
    *reinterpret_cast<float *>(&pagemem[0]) += 1.0; // modify a float
    writePage(pagemem, 2);
    readPage(pagemem, 2);

    Serial.println("Testing done");
#endif

    // Setup OneWire
    hub.attach(ds2433);
}


void loop()
{
    // following function must be called periodically
    hub.poll();
} 
