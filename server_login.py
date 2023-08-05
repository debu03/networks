import socket

# Server UDP socket details
UDP_IP = "127.0.0.1"
UDP_PORT = 5005

# Create a UDP socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Bind the socket to the IP address and port
server_socket.bind((UDP_IP, UDP_PORT))

print("Server is ready to receive login credentials...")

# Receive data from the client
data, address = server_socket.recvfrom(1024)

# Decode the received data
login_credentials = data.decode()

# Check if the login credentials are valid
if login_credentials == "username:password":
    response = "Login credentials matched"
else:
    response = "Invalid login credentials"

# Send the response back to the client
server_socket.sendto(response.encode(), address)

# Close the socket
server_socket.close()
