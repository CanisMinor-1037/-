from tabnanny import verbose
from scapy.all import *

ip = IP(src="192.168.31.141", dst="192.168.31.137")
data = b'Ping Pong Game'
udp = UDP(sport=9090, dport=9090)

pkt = ip/udp/data
send(pkt, verbose=0)
