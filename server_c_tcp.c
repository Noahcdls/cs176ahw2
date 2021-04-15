#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
//base code to set up client originally from http://www.linuxhowtos.org/data/6/server_tcp.c
void error(const char *msg)
{
    perror(msg);
    exit(1);
}
int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);//set up port and server
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
while(1){//run server forever
     if(listen(sockfd,1) < 0)//wait for message
       error("ERROR on listening");
     clilen = sizeof(cli_addr);//set up and store new client
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
     bzero(buffer,256);
     n = read(newsockfd,buffer,255);//read message from client
     if (n < 0) error("ERROR reading from socket");
     
     int total = 0;//sum of integers
     char outputBuffer[256];//buffer for response message
     bzero(outputBuffer,256);
     int characters = 0;
  do
  {  
      
     total = 0;
     int end = 0;
     for(int i = 0; i < 256; i++)//iterate every character to see if valid
     {
          if(isalpha(buffer[i]) > 0){//alphabetical character
          printf("is alpha");
          sprintf(outputBuffer,"From server: Sorry, cannot compute!\n");
          characters = 1; 
          end = 0;
         break;
     }
     else if(buffer[i] == '\0'){
     end = i;
      break;
     }
     }
     
          for(int i = 0; i < end; i++)
     {
          int digit = buffer[i] - '0';//convert to integer from ascii
          if(digit > 0 && digit < 10)
          total += digit;
     }
     
     
     if(characters == 0){//no alphabetical characters so write to buffers for message and new value to evaluate for sum
     sprintf(outputBuffer, "%sFrom server: %d\n", outputBuffer, total);
     sprintf(buffer, "%d", total);
     }

     }while(total > 9);

     n = write(newsockfd, outputBuffer , sizeof(buffer)); //write back to client
     if (n < 0) error("ERROR writing to socket");
  
     close(newsockfd);//close connection with client
     }
     return 0; 
}