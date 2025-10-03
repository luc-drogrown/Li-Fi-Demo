# Li-Fi-Demo

This is a project made to showcase the transmission of data using visible light as a carrier medium.
It consists of two Ardino boards, a Mega 2560 and a Uno, communicating through an LED and a photoresistor.

The Mega 2560 board takes the information inputed from the serial monitor by the user in the form on strings. Then the strings are split into characters, a '0' and a '1' bit are added in front of each character for synchronization of the receiver board. The bits are also used to signal the beginning of the data transmission.

The Uno board reads the values from a photoresistor placed in a resistor divider assembly. The code constantly watches for the consecutive "0", "1" bits signaling the beginning of transmission. As bits get transmitted the code composes the characters and displayes them on a OLED display.

Both board have a calibration function in which the Mega transmits a set number of bits as the set period and the Uno adjusts the voltage threshold and the period for the recognition of the bits. The Mega requires the user to type calibration for the function to start and the Uno has a button for that.

Some issues that I encountered were with the rejection of backround light radiation, making the threshold between '0' and '1' variable. Also a drawback of the transmission of data using visible light is that the transmitter and the receiver need to be close and alligned in order for correct data transmission.

REFERENCES:
https://www.ted.com/talks/harald_haas_wireless_data_from_every_light_bulb 

https://iopscience.iop.org/article/10.1088/1757-899X/872/1/012010/pdf 

https://www.digitaltrends.com/mobile/light-bulb-li-fi-wireless-internet/ 

https://www.newscientist.com/article/mg21128225-400-will-li-fi-be-the-new-wi-fi/ 

https://projecthub.arduino.cc/saadsaif0333/data-transfer-using-led-light-li-fi-ee33a3 
