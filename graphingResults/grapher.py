#import you graphing library
import matplotlib.pyplot as plt
#open you log file (saved as .txt)
log = open("canlog.txt", "r")
#read the contents of you log file
log = log.read()
#removes everything before the first T in tempurate (removes T aswell)
log = log.split("T", 2)
log[1].replace("----------------------------------------------", "")
log = log[2].rsplit("-", 2)[0]
log = log.rsplit("m", 1)[0]
log = log.split(",")
#index = time in seconds
index = 0
for i in log:
    #remove all unessary characters
    i = i.replace("emperature =  ", "")
    i = i.replace("T", "")
    i = i.replace("C", "")
    i = i.replace("m", "")
    i = i.replace("\n", "")
    i = i.replace("Pressure =  ", "")
    i = i.replace("Altitude =  ", "")
    i = i.replace(" ", "")
    #change all numbers to floats
    log[index] = float(i)
    #increase time
    index += 1
#declare all different values lists
temps = []
alti = []
pressure = []
index2 = 0
#split all numbers into their respective lists
for i in range(0, len(log), 3):
    temps.append(log[i])
    pressure.append(log[i+1])
    alti.append(log[i+2])
#very important to add all of your labels
plt.title("Cansat Pressure")
plt.xlabel("time(sec)")
plt.ylabel("pressure(millibars)")
#plot your desired values
plt.plot(pressure)
plt.show()
