#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#define PORT 8080

int stringcmp (char *s1,char *s2)
{
    int i=0,diff=0;
    int pjg=strlen(s2);
    int pjg2=strlen(s1);
    for(i=0; s1[i]!='\0'; i++)
    {
        if( toupper(s1[i])!=toupper(s2[i]) || pjg!=pjg2 )
            return 1;           
    }
    return 0;
}


int main(int argc, char const *argv[]) {
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char hello[1025];
    // memset(hello, ‘ ‘, strlen(hello));
    char *login = "login";
    char *regist = "register";
    char kata[1024],usrname[1024],passwd[1024];
    char *cek = "cek";
    char temp;
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    while(1){
        printf("1.Login\n2.Register\nChoice : ");
        scanf("%s",&*kata);
        if(!stringcmp(kata,login)){
             send(sock , login , strlen(login) , 0 );
            // send(sock , hello , strlen(hello) , 0 );
            printf("Username : ");
            // scanf("%s",&*usrname);
            scanf("%c", &temp);
            scanf("%[^\n]", &*usrname); 
            send(sock , usrname , 1024 , 0 );
            printf("Password : ");
            // scanf("%s",&*passwd);
            scanf("%c", &temp);
            scanf("%[^\n]", &*passwd);
            send(sock , passwd , 1024 , 0 );
            // memset(buffer, 0, sizeof buffer);
            valread = read( sock , buffer, 1024);
            // char *buffer="cuk";
            printf("%s\n",buffer );
            if(!stringcmp(buffer,"login success")){
            while (1)
            {
                printf("1.Find Match\n2.Logout\nChoice : ");
                scanf("%s",&*kata);
                if(!stringcmp(kata,"logout")){
                    send(sock , kata , 1024 , 0 );
                    break;
                }
                else if(!stringcmp(kata,"find")){
                    send(sock , kata , 1024 , 0 );
                    printf("waiting for player\n");
                }
            }
            
            }
            
            memset(buffer, 0, sizeof buffer);
        }
        if(!stringcmp(kata,regist)){
            send(sock , regist , strlen(regist) , 0 );
            printf("register\n");
            printf("Username : ");
            // scanf("%s",&*usrname);
            scanf("%c", &temp);
            scanf("%[^\n]", &*usrname); 
            // fgets(usrname,1024,stdin);
            send(sock , usrname , 1024 , 0 );
            printf("Password : ");
            // scanf("%s",&*passwd);
            scanf("%c", &temp);
            // fgets(passwd,1024,stdin);
            scanf("%[^\n]", &*passwd); 
            printf("register success\n");
            send(sock , passwd , 1024 , 0 );
            // valread = read( sock , buffer, 1024);
            // printf("%s\n",buffer );
            // memset(buffer, 0, sizeof buffer);
            // memset(usrname, 0, sizeof buffer);
            // memset(passwd, 0, sizeof buffer);
        }
    }
    return 0;
}