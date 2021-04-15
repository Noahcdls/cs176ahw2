#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//base code to set up client originally from http://www.linuxhowtos.org/data/6/client_udp.c
void error(const char *);
int main(int argc, char *argv[])
{
   int sock, n;
   unsigned int length;
   struct sockaddr_in server, from;
   struct hostent *hp;
     char buffer[256];
   
   if (argc != 3) { printf("Usage: server port\n");
                    exit(1);
   }
   sock= socket(AF_INET, SOCK_DGRAM, 0);//set up socket
   if (sock < 0) error("socket");

   server.sin_family = AF_INET;//set up client connection
   hp = gethostbyname(argv[1]);
   if (hp==0) error("Unknown host");

   bcopy((char *)hp->h_addr, 
        (char *)&server.sin_addr,
         hp->h_length);
   server.sin_port = htons(atoi(argv[2]));
   length=sizeof(struct sockaddr_in);
   printf("Enter string: ");//Enter string and grab characters
   bzero(buffer,256);
   fgets(buffer,256,stdin);
   
   n=sendto(sock,buffer,
            256,0,(const struct sockaddr *)&server,length);//send string to server
   if (n < 0) error("Sendto");
 
   n = recvfrom(sock,buffer,256,0,(struct sockaddr *)&from, &length);//wait and receive message from server 
   if (n < 0) error("recvfrom");
   printf(buffer);//print out message
   close(sock);//close connection
   return 0;
}

void error(const char *msg)
{
    perror(msg);
    exit(0);
}