import serial
from datetime import datetime
from serial.tools import list_ports
from os import write
import csv
import time

# Open file
f = open('data.csv', 'w', newline='')

# Clear values inside
f.truncate() 

# Serial arduino port connection
SERIAL_COM = serial.Serial('COM3', 9600, timeout=1) 

# Reset Arduino
SERIAL_COM.setDTR(False)
time.sleep(1)
SERIAL_COM.flushInput()
SERIAL_COM.setDTR(True)

Qtd_Data = 16000

for i in range (Qtd_Data):
    try:
        # Read a line of data
        s_bytes = SERIAL_COM.readline()
        
        # Decode binary
        decoded_bytes = s_bytes('utf-8').strip('\r\n')
        print(decoded_bytes)
        
        # Parse lines
        if i == 0:
            values = [float(x) for x in decoded_bytes.split()]
            print(values)
            
            writer = csv.writer(f, delimiter=",")
            writer.writerow(values)
        
    except:
        print("ERROR. Line was not recorded")
        
f.close()
        
    
    

    

