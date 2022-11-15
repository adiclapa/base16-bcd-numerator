import sys
from mainwidget import MainWidget
from PyQt6.QtWidgets import QWidget, QApplication

def main():
    app = QApplication(sys.argv)
    ex = MainWidget()
    sys.exit(app.exec())

if __name__ == '__main__':
    main()