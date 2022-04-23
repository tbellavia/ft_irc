import socket

def recv(client):
    response = client.recv(512)

    if response.decode() != "":
        print(f"Response: {response}")

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client:
    client.connect(("127.0.0.1", 6697))

    client.send(b"PASS ass\r\n")
    recv(client)
    client.send(b"PONG\r\n")
    recv(client)
