#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>
//base code to set up client originally from http://www.linuxhowtos.org/data/6/server_udp.c
void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
   int sock, length, n;
   socklen_t fromlen;
   struct sockaddr_in server;
   struct sockaddr_in from;
   char buf[256];

   if (argc < 2) {
      fprintf(stderr, "ERROR, no port provided\n");
      exit(0);
   }
   
   sock=socket(AF_INET, SOCK_DGRAM, 0);//set ups server socket and connection
   if (sock < 0) error("Opening socket");
   length = sizeof(server);
   bzero(&server,length);
   server.sin_family=AF_INET;
   server.sin_addr.s_addr=INADDR_ANY;
   server.sin_port=htons(atoi(argv[1]));
   if (bind(sock,(struct sockaddr *)&server,length)<0) //bind socket
       error("binding");
   fromlen = sizeof(struct sockaddr_in);
   while (1) {//run server indefinitely
       n = recvfrom(sock,buf,256,0,(struct sockaddr *)&from,&fromlen);//receive message from client
       if (n < 0) error("recvfrom");
       
       
     int total = 0;//sum of integers
     char outputBuffer[256];//buffer to output to
     sprintf(outputBuffer, "");//clear buffer
     int characters = 0;
  do{ //iterative process to get response message
     total = 0;
     int end = 0;
     characters = 0;
     for(int i = 0; i < 256; i++)//check every character to see if they are alphabetical or not
     {
          end = i;
          printf("%c", buf[i]);
          if(isalpha(buf[i]) > 0){//alphabetical character
          sprintf(outputBuffer,"From server: Sorry, cannot compute!\n");
          characters = 1; 
          end = 0;
         break;
     }
     else if(buf[i] == '\0'){//break at terminatio
      break;
     }
     }
     
          for(int i = 0; i < end; i++)//for all integers in message
     {
          int digit = buf[i] - 48;//ascii to integer value
         
          if(digit > 0 && digit < 10){//add value
          total += digit;}
     }
     
     
     if(characters == 0){//only if no alphabetical characters print total to buffers and update new buffer to find next sum
     sprintf(outputBuffer, "%sFrom server: %d\n", outputBuffer, total);
     sprintf(buf, "%d", total);
     }
  }while(total > 9);      

       n = sendto(sock,outputBuffer, sizeof(outputBuffer),//send message back
                  0,(struct sockaddr *)&from,fromlen);
       if (n  < 0) error("sendto");
   }
   return 0;
 }