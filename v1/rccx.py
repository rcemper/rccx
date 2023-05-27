#!/usr/bin/env  python3.6
# Run Control Command eXecutor v0.0.2
import socket
import os
import subprocess
# rdir="/irisrun/repo/"
rdir="/"
port=6666
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind(("", port))
stop = "" 
sock.listen(1)
try: 
    while True:
#        print("Listening on port: ",port)
        conn, addr = sock.accept()
        while True: 
            data = conn.recv(1024) 
            if not data: 
                conn.close()
                break
            txt = data.decode()
            stop = (txt == "###stop###")
            if stop:
                break              
            rx = (txt[:1] == "$")
            if rx :
                txt=txt[1:]
                stxt=rdir + "rccx '" + txt + "'"
#                stxt=rdir + "rccx '" + txt + "' ; echo '***'"
            else :
               stxt = txt + " ; exit "            
#              stxt = txt + " ; echo '***' ; exit "            
#            print("==>",stxt)

            subprocess.Popen(stxt,shell=True)           

        if stop:
            break

finally: 
    sock.close()
    
exit()
