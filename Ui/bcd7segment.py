from PyQt6.QtCore import QRect
from PyQt6.QtGui import QColor

#Globals used to draw the 7 segment BCD
startPosX = 15
startPosY = 10
rectangleWidth = 200
rectangleHeight = 20

onColor = QColor(255,0,0)
offColor = QColor(0,0,0)


#Colors for each state
colorsState = {
    '0': [onColor, onColor, onColor, offColor, onColor, onColor, onColor],
    '1': [offColor, offColor, onColor, offColor, offColor, onColor, offColor],
    '2': [onColor, offColor, onColor, onColor, onColor, offColor, onColor],
    '3': [onColor, offColor, onColor, onColor, offColor, onColor, onColor],
    '4': [offColor, onColor, onColor, onColor, offColor,onColor, offColor],
    '5': [onColor, onColor, offColor, onColor, offColor,onColor,onColor],
    '6': [onColor, onColor,offColor, onColor, onColor,onColor,onColor],
    '7': [onColor, offColor, onColor,offColor,offColor,onColor,offColor],
    '8': [onColor, onColor,onColor,onColor,onColor,onColor,onColor],
    '9': [onColor, onColor,onColor, onColor, offColor,onColor,onColor],
    '10': [onColor, onColor, onColor, onColor, onColor, onColor, offColor], #A
    '11': [onColor, onColor, onColor, onColor, onColor, onColor, onColor], #B
    '12': [onColor, onColor, offColor, offColor, onColor,offColor, onColor], #C
    '13': [onColor, onColor, onColor, offColor, onColor, onColor, onColor], #D
    '14': [onColor, onColor, offColor, onColor, onColor, offColor, onColor], #E
    '15': [onColor, onColor, offColor, onColor, onColor, offColor, offColor] #F
}

class BCD7Segment:
    state = -1 #All leds are off
    rectangles = []
    colors = []
    def __init__(self):
        #Initialize the off state of the bcd
        #Draw the up rectangle
        self.rectangles.append(QRect(startPosX + rectangleHeight, startPosY, rectangleWidth, rectangleHeight))
        #Draw the left rectangle
        self.rectangles.append(QRect(startPosX, startPosY + rectangleHeight, rectangleHeight, rectangleWidth))
        #Draw the right rectangle
        self.rectangles.append(QRect(startPosX + rectangleHeight + rectangleWidth, startPosY + rectangleHeight, rectangleHeight, rectangleWidth))
        #Draw the middle rectangle
        self.rectangles.append(QRect(startPosX + rectangleHeight, startPosY + rectangleHeight + rectangleWidth, rectangleWidth, rectangleHeight))
        #Draw the bottom left rectangle
        self.rectangles.append(QRect(startPosX, startPosY + 2 * rectangleHeight + rectangleWidth, rectangleHeight, rectangleWidth))
        #Draw the bottom right rectangle
        self.rectangles.append(QRect(startPosX + rectangleHeight + rectangleWidth, startPosY + 2 * rectangleHeight + rectangleWidth, rectangleHeight, rectangleWidth))
        #Draw the bottom rectangle
        self.rectangles.append(QRect(startPosX + rectangleHeight, startPosY + 2 * rectangleHeight + 2 * rectangleWidth, rectangleWidth, rectangleHeight))
        self.colors = [offColor for i in range(7)]

    def setState(self, state: int):
        if state < 0 or state > 16:
            return
        self.state = state
        self.colors = colorsState[str(self.state)]

    def getState(self):
        return self.state

    def getRectangles(self):
        return self.rectangles

    def getColors(self):
        return self.colors