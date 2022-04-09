import socket

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client:
    client.connect(("127.0.0.1", 6697))
    client.send(b"JOIN ")
    client.send(b"#channel\r\n")

    client.send(b"JOIN ")
    client.send(b"#discord\r\n")
