Add real EEPROM support to DS2433
=================================

In this project, a Maxim EVKIT and software are used to test the functionality of the EEPROM emulation on an Arduino Uno board.

# PC Setup:
This setup is based on
- [QSG from Maxim](https://www.maximintegrated.com/en/design/technical-documents/tutorials/4/4373.html)
- [DS9490 USB-to-1-wire dongle - 5V output](https://www.maximintegrated.com/en/products/interface/universal-serial-bus/DS9490.html)
- [DS9120P Breakout board for DS9490](https://www.maximintegrated.com/en/products/interface/controllers-expanders/DS9120P.html)



### Step 1
Note: **Install drivers BEFORE plugging in DS9490 USB dongle.**
- [Maxim 1-Wire Drivers](https://www.maximintegrated.com/en/products/ibutton-one-wire/one-wire/software-tools/drivers/download-1-wire-ibutton-drivers-for-windows.html)
[Read more here](https://www.maximintegrated.com/en/products/ibutton-one-wire/one-wire/software-tools.html)


1. Connect DS9490 USB dongle to DS9120P breakout board with RJ11 cable.
1. Insert 3-pin TO-92 DS2433 component to J2 socket on DS9210P PCB. 
1. Plug DS9490 USB dongle to PC.
1. Run Default 1-Wire Net.exe from Start Menu.

### Step 2
Confirm Java is installed on the PC or install Java JDK such as [OpenJDK](
https://adoptium.net/?variant=openjdk17&jvmVariant=hotspot)

### Step 3
1. Run OneWireViewer.jar from Start menu.
1. Select DS9490 adaptor and USB1 (or USB2) port. 
1. DS1973 (DS2433) should be discovered and shown in the Device List.
1. Take note of the unique Device 1 Address in the Description Tab.
1. Modify the memory in the device by changing the contents and commit changes.
1. Close the OneWireViewer program. Unplug the USB dongle.
1. Replace the DS2433 part on the DS9120P breakout board.
1. Plug in the USB dongle to the PC. Restart the OneWireViewer program.
1. Confirm that a new DS2433 is discovered with a new unique ID.
   - Device ID is 8 bytes long.
   - LSB (0x23) is the Family ID of DS2433 
   - MSB is the CRC.

# OneWireHub firmware footprint and speed

## Code Usage
### Original code usage
Sketch uses 5346 bytes (16%) of program storage space. Maximum is 32256 bytes.
Global variables use 1023 bytes (49%) of dynamic memory, leaving 1025 bytes for local variables. Maximum is 2048 bytes.

### New code usage with native EEPROM
Sketch uses 5366 bytes (16%) of program storage space. Maximum is 32256 bytes.
Global variables use 481 bytes (23%) of dynamic memory, leaving 1567 bytes for local variables. Maximum is 2048 bytes.

## EEPROM write-time 
- 5ms write-time per page on DS24B33 compared to 
- 114ms per page on ATMega328

Using EEPROMex example to check timing
----------------------------------------------------
Check how much time until EEPROM ready to be accessed
-----------------------------------------------------
Time to write 32 byte array  (ms)                 : 110
Recovery time after writing 32 byte array (ms)    : 4


