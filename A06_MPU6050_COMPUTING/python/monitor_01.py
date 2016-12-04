from PyQt4 import QtGui, QtCore  # (the example applies equally well to PySide)
import pyqtgraph as pg
import numpy as np
import serial
import threading

app = QtGui.QApplication([])
win = QtGui.QWidget()
win.setWindowTitle("MPU6050 Data Monitor")

## Create some widgets to be placed inside
lblAccel = QtGui.QLabel("=== ACCELEROMETER DATA ===")
lblGyro = QtGui.QLabel("=== GYRO DATA ===")
lblAccel.setAlignment(QtCore.Qt.AlignCenter)
lblGyro.setAlignment(QtCore.Qt.AlignCenter)
btnStart = QtGui.QPushButton('CONNECT COM PORT')
btnStop = QtGui.QPushButton('DISCONNECT')
text = QtGui.QLineEdit('enter comport name')
accelX = pg.PlotWidget()
accelY = pg.PlotWidget()
accelZ = pg.PlotWidget()
gyroX = pg.PlotWidget()
gyroY = pg.PlotWidget()
gyroZ = pg.PlotWidget()

## Create a grid layout to manage the widgets size and position
layout = QtGui.QGridLayout()
win.setLayout(layout)

## Add widgets to the layout in their proper positions
layout.addWidget(lblAccel, 0, 0)
layout.addWidget(lblGyro, 0, 1)
layout.addWidget(accelX, 1, 0)
layout.addWidget(gyroX, 1, 1)
layout.addWidget(accelY, 2, 0)
layout.addWidget(gyroY, 2, 1)
layout.addWidget(accelZ, 3, 0)
layout.addWidget(gyroZ, 3, 1)
layout.addWidget(text, 4, 0, 1, 0)
layout.addWidget(btnStart, 5, 0)
layout.addWidget(btnStop, 5, 1)

graphRange = 300
######################################################################################
# DRAW Accel X
accelX.setDownsampling(mode='peak')
accelX.setClipToView(True)
accelX.setRange(xRange=[-graphRange, 0])
accelX.setLimits(xMax=0)
curveAccelX = accelX.plot(pen=(255, 0, 0))
dataAccelX = np.empty(graphRange)
dataPoint = 0
def updateAccelX(data):
    global dataAccelX, dataPoint
    dataAccelX[dataPoint] = data
    dataPoint += 1
    if dataPoint >= dataAccelX.shape[0]:
        tmp = dataAccelX
        dataAccelX = np.empty(dataAccelX.shape[0] * 2)
        dataAccelX[:tmp.shape[0]] = tmp
    curveAccelX.setData(dataAccelX[:dataPoint])
    curveAccelX.setPos(-dataPoint, 0)

######################################################################################
# DRAW Accel Y
accelY.setDownsampling(mode='peak')
accelY.setClipToView(True)
accelY.setRange(xRange=[-graphRange, 0])
accelY.setLimits(xMax=0)
curveAccelY = accelY.plot(pen=(0, 0, 255))
dataAccelY = np.empty(graphRange)
def updateAccelY(data):
    global dataAccelY, dataPoint
    dataAccelY[dataPoint-1] = data
    if dataPoint >= dataAccelY.shape[0]:
        tmp = dataAccelY
        dataAccelY = np.empty(dataAccelY.shape[0] * 2)
        dataAccelY[:tmp.shape[0]] = tmp
    curveAccelY.setData(dataAccelY[:dataPoint])
    curveAccelY.setPos(-dataPoint, 0)

######################################################################################
# DRAW Accel Z
accelZ.setDownsampling(mode='peak')
accelZ.setClipToView(True)
accelZ.setRange(xRange=[-graphRange, 0])
accelZ.setLimits(xMax=0)
curveAccelZ = accelZ.plot()
dataAccelZ = np.empty(graphRange)
def updateAccelZ(data):
    global dataAccelZ, dataPoint
    dataAccelZ[dataPoint-1] = data
    if dataPoint >= dataAccelZ.shape[0]:
        tmp = dataAccelZ
        dataAccelZ = np.empty(dataAccelZ.shape[0] * 2)
        dataAccelZ[:tmp.shape[0]] = tmp
    curveAccelZ.setData(dataAccelZ[:dataPoint])
    curveAccelZ.setPos(-dataPoint, 0)

######################################################################################
# DRAW Gyro Z
gyroX.setDownsampling(mode='peak')
gyroX.setClipToView(True)
gyroX.setRange(xRange=[-graphRange, 0])
gyroX.setLimits(xMax=0)
curveGyroX = gyroX.plot(pen=(255, 0, 0))
dataGyroX = np.empty(graphRange)
def updateGyroX(data):
    global dataGyroX, dataPoint
    dataGyroX[dataPoint-1] = data
    if dataPoint >= dataGyroX.shape[0]:
        tmp = dataGyroX
        dataGyroX = np.empty(dataGyroX.shape[0] * 2)
        dataGyroX[:tmp.shape[0]] = tmp
    curveGyroX.setData(dataGyroX[:dataPoint])
    curveGyroX.setPos(-dataPoint, 0)

######################################################################################
# DRAW Gyro Y
gyroY.setDownsampling(mode='peak')
gyroY.setClipToView(True)
gyroY.setRange(xRange=[-graphRange, 0])
gyroY.setLimits(xMax=0)
curveGyroY = gyroY.plot(pen=(0, 0, 255))
dataGyroY = np.empty(graphRange)
def updateGyroY(data):
    global dataGyroY, dataPoint
    dataGyroY[dataPoint-1] = data
    if dataPoint >= dataGyroY.shape[0]:
        tmp = dataGyroY
        dataGyroY = np.empty(dataGyroY.shape[0] * 2)
        dataGyroY[:tmp.shape[0]] = tmp
    curveGyroY.setData(dataGyroY[:dataPoint])
    curveGyroY.setPos(-dataPoint, 0)

######################################################################################
# DRAW Gyro Y
gyroZ.setDownsampling(mode='peak')
gyroZ.setClipToView(True)
gyroZ.setRange(xRange=[-graphRange, 0])
gyroZ.setLimits(xMax=0)
curveGyroZ = gyroZ.plot()
dataGyroZ = np.empty(graphRange)
def updateGyroZ(data):
    global dataGyroZ, dataPoint
    dataGyroZ[dataPoint-1] = data
    if dataPoint >= dataGyroZ.shape[0]:
        tmp = dataGyroZ
        dataGyroZ = np.empty(dataGyroZ.shape[0] * 2)
        dataGyroZ[:tmp.shape[0]] = tmp
    curveGyroZ.setData(dataGyroZ[:dataPoint])
    curveGyroZ.setPos(-dataPoint, 0)

arduino = serial.Serial(port="com3", baudrate=230400, timeout=1, xonxoff=False)

arduino.close()
def update():
    if arduino.readable():
        data = arduino.readline().split(",")
        if (len(data) >= 3):
            updateAccelX(data[0])
            updateAccelY(data[1])
            updateAccelZ(data[2])
        if (len(data) >= 6):
            updateGyroX(data[3])
            updateGyroY(data[4])
            updateGyroZ(data[5])

def start():
    if arduino.isOpen() == False:
        arduino.open()
    timer.start(10)

def stop():
    if arduino.isOpen() == True:
        arduino.close()
    timer.stop()

btnStart.clicked.connect(start)
btnStop.clicked.connect(stop)
timer = pg.QtCore.QTimer()
timer.timeout.connect(update)

## Display the widget as a new window
win.show()

## Start the Qt event loop
app.exec_()