#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
void error(const char *msg)
{
    perror(msg);
    exit(1);
}
int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[128];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
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
     if(listen(sockfd,1) < 0)
       error("ERROR on listening");
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
     bzero(buffer,128);
     n = read(newsockfd,buffer,127);
     if (n < 0) error("ERROR reading from socket");
     
     int total = 10;
  while(total > 9)
  {  
     int characters = 0;
     total = 0;
     int end = 0;
     for(int i = 0; i < 128; i++)
     {
          if(isalpha(buffer[i])){//alphabetical character
          n = write(newsockfd,"Sorry, cannot compute!",22);
          characters = 1; 
          if (n < 0) error("ERROR writing to socket");
         break;
     }
     else if(buffer[i] == '\0'){
     end = i;
      break;
     }
     }
     
          for(int i = 0; i < end; i++)
     {
          int digit = buffer[i] - '0';
          if(digit > -1 && digit < 10)
          total += digit;
     }
     char tempword[20];
     sprintf(tempword, "From server: %d", total);
     
     if(characters == 0){
     n = write(newsockfd, tempword , sizeof(tempword));
     n = read(newsockfd,buffer,127);
     if (n < 0) error("ERROR writing to socket");
     }
     
     sprintf(buffer, "%d", total);
     }
     sprintf(buffer, "d");
     n = write(newsockfd, buffer , sizeof(buffer)); 
     if (n < 0) error("ERROR writing to socket");
     close(newsockfd);
     close(sockfd);
     return 0; 
}