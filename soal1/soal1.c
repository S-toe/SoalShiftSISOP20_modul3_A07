#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
// #include <conio.h> 
#include<sys/types.h> 
     
    int main() 
    { 
        int heal=100;
        char *read=(char)getchar();
     while(1){
        if(!strcmp(" ",read)){
            heal-=10;
            printf("%d",heal);
        }
     } 
    } 