import socket

# Create a socket object
s = socket.socket()
print("Socket successfully created")

# Define the port to listen on
port = 8080

# Bind to the port
s.bind(('', port))
print("Socket binded to %s" % port)

# Put the socket into listening mode
s.listen(5)
print("Socket is listening")

# A forever loop until interrupted or an error occurs
while True:
    # Establish connection with the client
    c, addr = s.accept()
    print('Got connection from', addr)

    # Send a thank you message to the client
    c.send('Thank you for connecting'.encode())

    # Close the connection with the client
    c.close()
    break
