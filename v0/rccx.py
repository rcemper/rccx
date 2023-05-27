#!/usr/bin/env  python3.6
# Run Control Command eXecutor
import socket
import os
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind(("", 6666))
stop = "" 
sock.listen(1)
try: 
    while True: 
        conn, addr = sock.accept()
        while True: 
            data = conn.recv(1024) 
            if not data: 
                conn.close()
                break
            txt = data.decode()
            print(txt)
            os.system(txt)
            stop = (txt == "###stop###")
        if stop:
            break

finally: 
    sock.close()
    
exit()
