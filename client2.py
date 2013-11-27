#! /user/bin/env python

import socket

host = '128.59.17.215'
port = 2048
size = 1024

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((host,port))
while 1:
	s.send('Hello, world too')
	data = s.recv(size)
	#s.close()
	print 'Received:', data
