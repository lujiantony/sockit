#Chat server used for CSEE 4840 @ Columbia University
#Jian Lu
#Columbia University SEAS'13
#jl3946@columbia.edu
 
import socket, select, struct, fcntl
 
#This function is used to broadcast chat messages to all connected clients
def broadcast_data (sock, message):
    #Do not send the message to master socket and the client who has send us the message
    for socket in CONNECTION_LIST:
        if socket != server_socket and socket != sock :
            try :
                socket.send(message)
		print 1
            except :
                # broken socket connection may be, chat client pressed ctrl+c for example 
		print 2            
		#socket.close()
                #CONNECTION_LIST.remove(socket)

#This function is used to get the ip address the local host
def get_ip_address(ifname):
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    return socket.inet_ntoa(fcntl.ioctl(
        s.fileno(),
        0x8915,  # SIOCGIFADDR
        struct.pack('256s', ifname[:15]))[20:24])
 
if __name__ == "__main__":
     
    # List to keep track of socket descriptors
    CONNECTION_LIST = []
    RECV_BUFFER = 4096 # Advisable to keep it as an exponent of 2
    PORT = 42000
    host = ''; 
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # this has no effect, why ?
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server_socket.bind((host, PORT))
    server_socket.listen(10)
 
    # Add server socket to the list of readable connections
    CONNECTION_LIST.append(server_socket)
    print "This is the first server address appended"
    for item in CONNECTION_LIST:
        print item 
 
    print "CHAT SERVER START ON " + str(get_ip_address('eth0')) + ":" + str(PORT) 
    print "READY TO RECEIVE CONNECTIONS..."
 
    while 1:
        # Get the list sockets which are ready to be read through select
        read_sockets,write_sockets,error_sockets = select.select(CONNECTION_LIST,[],[])
 	
	#print "This is the current readble sockets"
	#print read_sockets
        for sock in read_sockets:
            #New connection
            if sock == server_socket:
                # Handle the case in which there is a new connection recieved through server_socket
                sockfd, addr = server_socket.accept()
                CONNECTION_LIST.append(sockfd)
                print "Server Msg: Client (%s, %s) is online" % addr
                
                sockfd.send("Server Msg: Welcome to CSEE 4840 Lab2!") 
                broadcast_data(sockfd, "Server Msg: Client (%s:%s) is online" % addr)
		print "New member added to connection list "
		for item in CONNECTION_LIST:
        	    print item 
             
            #Some incoming message from a client
            else:
                # Data recieved from client, process it
                try:
                    #In Windows, sometimes when a TCP program closes abruptly,
                    # a "Connection reset by peer" exception will be thrown
                    data = sock.recv(RECV_BUFFER)
		    address = sock.getpeername()
		    
                    if data:
                        broadcast_data(sock, '<' + str(sock.getpeername()) + '> ' + data) 
                        print '<' + str(sock.getpeername()) + '>' + data  
			print "These are the current members of the list"
			for item in CONNECTION_LIST:
        		    print item 
		    elif len(data) == 0:    
			print 4                
                        broadcast_data(sock, "Server Msg: Client (%s, %s) is offline" % address)
                        print "Server Msg: Client (%s, %s) is offline" % address
			sock.close()
			CONNECTION_LIST.remove(sock)  
			print "Member got removed from Connection List"
			for item in CONNECTION_LIST:
              		    print item 

                except:
		    #print 3
                    #broadcast_data(sock, "Server Msg: Client (%s, %s) is offline" % addr)
                    #print "Server Msg: Client (%s, %s) is offline" % addr
                    #sock.close()
                    #CONNECTION_LIST.remove(sock)
                    continue
     
    server_socket.close()
