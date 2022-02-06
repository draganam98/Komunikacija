#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int agents(int sock) {

          char buffer[256];
          char *agenti[]={"THOMASMUSTERAUSTRIJA","PETARPETROVICMADJARSKA","DRAGANAMATICTURSKA"
                          ,"MARKOMARKOVICIZRAEL", "MAJKLDZORDANSAD", "LEWHOADAUSTRALIJA",
                          ,"ANDYMURRAYSKODSKA","MARIABUENOBRAYIL","MARATSAFINRUSIJA",
                          "RAFAELNADALSPANIJA"};
          char *alterEgo[]={"JAMESBOND", "TINATARNER","SIDNEYREILLY","IANFLEMINGAIG","DANIELCRAIG"
                            ,"STIVIJANG","AXLROSE","DEJVEVANS","LADYGAGA","ALPACINO"};

          int n, i;
          bzero(buffer,256);
          n = read(sock, buffer, 255);
          buffer[n]=0;
          int j, key=4;
          char ch;

          for(j=0;buffer[j] != '\0';++j){
                   ch=buffer[j];
                   if(ch >= 'A' && ch <= 'Z'){
                          ch = ch-key;
                          if(ch < 'A'){
                                  ch = ch + 'Z' - 'A' + 1;
                          }
                          buffer[j] = ch;
                    }
          }


          for(i=0;i<10;i++){
                   if(strcmp(buffer,alterEgo[i])==0){
                           printf("%s\n",agenti[i]);
                           return 0;
                   }
           }
           printf("AlterEgo se ne poklapa, KOMUNIKACIJA SE PREKIDA!\n");
           return 5;
}


        
void doprocessing (int sock)
{

    int n;
    char buffer[256];
    char sendBuf[256];
    char tempstr[256];

    bzero(buffer,256);
    int done = 0;
    char ch;
    int j,m, key=4;

    while (!done)
    {
      n = read(sock, buffer,255);
      for(j=0;buffer[j] != '\0';++j){
              ch=buffer[j];
              if(ch >= 'A'&& ch <= 'Z'){
                      ch = ch-key;
                      if(ch < 'A'){
                              ch = ch + 'Z' - 'A' + 1;
                      }
                      buffer[j] = ch;
               }
       }
   
       buffer[n] = 0;

       if(strcmp(buffer,"NEEDINFO")==0){

               printf("YOUCANGETINFO"\n");
               m = agents(sock);
               if(m==5){
                        done=1;
               }
       }else if(strcmp(buffer, "ENDE")==0){

                done=1;
                printf("ENDE\n");
       }else{
                done=1;
                printf("KOMUNIKACIJA SE PREKIDA!\n");          

int main( int argc, char *argv[] )
{

   int sockfd, newsockfd, portno, clilen;
   char buffer[256];
   struct sockaddr_in serv_addr, cli_addr;
   int n;

sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd < 0)
{
    perror("ERROR openig socket");
    exit(1);
}


bzero((char *) &serv_addr, sizeof(serv_addr));
portno = 5001;
serv_addr.sin_family = AF_INET;

serv_addr.sin_addr.s_addr = INADDR_ANY;

serv_addr.sin_port = htons(portno);

if  (bind(sockfd, (struct sockaddr *) &serv_addr,
                       sizeof(serv_addr)) < 0)
{
     perror("ERROR on binding");
     exit(1);
}
printf("Server started.. waiting for clients ...\n");


listen(sockfd,5);

clilen = sizeof(cli_addr);

while (1)
{

    newsockfd = accept(sockfd,
            (struct sockaddr *) &cli_addr, &clilen);
    printf("Client connected...\n");
      if (newsockfd < 0)
      {
         perror("ERROR on accept");
         exit(1);
}


int pid = fork();
if (pid < 0)
{
    perror("ERROR on fork");
    exit(1);
}

if (pid == 0)
{

    close(sockfd);
    doprocessing(newsockfd);
    exit(0);
}
else
{


    close(newsockfd);
}
}
}
  
