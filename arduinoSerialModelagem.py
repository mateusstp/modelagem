import  serial 
import numpy # carrega a biblioteca numpy
import matplotlib.pyplot as plt #carrega a
                                #biblioteca pyplot
import matplotlib.gridspec as gridspec #carrega a
                                       # biblioteca gridspec
from drawnow import drawnow #carrega a biblioteca
                      # drawnow
from array import array #carrega a biblioteca
                        # array

#instanciacao dos objectos
tempF = array('f')
tempF2 = array('f')
humF1 = array('f')
humF2 = array('f')
lum = array('f')
moist = array('f')
#comunicacao
arduinoData = serial.Serial('/dev/ttyACM0', 9600) #Cria
#arduinoData = serial.Serial('/dev/ttyACM1', 9600) #Cria
# um objecto do tipo serial chamado
# arduinoData
#while True:
  # leemos hasta que encontarmos el final de linea
#  arduinoString = arduinoData.readline()
  # Mostramos el valor leido y eliminamos el salto de linea del final
#  print "Valor Arduino: " + arduinoString.rstrip('\n')
plt.ion()
cnt=0

def makeFig():
 gs = gridspec.GridSpec(3, 3) #gridspec 3x3
 #Plot 1
 plt.ylim([0,30])#valor min e max de y
 plt.xlim([0,350])#valor min e max de y
 plt.title('Nivel do tanque em funcao de degrau de tensao')#titulo
 plt.grid(True)
 plt.ylabel('Nivel ( cm )')#etiquetas do eixo y
 plt.xlabel('Amostras ( 10/ seg )')#etiquetas do eixo y
 plt.plot(tempF, 'r', label='Nivel tanque') #plot de temperature
 plt.legend(loc='upper left')#plot da legenda
 plt2=plt.twinx()#cria um Segundo eixo y
 plt2.plot(tempF2, 'b', label='Degrau de tensao')
 # desenha os val. De tempF2
 plt2.set_ylabel('Tensao ( V )') #Etiqueta do
 # Segundo eixo
 plt2.ticklabel_format(useOffset=False)# impede
 # a escala do eixo X
 plt2.legend(loc='upper right')

#mainProgram

while True:
 amostras=0
 while (amostras <100):
   while (arduinoData.inWaiting()==0):
     pass
   arduinoString = arduinoData.readline()
   #varfile = open("vazaoEntrada86EXP3.txt","a")
   varfile = open("estabilizar86.txt","a")
   varfile.write(arduinoString)
   varfile.close()
   splitedArray = [float(s) for s in arduinoString.split(';')]
   temp = splitedArray[0]
   temp2 = splitedArray[4]
   tempF.append(temp)
   tempF2.append(temp2)
   amostras= amostras+1
  
 drawnow(makeFig)
 plt.pause(.0005)
 cnt=cnt+1
 if(cnt>1000):
   tempF.pop(0)
   tempF2.pop(0)