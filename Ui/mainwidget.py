from PyQt6.QtWidgets import QWidget, QApplication, QPushButton
from PyQt6.QtGui import QPainter, QColor
from bcd7segment import BCD7Segment
from threading import Thread
import sys
import serial

class MainWidget(QWidget):
    bcd = 0
    serConnection = 0
    reverse = 0
    def __init__(self):
        super().__init__()
        self.bcd = BCD7Segment()
        self.reverse = 0
        #self.bcd.setState(2)
        self.initSerialConnection()
        self.initUI()

    def initSerialConnection(self):
        self.ser = serial.Serial('COM9', baudrate=115200, timeout=1)
        if self.ser.is_open:
            print("Connected to serial")
        #self.ser.open()
        #Start a thread to listen for messages on serial communication
        self.t = Thread(target=self.pollSerial, args=(self.ser,))
        self.t.start()

    def pollSerial(self, connection: serial.Serial):
        #Wait for a message to come on serial communication
        while(True):
            byte = connection.read()
            if byte != b'':
                print(f'Received: {byte}')
                self.bcd.setState(ord(byte))
                self.update()

    def initUI(self):
        #Initialize the window
        self.setGeometry(300, 300, 800, 800)
        #Set the window title
        self.setWindowTitle('Microprocesoare')
        #Add the button
        self.button = QPushButton(self)
        self.button.setText("Reverse order")
        self.button.move(300, 20)
        #Add the handler for button clicked
        self.button.clicked.connect(self.reverse_button_clicked)
        #Add increment button
        self.button_increment = QPushButton(self)
        self.button_increment.setText("Increment")
        self.button_increment.move(300, 100)
        #Add the clicked function
        self.button_increment.clicked.connect(self.increment_button_clicked)
        #Add decrement button
        self.button_decrement = QPushButton(self)
        self.button_decrement.setText("Decrement")
        self.button_decrement.move(300, 200)
        #Add the clicked function
        self.button_decrement.clicked.connect(self.decrement_button_clicked)
        self.show()

    def reverse_button_clicked(self):
        #Reverse the order of counting
        if self.reverse == 0:
            self.ser.write(b'd')
            self.reverse = 1
        else:
            self.ser.write(b'a')
            self.reverse = 0
        print(f'Reverse = {self.reverse}')

    def decrement_button_clicked(self):
        self.ser.write(b's')
        print("Clicked button to decrement")
        newState = self.bcd.getState() - 1
        if newState < 0:
            newState = 15
        self.bcd.setState(newState)
        self.update()

    def increment_button_clicked(self):
        self.ser.write(b'w')
        print("Clicked button to increment")
        #Update internal state
        newState = (self.bcd.getState() + 1) % 16
        self.bcd.setState(newState)
        self.update()


    def paintEvent(self, e):
        qp = QPainter()
        qp.begin(self)
        self.drawBCD(qp)
        qp.end()

    def drawBCD(self, qp: QPainter):
        rects = self.bcd.getRectangles()
        colors = self.bcd.getColors()
        col = QColor(0,0,0)
        qp.setPen(col)
        for i in range(len(rects)):
            qp.setBrush(colors[i])
            qp.drawRect(rects[i])
        
