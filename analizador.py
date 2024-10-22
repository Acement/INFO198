from decouple import config
import matplotlib.pyplot as plt
import numpy as np

print("INICIANDO PLOT")

#Obtiene la variable con los threads
THREADS = config('ARRAY_THREADS')
DATA = config('DATOS')
REPETICIONES = int(config('REPETICIONES'))



tempList = THREADS.rsplit(",")
threadList = []

for i in tempList:
    threadList.append(int(i))
print(threadList)

tempList.clear()

timeList = []
dataList = [] #Formato [[nthread1,rep1,rep2,...],[nthread2,rep1,rep2,...],...,[nthreadN,rep1,rep2,...]]


f = open(DATA,'r')

for i in f:
    timeList.append(float(i.replace("\n","")))

for i in range(0,REPETICIONES):
    tempList.clear()
    for j in range(0,len(threadList)):
        tempList.append(timeList[j+(i*len(threadList))])
    dataList.extend([tempList.copy()])
    

print(dataList)

for i in range (0,len(dataList)):
    plt.plot(threadList,dataList[i],label = "Repeticion " + str(i + 1))

plt.legend()
plt.show()

    

f.close()