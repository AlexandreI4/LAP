import serial # import Serial Library
import numpy  # Import numpy
import matplotlib.pyplot as plt #import matplotlib library
from drawnow import *
from time import gmtime, strftime

tempF= []
pressure=[]
tempsN = []
arduinoData = serial.Serial('com6', 115200) #Creating our serial object named arduinoData
plt.ion() #Tell matplotlib you want interactive mode to plot live data
cnt=0

def makeFig(): #Create a function that makes our desired plot
    plt.ylim(0,100)                                 #Set y min and max values
    plt.title('Suivi en temps réel LAP-TEAM')      #Plot the title
    plt.grid(True)                                  #Turn the grid on
    plt.ylabel('Temperature (°C)')                     #Set ylabels
    plt.xlabel('Temps (s)')                         #set xlabel
    plt.plot(tempsN,tempF, 'r', label='Degres C')       #plot the temperature modifier 'r' pour points
    plt.legend(loc='lower left')                    #plot the legend
    plt2=plt.twinx()                                #Create a second y axis
    plt.ylim(0,2000)                           #Set limits of second y axis- adjust to readings you are getting
    plt2.plot(tempsN, pressure, 'b', label='Luminosité') #plot pressure data modifier 'b' pour points
    plt2.set_ylabel('Luminosité (b)')                    #label second y axis
    plt2.ticklabel_format(useOffset=True)           #Force matplotlib to NOT autoscale y axis
    plt2.legend(loc='lower right')                  #plot the legend
    
def faireTime():
    liste = []
    temps = (strftime('%H:%M:%S', gmtime()))
    liste = temps.split(':')
    tpS = int(liste[0])*3600 + int(liste[1])*60 + int(liste[2])
    return(tpS)

tempsN = []    
while True: # While loop that loops forever
    while (arduinoData.inWaiting()==0): #Wait here until there is data
        pass #do nothing
    arduinoString = arduinoData.readline() #read the line of text from the serial port
    arduinoString = arduinoString.decode('UTF-8')
    #print(arduinoString)
    dataArray = arduinoString.split(',')   #Split it into an array called dataArray
    temp = float( dataArray[0])            #Convert first element to floating number and put in temp
    P =    float( dataArray[1])             #Convert second element to floating number and put in P
    tempsN.append(faireTime())
    tempF.append(temp)                     #Build our tempF array by appending temp readings
    pressure.append(P)                     #Building our pressure array by appending P readings
    drawnow(makeFig)                       #Call drawnow to update our live graph
    plt.pause(.000001)                     #Pause Briefly. Important to keep drawnow from crashing
    cnt=cnt+1
    if(cnt>50):                            #If you have 50 or more points, delete the first one from the array
        tempF.pop(0)                       #This allows us to just see the last 50 data points
        pressure.pop(0)
        tempsN.pop(0)
