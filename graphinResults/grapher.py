import matplotlib.pyplot as plt
log = open("canlog.txt", "r")
log = log.read()
log = log.split("T", 2)
log[1].replace("----------------------------------------------", "")
log = log[2].rsplit("-", 2)[0]
log = log.rsplit("m", 1)[0]
log = log.split(",")
index = 0
for i in log:
    i = i.replace("emperature =  ", "")
    i = i.replace("T", "")
    i = i.replace("C", "")
    i = i.replace("m", "")
    i = i.replace("\n", "")
    i = i.replace("Pressure =  ", "")
    i = i.replace("Altitude =  ", "")
    i = i.replace(" ", "")
    log[index] = float(i)
    index += 1

temps = []
alti = []
pressure = []
index2 = 0
for i in range(0, len(log), 3):
    temps.append(log[i])
    pressure.append(log[i+1])
    alti.append(log[i+2])
plt.title("Cansat Pressure")
plt.xlabel("time(sec)")
plt.ylabel("pressure(millibars)")
plt.plot(pressure)
plt.show()
