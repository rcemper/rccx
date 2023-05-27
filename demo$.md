#### first we login into IRIS and do ^zrccx   
~~~
C:\GitHub\zrccx>docker-compose exec iris iris session iris -U "%SYS"  
Node: 32842aedd3c5, Instance: IRIS   
%SYS>   
%SYS>do ^zrccx   
start Run Container Command eXecution   
server = localhost,  port = 6666  
Enter bash command [?=dump logfile, .=exit, ***=stop executor & exit]
??> :   
~~~
#### next we run some listing and check the log   
~~~
??> :    
??> :ls -la /   
??> :??
$>#
$>total 1576$>drwxr-xr-x   1 root      root         4096 May  9 11:01 .
$>drwxr-xr-x   1 root      root         4096 May  9 11:01 ..
$>-rwxr-xr-x   1 root      root            0 May  9 11:01 .dockerenv
$>drwxr-xr-x   5 irisowner irisowner    4096 Oct 22  2020 LIC
$>drwxr-xr-x   1 root      root         4096 Feb  3  2020 bin
$>drwxr-xr-x   2 root      root         4096 Apr 24  2018 boot
$>drwxr-xr-x   5 root      root          360 May  9 11:01 dev
$>drwxr-xr-x   1 root      root         4096 May  9 11:01 etc
$>drwxr-xr-x   1 root      root         4096 Feb  3  2020 home
$>-rwxr-xr-x   1 root      root      1491216 Oct 22  2020 iris-main
$>-rwxr-xr-x   1 root      root          382 Oct 22  2020 irisHealth.sh
$>drwxr-xr-x   1 root      root         4096 May 23  2017 lib
$>drwxr-xr-x   2 root      root         4096 Jan 12  2020 lib64
$>drwxr-xr-x   2 root      root         4096 Jan 12  2020 media
$>drwxr-xr-x   2 root      root         4096 Jan 12  2020 mnt
$>drwxr-xr-x   1 root      root         4096 May  9 11:00 opt
$>dr-xr-xr-x 323 root      root            0 May  9 11:01 proc
$>-rwsr-sr-x   1 root      root        20760 May  9 10:59 rccx
$>drwx------   1 root      root         4096 Oct 22  2020 root
$>drwxr-xr-x   1 root      root         4096 May  9 11:01 run
$>drwxr-xr-x   1 root      root         4096 Feb  3  2020 sbin
$>drwxr-xr-x   2 root      root         4096 Jan 12  2020 srv
$>dr-xr-xr-x  12 root      root            0 May  9 11:00 sys
$>drwxrwxrwt   1 root      root         4096 May  9 11:03 tmp
$>drwxr-xr-x   1 root      root         4096 Oct 22  2020 usr
$>drwxr-xr-x   1 root      root         4096 Jan 12  2020 var
$> *************** done **************
$?> :
~~~
#### what is in /rot in a rootless container?
~~~
??> :
??> :ls -la /root ; whoami
$>#
$>ls: cannot open directory '/root': Permission denied
$>irisowner
$> *************** done **************
??> :          
~~~
#### $ in position 1 changes the view
~~~
??> :
??> :$ls -la /root ; whoami
??> :?
$>#
$>total 24
$>drwx------ 1 root root 4096 Oct 22  2020 .
$>drwxr-xr-x 1 root root 4096 May  9 11:02 ..
$>-rw-r--r-- 1 root root 3106 Apr  9  2018 .bashrc
$>-rw-r--r-- 1 root root  148 Aug 17  2015 .profile
$>-rw-r--r-- 1 root root  176 Feb  3  2020 .wget-hsts
$>-rw-r--r-- 1 root root  199 Oct 22  2020 waitISC.log
$>root
$> *************** done **************
??> :
~~~   

#### and even this is possible
~~~
??> :iris view
??> :iris restart iris quietly
??> :See you!  <<<---- webterminal stops

%SYS > ;; after restart terminal
%SYS > do ^zrccx 
start Run Container Command eXecution
server = localhost,  port = 6666
Enter bash command [?=dump logfile, .=exit, ***=stop executor & exit]
??> :date
??> :?
?
$>#
$>
$>Instance 'IRIS'   (default)
$>      directory:    /usr/irissys
$>      versionid:    2020.4.0.524.0com
$>      datadir:      /usr/irissys
$>      conf file:    iris.cpf  (SuperServer port = 1972, WebServer = 52773)
$>      status:       running, since Sun May  9 11:38:41 2021
$>      state:        alert
$>      product:      InterSystems IRIS
$>#
$>This copy of InterSystems IRIS has been licensed for use exclusively by:
$>InterSystems IRIS Community
$>Copyright (c) 1986-2020 by InterSystems Corporation
$>Any other use is a violation of your license agreement
$>Starting IRIS
$>
$>#
$>Sun May  9 11:44:54 UTC 2021
$> *************** done **************
??> :
~~~
#### Q.A.D.
