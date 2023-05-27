This example shows how to execute bash commands outside IRIS.   
It's a low comfort tool for testing and devolpment and not for production.   

### Prerequisites  
Make sure you have [git](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git) and [Docker desktop](https://www.docker.com/products/docker-desktop) installed.   
### Installation   
Clone/git pull the repo into any local directory  
```
$ git clone https://github.com/rcemper/SSH-for-IRIS-container.git   
```
Open the terminal in this directory and run:   
```
$ docker-compose build
```
Run the IRIS container with   
```
$ docker-compose up -d
```
### How to use it:   

Login to WebTerminal   
```
WTv4.9.2 5611fa9229c9:IRIS:_SYSTEM        
Welcome to WebTerminal! Type /help special command to see how to use all the features.  
New update is available. Click here to install it now. Changelist:   
4.9.3:          IRIS 2020 compatibility add   
%SYS > do ^zrccx   
start Run Container Command eXecution  
server = localhost,  port = 6666  
Enter bash command [.=exit, *** = stop executor & exit]  
??> :iris view > /opt/irisbuild/iris_view.log   
??> :  
??> :cp -v /usr/irissys/iris.cpf /irisrun/repo/ > /opt/irisbuild/copy_cpf.log
??> :.   
%SYS >
```
see results:
~~~
$
$ cat copy_cpf.log
'/usr/irissys/iris.cpf' -> '/irisrun/repo/iris.cpf'
$
$ cat iris_view.log

Instance 'IRIS'   (default)
        directory:    /usr/irissys
        versionid:    2020.4.0.524.0com
        datadir:      /usr/irissys
        conf file:    iris.cpf  (SuperServer port = 1972, WebServer = 52773)
        status:       running, since Mon Apr 26 12:50:32 2021
        state:        alert
        product:      InterSystems IRIS
$
~~~
Update to 0.0.3: 
- added logging into /tmp/rccx.log
- single module monolythic build
- no Python, no startscript anymore
- <defunct> zombie processes fixed

[Article in DC](https://community.intersystems.com/post/how-execute-iris-restart-inside)
