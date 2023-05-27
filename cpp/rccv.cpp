/* verbose version for debug & testing */
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h> 
# include <sys/socket.h>
# include <netinet/in.h>
# include <iostream>
# include <sys/wait.h>
 
int docmd(int);  /* function prototype */
void execmd(std::string cmd) ; /*prototype */
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
 	 int sockfd, newsockfd, pid, cli_port,  portno, doit ; 
     socklen_t clilen;
     struct sockaddr_in serv_addr, cli_addr;

     if (argc < 2) {
         portno = 6666;
         std::cout << "No port provided " << std::endl;
     } else  { portno = atoi(argv[1]); }
     std::cout << "listen on port: " << portno << std::endl;
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     
     listen(sockfd,0);
     clilen = sizeof(cli_addr);
     while (1) {
         newsockfd = accept(sockfd, 
               (struct sockaddr *) &cli_addr, &clilen);
         if (newsockfd < 0) {
             error("ERROR on accept");
         }
        cli_port = ntohs(cli_addr.sin_port) ;
        std::cout << "client-port: " << cli_port << std::endl ;  
        doit =  docmd(newsockfd);
        std::cout << "after stuff = "<< doit << std::endl ;
        close(newsockfd) ;
        if (doit < 0 )  break ;           
     }
     close(sockfd);
     return 0;
}
// analyze commands
int docmd(int sock)
{
   int n = 1 ;
   char buffer[256];
   std::string cmd ;
   bzero(buffer,256);
   
  while(n > 0) {    
   n = read(sock,buffer,255);
   buffer[n] = 0  ;
   cmd = std::string(buffer);
   if (n < 0) error("ERROR reading from socket");
   if ( n == 0) {
      std::cout << " no command " << std::endl;
      close(sock) ;
      break ;
      }
   if (cmd.substr(0,10) == "###stop###") { 
        std::cout << "stop server :" << cmd << std::endl;
        close(sock) ;
        n =-1;
        break ;
        }
   std::cout << cmd << std::endl;
   if (cmd.substr(0,1) == "#") {
	   continue ;   // skip comments
     }
   execmd(cmd) ;     
  }
/* only required for reply */  
//  n = write(sock,"I got your message",18);
//  if (n < 0) error("ERROR writing to socket");
//    std::cout << "return" << n << std::endl;
  return n ;
}
// execute commands
void execmd(std::string cmd)
{
using namespace std;
  int sc1,sc2,sc3,pid,fstat;
  int ui = getuid();
  int gi = getgid();
  string dl = "$";
  bool rt = (cmd.substr(0,1) == dl) ;
  cout << rt << ":" << cmd.substr(0,1) << "-" << cmd.length() << endl; 

  if (rt) {
    cmd=cmd.substr(1); 
    }
  cout << rt << ":" << cmd << "-" << cmd.length() << endl; 
  if (cmd.length() == 0) return ;

  cmd = "( echo '#' ; " + cmd + " ; exit ) >> /tmp/rccx.log 2>&1 " ;   
  cout << rt << ":" << cmd << "-" << cmd.length() << endl; 
  cout << "UI 1>" << ui << ":" << gi << endl;
	
	pid = vfork();
    if (pid < 0) {
		error("ERROR on fork"); 
		}
	if (pid > 0 ) {
// main process		
		cout << "pid = " << pid << " spawned " << endl;
		waitpid(pid,&fstat,0) ;
		cout << pid << "comlpeted" << endl ;
		return ;
		}
// now spawned		
	cout << getpid() << " = spawned : " << cmd <<  endl;
 if (rt) {
    sc1 = setuid(0); 
    sc2 = setgid(0);
    cout << "==1> " << sc1 << " : " << sc2 << endl;      
    }  
  try {
	  
   sc3 = system(cmd.c_str()) ;
    }
  catch (...) {}
	cout << "spawned return " << endl;  
	_exit(0);
}
