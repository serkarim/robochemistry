import sys
from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
import socket
host = "localhost"
port = 4210

print("[$] Creating socket...")
client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
print("[$] Socket created successfully!")
class New(QMainWindow):
    def __init__(self):
        super(New, self).__init__()
        loadUi("untitled.ui", self)
        self.setWindowTitle('New')
        self.bottle1.clicked.connect(self.mod1)
        self.pushButton_2.clicked.connect(self.mod2)


    def mod1(self):
        data = "1"
        client_socket.sendto(data.encode(), ((host, port)))
        mess = QMessageBox()
        mess.setText('Вы запустили эксперимент!')
        mess.setDetailedText('Ожидайте начала!')
        mess.setWindowTitle('Внимание!')
        mess.setStandardButtons(QMessageBox.Ok | QMessageBox.Cancel)
        mess.exec_()

    def mod2(self):
        data = "2"
        client_socket.sendto(data.encode(), ((host, port)))
        mess = QMessageBox()
        mess.setText('Вы запустили эксперимент!')
        mess.setDetailedText('Ожидайте начала!')
        mess.setWindowTitle('Внимание!')
        mess.setStandardButtons(QMessageBox.Ok | QMessageBox.Cancel)
        mess.exec_()



    def upClicked(self):
        self.label_4.setText(str(self.counter))
        self.counter += 1

    def exit_action(self):
        self.close()


if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = New()
    window.show()
    sys.exit(app.exec_())