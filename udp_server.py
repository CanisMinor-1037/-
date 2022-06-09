from scapy.all import *
import socket

IP = "192.168.31.1"
PORT = 9090

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((IP, PORT))

while True:
    data, (ip, port) = sock.recvfrom(1024)
    print("Data: ", data)
    print("IP: {}, Port: {}".format(ip, port))