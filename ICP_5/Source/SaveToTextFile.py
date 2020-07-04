## import the serial library
import serial

## Boolean variable that will represent
## whether or not the arduino is connected
connected = False

## establish connection to the serial port that your arduino
## is connected to.

locations=['/dev/ttyUSB0','/dev/ttyUSB1','/dev/ttyUSB2','/dev/ttyUSB3']


ser = serial.Serial("COM5", 9600)


## loop until the arduino tells us it is ready
while not connected:
    serin = ser.read()
    connected = True

## open text file to store the current
##gps co-ordinates received from the rover
text_file = open("distance_data.txt", 'w')
## read serial data from arduino and
## write it to the text file 'position.txt'
while 1:
    if ser.inWaiting():
        x=ser.readline()
        x = str(x).replace('b','')
        x=x.replace('\r\n','')
        print(x)
        text_file.write(x+"\n")

        text_file.flush()

## close the serial connection and text file
# text_file.close()
# ser.close()