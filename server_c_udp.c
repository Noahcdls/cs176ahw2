#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>

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
   char buf[128];

   if (argc < 2) {
      fprintf(stderr, "ERROR, no port provided\n");
      exit(0);
   }
   
   sock=socket(AF_INET, SOCK_DGRAM, 0);
   if (sock < 0) error("Opening socket");
   length = sizeof(server);
   bzero(&server,length);
   server.sin_family=AF_INET;
   server.sin_addr.s_addr=INADDR_ANY;
   server.sin_port=htons(atoi(argv[1]));
   if (bind(sock,(struct sockaddr *)&server,length)<0) 
       error("binding");
   fromlen = sizeof(struct sockaddr_in);
   while (1) {
       n = recvfrom(sock,buf,128,0,(struct sockaddr *)&from,&fromlen);
       if (n < 0) error("recvfrom");
       
       
     int total = 0;
     char outputBuffer[256];
     bzero(outputBuffer,256);
     int characters = 0;
  do{ 
     total = 0;
     int end = 0;
     for(int i = 0; i < 128; i++)
     {
          if(isalpha(buf[i]) > 0){//alphabetical character
          sprintf(outputBuffer,"From server: Sorry, cannot compute!\n");
          characters = 1; 
          end = 0;
         break;
     }
     else if(buf[i] == '\0'){
     end = i;
      break;
     }
     }
     
          for(int i = 0; i < end; i++)
     {
          int digit = buf[i] - '0';
          //printf("%c == %d\n", buf[i], digit);
          if(digit > 0 && digit < 10)
          total += digit;
     }
     
     
     if(characters == 0){
     sprintf(outputBuffer, "%sFrom server: %d\n", outputBuffer, total);
     sprintf(buf, "%d", total);
     }
  }while(total > 9);      

       n = sendto(sock,outputBuffer, sizeof(outputBuffer),
                  0,(struct sockaddr *)&from,fromlen);
       if (n  < 0) error("sendto");
   }
   return 0;
 }