import socket

# Server UDP socket details
UDP_IP = "127.0.0.1"  # The server's IP address (in this case, it's the loopback address, i.e., localhost)
UDP_PORT = 5005  # The port number the server is listening on

# Create a UDP socket
client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Get login credentials from the user
username = input("Enter username: ")
password = input("Enter password: ")

# Combine the username and password
login_credentials = f"{username}:{password}"

# Send login credentials to the server
client_socket.sendto(login_credentials.encode(), (UDP_IP, UDP_PORT))

# Receive response from the server
response, server_address = client_socket.recvfrom(1024)

# Decode and print the response
print(response.decode())

# Close the socket
client_socket.close()
