# WifiBadUsb

This project uses an Arduino Leonardo to create a BadUSB. 

A BadUSB is a usb device which impersonates HID (Human Input Device) to inject keystrokes into a system via the USB port.

This Badusb will collect Wifi info such as SSID's and Password's from a Windows machine. 
The collected information is then sent via email to a specificed email address which can be changed in the code.

This project has been designed for demonstration purposes and as such creates the files on the desktop.
This allows demonstration of just how quickly an attacker can deploy this method on an unattended machine to possibly grant a foothold in the larger network.

This Project has been primarily designed for Windows 10, other windows versions such as Vista, 7, 8, and 11 have not been tested.

Code is free to use however you please.
