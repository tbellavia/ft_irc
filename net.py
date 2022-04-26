import socket

def recv(client):
    response = client.recv(512)

    if response.decode() != "":
        print(f"Response: {response}")

def ston(s):
    return f"{s}\r\n".encode()

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client:
    client.connect(("127.0.0.1", 6697))

    client.send(b"PASS pass\r\n")
    client.send(b"PASS pass\r\n")
    recv(client)

