# SoalShiftSISOP20_modul3_A07

## Thread dan IPC

## 2. Soal 2
```
Qiqi adalah sahabat MamMam dan Kaka. Qiqi , Kaka dan MamMam sangat senang
bermain “Rainbow six” bersama-sama , akan tetapi MamMam sangat Toxic ia selalu
melakukan Team killing kepada Qiqi di setiap permainannya. Karena Qiqi orang yang
baik hati, meskipun marah Qiqi selalu berkata “Aku nggk marah!!”. Kaka ingin
meredam kemarahan Qiqi dengan membuatkannya sebuah game yaitu TapTap
Game. akan tetapi Kaka tidak bisa membuatnya sendiri, ia butuh bantuan mu. Ayo!!
Bantu Kaka menenangkan Qiqi.
TapTap Game adalah game online berbasis text console. Terdapat 2 program yaitu
tapserver.c dan tapplayer.c
Syarat :
- Menggunakan Socket, dan Thread
Hint :
- fwrite, fread
Spesifikasi Game :

CLIENT SIDE

Screen 1 :
1. Login
2. Register
Choices : {your input}
★ Pada screen 1 kalian dapat menginputkan “login”, setelah menekan enter
anda diminta untuk menginputkan username dan password seperti berikut
Screen 1 :
1. Login
2. Register
Choices : login
Username : { ex : qiqi }
Password : { ex : aku nggak marah!! }
★ Jika login berhasil maka akan menampilkan pesan “login success”, jika gagal
akan menampilkan pesan “login failed” (pengecekan login hanya mengecek
username dan password, maka dapat multi autentikasi dengan username dan
password yang sama)
★ Pada screen 1 kalian juga dapat menginputkan “register”, setelah menekan
enter anda diminta untuk menginputkan username dan password sama
halnya seperti login
★ Pada register tidak ada pengecekan unique username, maka setelah register
akan langsung menampilkan pesan “register success” dan dapat terjadi
double account
★ Setelah login berhasil maka anda berpindah ke screen 2 dimana
menampilkan 2 fitur seperti berikut.

Screen 2 :
1. Find Match
2. Logout
Choices : {your input}
★ Pada screen 2 anda dapat menginputkan “logout” setelah logout anda akan
kembali ke screen 1
★ Pada screen 2 anda dapat menginputkan “find”, setelah itu akan
menampilkan pesan “Waiting for player ...” print terus sampai menemukan
lawan
★ Jika menemukan lawan maka akan menampilkan pesan “Game dimulai
silahkan tap tap secepat mungkin !!”
★ Pada saat game dimulai diberikan variable health = 100,dan anda dapat
men-tap (menekan space pada keyboard tanpa harus menekan enter)
★ Pada saat anda men-tap maka akan menampilkan pesan “hit !!”, dan pada
lawan healthnya akan berkurang sebanyak 10 kemudian pada lawan
menampilkan pesan status healthnya sekarang. (conclusion : anda tidak bisa
melihat status health lawan)
★ Jika health anda <= 0 maka akan menampilkan pesan “Game berakhir kamu
kalah”, apabila lawan anda healthnya <= 0 maka akan menampilkan pesan
”Game berakhir kamu menang”
★ Setelah menang atau kalah maka akan kembali ke screen 2

SERVER SIDE

★ Pada saat program pertama kali dijalankan maka program akan membuat file
akun.txt jika file tersebut tidak ada. File tersebut digunakan untuk menyimpan
username dan password
★ Pada saat user berhasil login maka akan menampilkan pesan “Auth success” jika
gagal “Auth Failed”
★ Pada saat user sukses meregister maka akan menampilkan List account yang
terdaftar (username dan password harus terlihat)
```
Dalam pengerjaannya saya membuat dua buah file script .c yang akan menjadi server dan client sebagai berikut :
```c
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include<pthread.h>
#define PORT 8080

pthread_t tid[3000];
int find;
struct Akun
       {
              char name[50];
              char passwd[50];
       };

struct player
       {
              int id;
              int health;
       };

int stringcmp (char *s1,char *s2)
{
    int i=0,diff=0;
    for(i=0; s1[i]!='\0'; i++)
    {
        if( toupper(s1[i])!=toupper(s2[i]) )
            return 1;           
    }
    return 0;
}

void *client(void *tmp){
    FILE *fp, *fp2, *fp3;
    struct Akun akun,akun2;
    int valread;
    char buffer[1024] = {0};
    char hello[1024];
    char *regist = "register";
    char *login = "login";
    int new_socket = *(int *)tmp;
    int player = new_socket;
    printf("player:%d soc_addr:%d\n",player,new_socket);

     while(1){
        
        valread = read( new_socket , buffer, 1024);
        // printf("Hello message sent1\n");
        // printf("%s\n",buffer );
        if(!stringcmp(login,buffer)){
            // Count++;
            valread = read( new_socket , akun.name, 1024);
            // printf("1\n");
            valread = read( new_socket , akun.passwd, 1024);
            // printf("%s %s %s\n",buffer,akun.name,akun.passwd);
            fp3 = fopen("akun.txt","a+");
            // if(fp3 == NULL)
            //   {
            //          printf("\nCan't open file or file doesn't exist.");
            //          exit(0);
            //   }
            // printf("%s2\n",buffer );
            // // akun2.name = malloc(sizeof(akun.name));
            // if (akun2.name == NULL)
            // exit(EXIT_FAILURE);

            // akun2.passwd = malloc(sizeof(akun.passwd));
            // if (akun2.passwd == NULL)
            // exit(EXIT_FAILURE);
            int flag=0;
            while(fread(&akun2, sizeof(struct Akun), 1, fp3)){
                if(strcmp(akun.name,akun2.name)==0 && strcmp(akun.passwd,akun2.passwd)==0){
                // printf ("username = %s password = %s\n", akun2.name, akun2.passwd);
                // char *othing = "login failed";
                char *buffer = "login success";
                // printf("%s\n",buffer);
                send(new_socket , buffer , strlen(buffer) , 0 );
                // printf("%s\n",buffer);
                flag=1;
                break;
                }
                // printf("masok");
            }
            if (flag==0){
                printf("Auth Failed\n");

                char *buffer = "login failed";
                // char *lucky = "login success";
                send(new_socket , buffer , strlen(buffer) , 0 );
            }
            else if(flag==1){
                printf("Auth success\n");
                while(1){
                    valread = read( new_socket , buffer, 1024);
                    // printf("masuk pilihan log\n");
                    if(!stringcmp("logout",buffer)){
                        break;
                    }
                    else if(!stringcmp("find",buffer)){
                        // printf("nyarii\n");
                        int opponent;
                        struct player player1,player2;

                        if(!find){
                            // printf("find:%d\n",find);
                            find=player;

                            // printf("1 find:%d client:%d opponent:%d\n",find,player,opponent);

                            while (find == player)
                            {
                                //waiting for opponent;
                                // printf("nyarii2\n");
                                // printf("loop find:%d client:%d opponent:%d\n",find,player,opponent);
                                send(player,"find",4,0);
                                sleep(1);
                            }
                            // printf("nemu!");
                            send(player,"found",5,0);
                            opponent = find;
                            // printf("2 find:%d client:%d opponent:%d\n",find,player,opponent);
                               
                        }
                        else{
                            send(player,"found",5,0);
                            opponent=find;
                            find=player;
                            sleep(1);
                            find=0;
                            player1.id=player;
                            player2.id=opponent;
                            
                            // printf("3 find:%d client:%d opponent:%d\n",find,player,opponent);
                        }
                            player1.health=player2.health=100;
                        //  printf("last find:%d client:%d opponent:%d\n",find,player,opponent);
                         
                            // if(player2.health==100)
                            //     send(opponent,"health 100",10,0);

                         while(1){
                            memset(buffer,0,1024);
                            // printf("%d %d\n",player1.health,player2.health);
                            valread = read( new_socket , buffer, 1024);
                            // printf("ini buffer:%s\n",buffer);
                            // printf("last-last new_socket:%d find:%d client:%d opponent:%d\n",new_socket,find,player,opponent);
                           

                            if(!strcmp(buffer,"hit")){
                                
                                // printf("masuk hit\n");
                                // printf("hitt\n");
                                // if(new_socket == player){
                                    
                                    // printf("dalam player\n");
                                    player2.health = player2.health - 10;
                                    // printf("%d %d\n",player1.health,player2.health);
                                    char healt[1024];
                                    // printf("setelah deklarasi healt\n");
                                    sprintf(healt,"%d",player2.health);
                                    // printf("setelah naro isi healt\n");
                                    char buffer[1024] = "health ";
                                    // printf("setelah naro healt ke buffer\n");
                                    strcat(buffer,healt);
                                    // printf("setelah setelah gabung healt\n");
                                    send(opponent,buffer,1024,0);
                                
                                if(player2.health <= 0) {
                                    //  printf("masuk player win\n");
                                     send(player, "win", strlen("win"), 0);
                                    //  printf("masuk player win\n");
                                     send(opponent, "dead", strlen("dead"), 0);
                                     break;
                                 }

                                if(player1.health <= 0) {
                                     send(player, "dead", strlen("dead"), 0);
                                     send(opponent, "win", strlen("win"), 0);
                                     break;
                                 }
                            }
                            if(!strcmp(buffer,"dead"))break;
                        }
                    }
                }
            }
              fclose(fp3);
            
            // char hello1[1024] = "Penambahan Berhasil";
            // send(new_socket , hello1 , strlen(hello1) , 0 );
            // printf("Hello message sent1\n");
        }
        if(!stringcmp(regist,buffer)){
            // sprintf(hello,"%d",Count);
            fp2 = fopen("akun.txt","a");

        // fclose(fp);
            // printf("register\n" );
            valread = read( new_socket , akun.name, 1024);
            // sleep(1);
            valread = read( new_socket , akun.passwd, 1024);
            // printf("%s %s %s\n",buffer,akun.name,akun.passwd);
            fwrite(&akun,sizeof(akun),1,fp2);
            fclose(fp2);
            fp = fopen("akun.txt","r");
            while(fread(&akun, sizeof(struct Akun), 1, fp)) 
            printf ("username = %s password = %s\n", akun.name, akun.passwd); 
                // printf("masok");
            fclose(fp);
            // send(new_socket , hello , strlen(hello) , 0 );
            // printf("Hello message sent2\n");
        }
        // else  printf("nope" );

    }

}

int main(int argc, char const *argv[]) {
    FILE *fp, *fp2, *fp3;
    // char name[50];
    // char passwd[50];
    struct Akun akun,akun2;
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    // int Count=0;
    char hello[1024];
    char *regist = "register";
    char *login = "login";
    find=0;
    // char *othing = "login failed";
    // char *lucky = "login success";
    // char *cek = "cek";
      
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
   
//    fp = fopen("akun.txt","a");
//         if(fp == NULL){
//             // system("touch /home/stoe/PRAKTIKUM/MODUL3/soal2/akun.txt");
//         }
//         fclose(fp);

int total=0;
    while(1){
        
        // valread = read( new_socket , buffer, 1024);
        // // printf("Hello message sent1\n");
        // // printf("%s\n",buffer );
        // if(!stringcmp(login,buffer)){
        //     // Count++;
        //     valread = read( new_socket , akun.name, 1024);
        //     // printf("1\n");
        //     valread = read( new_socket , akun.passwd, 1024);
        //     // printf("%s %s %s\n",buffer,akun.name,akun.passwd);
        //     fp3 = fopen("akun.txt","r");
        //     // if(fp3 == NULL)
        //     //   {
        //     //          printf("\nCan't open file or file doesn't exist.");
        //     //          exit(0);
        //     //   }
        //     // printf("%s2\n",buffer );
        //     // // akun2.name = malloc(sizeof(akun.name));
        //     // if (akun2.name == NULL)
        //     // exit(EXIT_FAILURE);

        //     // akun2.passwd = malloc(sizeof(akun.passwd));
        //     // if (akun2.passwd == NULL)
        //     // exit(EXIT_FAILURE);
        //     int flag=0;
        //     while(fread(&akun2, sizeof(struct Akun), 1, fp3)){
        //         if(strcmp(akun.name,akun2.name)==0 && strcmp(akun.passwd,akun2.passwd)==0){
        //         // printf ("username = %s password = %s\n", akun2.name, akun2.passwd);
        //         // char *othing = "login failed";
        //         char *buffer = "login success";
        //         // printf("%s\n",buffer);
        //         send(new_socket , buffer , strlen(buffer) , 0 );
        //         // printf("%s\n",buffer);
        //         flag=1;
        //         }
        //         // printf("masok");
        //     }
        //     if (flag==0){
        //         printf("Auth Failed\n");

        //         char *buffer = "login failed";
        //         // char *lucky = "login success";
        //         send(new_socket , buffer , strlen(buffer) , 0 );
        //     }
        //     else {
        //         printf("Auth success\n");
                
        //     }
        //       fclose(fp3);
            
        //     // char hello1[1024] = "Penambahan Berhasil";
        //     // send(new_socket , hello1 , strlen(hello1) , 0 );
        //     // printf("Hello message sent1\n");
        // }
        // if(!stringcmp(regist,buffer)){
        //     // sprintf(hello,"%d",Count);
        //     fp2 = fopen("akun.txt","a");

        // // fclose(fp);
        //     // printf("register\n" );
        //     valread = read( new_socket , akun.name, 1024);
        //     // sleep(1);
        //     valread = read( new_socket , akun.passwd, 1024);
        //     // printf("%s %s %s\n",buffer,akun.name,akun.passwd);
        //     fwrite(&akun,sizeof(akun),1,fp2);
        //     fclose(fp2);
        //     fp = fopen("akun.txt","r");
        //     while(fread(&akun, sizeof(struct Akun), 1, fp)) 
        //     printf ("username = %s password = %s\n", akun.name, akun.passwd); 
        //         // printf("masok");
        //     fclose(fp);
        //     // send(new_socket , hello , strlen(hello) , 0 );
        //     // printf("Hello message sent2\n");
        // }
        // // else  printf("nope" );

        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        
        pthread_create(&(tid[total]), NULL, &client, &new_socket);
        total++;
        printf("%d\n",total);
    }
    return 0;
}
```

```c
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <termios.h>
#include <pthread.h>
#define PORT 8080

// static struct termios stored;
int sock = 0, valread;
int status = 0;
pthread_t thread;

static struct termios stored_settings;

void set_keypress(void)
{
    struct termios new_settings;
    tcgetattr(0,&stored_settings);
    new_settings = stored_settings;
    new_settings.c_lflag &= (~ICANON);
    new_settings.c_cc[VTIME] = 0;
    new_settings.c_cc[VMIN] = 1;
    tcsetattr(0,TCSANOW,&new_settings);
    return;
}

void reset_keypress(void)
{
    tcsetattr(0,TCSANOW,&stored_settings);
    return;
}

// void set_keypress(void)
// {
//     struct termios new;

//     tcgetattr(0,&stored);

//     memcpy(&new,&stored,sizeof(struct termios));

//     /* Disable canonical mode, and set buffer size to 1 byte */
//     new.c_lflag &= (~ICANON);
//     new.c_cc[VTIME] = 0;
//     new.c_cc[VMIN] = 1;

//     tcsetattr(0,TCSANOW,&new);
//     return;
// }

// void reset_keypress(void)
// {
//     tcsetattr(0,TCSANOW,&stored);
//     return;
// }


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

void *cekhasil( void *ptr )
{
    char buffer[1024];
    while(1) {
        valread = read(sock, buffer, 1024);
        printf("%s\n",buffer);
        if(!strcmp(buffer, "win")) {
            printf("Game berakhir kamu menang\n");
            status = 2;
            break;
        }

        if(!strcmp(buffer, "dead")) {
            printf("Game berakhir kamu kalah\n");
            send(sock , "dead" , strlen("dead"), 0 );
            status = -1;
            break;
        }
        // printf("%d\n",status);
        // sleep(1);
        // printf("buffer ini : %s\n", buffer);

        memset(buffer, 0, sizeof(buffer));
    }

    status = 0;
    return NULL;
}

int main(int argc, char const *argv[]) {
    struct sockaddr_in address;
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
            memset(buffer, 0, sizeof buffer);
            valread = read( sock , buffer, 1024);
            // char *buffer="cuk";
            printf("%s\n",buffer );
            if(!stringcmp(buffer,"login success")){
            while (1){
                printf("1.Find Match\n2.Logout\nChoice : ");
                scanf("%s",&*kata);
                if(!stringcmp(kata,"logout")){
                    send(sock , kata , 1024 , 0 );
                    break;
                }
                else if(!stringcmp(kata,"find")){
                    
                    send(sock , kata , 1024 , 0 );
                    while(!stringcmp(kata,"find")){
                    read(sock,kata,1024);
                    printf("waiting for player\n");
                    
                    }
                    printf("Game dimulai silahkan tap tap secepat mungkin !!\n");

                    sleep(1);

                    status = 1;

                    int iret = pthread_create(&thread,NULL,&cekhasil,NULL);

                    if(iret)
                    {
                        fprintf(stderr,"Error - pthread_create() return code: %d\n",iret);
                        exit(EXIT_FAILURE);
                    }

                    set_keypress();
                    // printf("sebelum masuk while\n");
                    // char text[10];
                    // valread = read(sock, text, 10);
                    // printf("%s\n",text);
                    // printf("tetet\n");

                    while (status == 1)
                    {
                        if(status != 1) break;
                        // printf("status:%d\n",status);
                        char c = getc(stdin);
                        if(status == 2) break;
                        if(c == 32) {

                            // printf("dalam 32\n");
                            if(status != 2){
                                send(sock , "hit" , strlen("hit"), 0 );
                                printf("hit !!\n");
                            }
                        }
                    }
                    status = 0;
                    
                    reset_keypress();


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
```

Dalam script pertama kita membuat sebuah server yang akan menjadi proses utama untuk menerima proses client yang masuk. Didalamnya dibuat thread agar client yang masuk bisa lebih dari satu.

didalam looping, proses akan menerima setiap pesan dari client atau player proses dimulai dari register, login, dan seterusya. Dari server juga akan mengirim pesan selanjutnya setelah menerima pesan dari client.

Dalam script kedua kita membuat sebuah client yang akan menjadi proses untuk mengirim pesan ke server. Didalamnya dibuat thread yang berguna pada saat game dimulai sampai mendapat pesan game selesai dari server.

didalam looping, proses akan mengirim setiap pesan ke server proses dimulai dari register, login, dan seterusya.

Berikut gambar ketika programnya dijalankan:

![soal2a](https://user-images.githubusercontent.com/58405725/79046400-f2b33680-7c3a-11ea-85ba-53db4940acd4.png)
![soal2b](https://user-images.githubusercontent.com/58405725/79046402-f646bd80-7c3a-11ea-9daa-4716dca9b834.png)

## 3. Soal 3

```
Buatlah sebuah program dari C untuk mengkategorikan file. Program ini akan
memindahkan file sesuai ekstensinya (tidak case sensitive. JPG dan jpg adalah
sama) ke dalam folder sesuai ekstensinya yang folder hasilnya terdapat di working
directory ketika program kategori tersebut dijalankan.
● Semisal program dijalankan:
# File kategori terletak di /home/izone/kategori
$ ./kategori -f path/to/file1.jpg path/to/file2.c path/to/file3.zip
#Hasilnya adalah sebagai berikut
/home/izone
|-jpg
|--file1.jpg
|-c
|--file2.c
|-zip
|--file3.zi
● Pada opsi -f tersebut, user bisa menambahkan argumen file yang bisa
dikategorikan sebanyak yang user inginkan seperti contoh di atas.
● Pada program kategori tersebut, folder jpg,c,zip tidak dibuat secara manual,
melainkan melalui program c. Semisal ada file yang tidak memiliki ekstensi,
maka dia akan disimpan dalam folder “Unknown”.
● Program kategori ini juga menerima perintah (*) seperti di bawah;
$ ./kategori \*
● Artinya mengkategori seluruh file yang ada di working directory ketika
menjalankan program C tersebut.
● Selain hal itu program C ini juga menerima opsi -d untuk melakukan kategori
pada suatu directory. Untuk opsi -d ini, user hanya bisa menginput 1 directory
saja, tidak seperti file yang bebas menginput file sebanyak mungkin.
$ ./kategori -d /path/to/directory/
● Hasilnya perintah di atas adalah mengkategorikan file di /path/to/directory dan
hasilnya akan disimpan di working directory di mana program C tersebut
berjalan (hasil kategori filenya bukan di /path/to/directory).
● Program ini tidak rekursif. Semisal di directory yang mau dikategorikan, atau
menggunakan (*) terdapat folder yang berisi file, maka file dalam folder
tersebut tidak dihiraukan, cukup file pada 1 level saja.
● Setiap 1 file yang dikategorikan dioperasikan oleh 1 thread agar bisa berjalan
secara paralel sehingga proses kategori bisa berjalan lebih cepat. Dilarang
juga menggunakan fork-exec dan system.
● Silahkan download soal3.zip sebagai percobaan. Namun silahkan
dicoba-coba sendiri untuk kemungkinan test case lainnya yang mungkin
belum ada di soal3.zip.
```

Dalam pengerjaannya saya kembali membuat sebuah file script .c sebagai berikut :

```c
#include <dirent.h>
#include <libgen.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 500

char pwd[MAX];

int isDirectory(const char *path){
  struct stat path_stat;
  stat(path, &path_stat);
  return S_ISDIR(path_stat.st_mode);
}

const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

void *moveFile(void *filename) {
    char *source = (char *)filename;
    char new_source[MAX];
    strcpy(new_source, source);
    FILE *fp1, *fp2;
    int ch;

    char *filenm = basename(source);
    const char *eks = get_filename_ext(source);
    char ekstention[300];
    int Lg=strlen(eks);
    bzero(ekstention,300);
    bzero(new_source,500);
    // printf("1\n");
    for (int i = 0; i <= Lg; i++){
        ekstention[i] = tolower(eks[i]);
        // printf("%d\n",ekstention[i-1]);
    }
    // printf("%s\n",ekstention);
    // printf("2\n");

    if(!Lg) {
        if(!isDirectory("Unknown"))mkdir("Unknown", 0777);
        strcpy(new_source, "Unknown/");
        strcat(new_source, filenm);
    }else{

        // printf("3\n");
        if(!isDirectory(ekstention))mkdir(ekstention, 0777);
        // printf("4\n");
        strcpy(new_source, ekstention);
        // printf("5\n");
        strcat(new_source, "/");
        // printf("6\n");
        strcat(new_source, filenm);
        printf("%s\n",new_source);
        // printf("7\n");
    }
    // printf("8\n");
    fp1 = fopen(source, "rb");
    // printf("9\n");
    fp2 = fopen(new_source, "wb");
    // printf("10\n");
    while ((ch = fgetc(fp1)) != EOF) fputc(ch, fp2);
    // printf("11\n");
    fclose(fp1);
    // printf("13\n");
    fclose(fp2);
    // printf("14\n");
    remove(source);
    // printf("12\n");
}

int main(int argc, char **argv){
    if (argc <= 1){
    printf("Harusnya ada argumen!\n");
    exit(EXIT_FAILURE);
  }

  getcwd(pwd, sizeof(pwd));
  pthread_t threads[3000];
  struct dirent *dir;
  int err;

  if (strcmp(argv[1], "*") == 0 && argc == 2){
    int file_count = 0;
    char files[MAX][MAX];

    DIR *d;
    d = opendir(".");

    if (d){
      while (dir = readdir(d)){
        if(strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0 && !isDirectory(dir->d_name)){
          char tmp[100];
          strcpy(tmp, dir->d_name);
          sprintf(files[file_count], "%s", dir->d_name);
          file_count++;
        }
      }
      closedir(d);
    }

    for (int i = 0; i < file_count; i++){
        err=pthread_create(&threads[i], NULL, moveFile, files[i]);
        if(err){
            fprintf(stderr,"Error - pthread_create() return code: %d\n",err);
            exit(EXIT_FAILURE);
        }
        err=0;
    }
    for (int i = 0; i < file_count; i++){
        pthread_join(threads[i], NULL);
    }
  }

  else if (strcmp(argv[1], "-d") == 0 && argc == 3){
    int file_count = 0;
    char files[MAX][MAX];

    DIR *d;
    chdir(argv[2]);
    d = opendir(".");

    if (d){
      while (dir = readdir(d)){
        if(strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0 && !isDirectory(dir->d_name)){
          char tmp[100];
          strcpy(tmp, dir->d_name);
          sprintf(files[file_count], "%s/%s", argv[2], dir->d_name);
          file_count++;
        }
      }
      closedir(d);
    }

    chdir(pwd);
    for (int i = 0; i < file_count; i++){
        err=pthread_create(&threads[i], NULL, moveFile, files[i]);
        if(err){
            fprintf(stderr,"Error - pthread_create() return code: %d\n",err);
            exit(EXIT_FAILURE);
        }
        err=0;
    }
    for (int i = 0; i < file_count; i++){
        pthread_join(threads[i], NULL);
    }
  }

  else if (strcmp(argv[1], "-f") == 0 && argc>2){
    for (int i = 2; i < argc; i++){
      if(!isDirectory(argv[i]))
        err=pthread_create(&threads[i-2], NULL, moveFile, argv[i]);
      else
        printf("%s is a directory\n", argv[i]);

      if(err){
        fprintf(stderr,"Error - pthread_create() return code: %d\n",err);
        exit(EXIT_FAILURE);
      }
      err=0;
    }
    for (int i = 2; i < argc; i++){
      pthread_join(threads[i-2], NULL);
    }
  }

  else
    printf("Argument salah gans!!\n");

}
```
Dalam script ini kita membuat sebuah program untuk memindahkan sebuah file ke sebuah folder sesuai ekstensinya. Pertama membaca argument dari program saat dijalankan, sehingga program berjalan sesuai argument yang di input.

kemudian dibuat fungsi memindahkan file ke dalam folder yang dibuat berdasarkan ekstensinya, yang mana ekstensinya didapat melalui fungsi yang telah dibuat sebelumnya.

Setiap ekstensi dirubah ke huruf kecil terlebih dahulu sebelum dibuat foldernya, karena misal JPG dengan jpg adalah sama.

setelah dibuat setiap file disalin ke dalam folder berdasarkan biner dan file asalnya dihapus..

tetapi dalam pengerjaan saya ada kekurangan dimana file eksekutornya ikut terpindah apabila dijalankan. sehingga program terhenti sebab file eksekutor sudah tidak ada.

Berikut gambar ketika program dijalankan:

![soal3a](https://user-images.githubusercontent.com/58405725/79046406-f8a91780-7c3a-11ea-948f-41a64da38a7e.png)
![soal3b](https://user-images.githubusercontent.com/58405725/79046407-fa72db00-7c3a-11ea-8d34-ffe30769f4e0.png)

## 4. Soal 4
```
Norland adalah seorang penjelajah terkenal. Pada suatu malam Norland menyusuri
jalan setapak menuju ke sebuah gua dan mendapati tiga pilar yang pada setiap
pilarnya ada sebuah batu berkilau yang tertancap. Batu itu berkilau di kegelapan dan
setiap batunya memiliki warna yang berbeda.
Norland mendapati ada sebuah teka-teki yang tertulis di setiap pilar. Untuk dapat
mengambil batu mulia di suatu pilar, Ia harus memecahkan teka-teki yang ada di
pilar tersebut. Norland menghampiri setiap pilar secara bergantian.
- Batu mulia pertama. Emerald. Batu mulia yang berwarna hijau mengkilat. Pada
batu itu Ia menemukan sebuah kalimat petunjuk. Ada sebuah teka-teki yang berisi:
1. Buatlah program C dengan nama "4a.c", yang berisi program untuk
melakukan perkalian matriks. Ukuran matriks pertama adalah 4x2, dan
matriks kedua 2x5. Isi dari matriks didefinisikan di dalam kodingan. Matriks
nantinya akan berisi angka 1-20 (tidak perlu dibuat filter angka).
2. Tampilkan matriks hasil perkalian tadi ke layar.

- Batu kedua adalah Amethyst. Batu mulia berwarna ungu mengkilat. Teka-tekinya
adalah:

1. Buatlah program C kedua dengan nama "4b.c". Program ini akan
mengambil variabel hasil perkalian matriks dari program "4a.c" (program
sebelumnya), dan tampilkan hasil matriks tersebut ke layar.
(Catatan!: gunakan shared memory)
2. Setelah ditampilkan, berikutnya untuk setiap angka dari matriks
tersebut, carilah nilai faktorialnya, dan tampilkan hasilnya ke layar dengan
format seperti matriks.

Contoh: misal array [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], ...],

maka:

1 2 6 24
120 720 ... ...
...

(Catatan! : Harus menggunakan Thread dalam penghitungan
faktorial)
- Batu ketiga adalah Onyx. Batu mulia berwarna hitam mengkilat. Pecahkan
teka-teki berikut!

1. Buatlah program C ketiga dengan nama "4c.c". Program ini tidak
memiliki hubungan terhadap program yang lalu.
2. Pada program ini, Norland diminta mengetahui jumlah file dan
folder di direktori saat ini dengan command "ls | wc -l". Karena sudah belajar
IPC, Norland mengerjakannya dengan semangat.
(Catatan! : Harus menggunakan IPC Pipes)
Begitu batu terakhir berhasil didapatkan. Gemuruh yang semakin lama semakin
besar terdengar. Seluruh tempat berguncang dahsyat, tanah mulai merekah. Sebuah
batu yang di atasnya terdapat kotak kayu muncul ke atas dengan sendirinya.

Sementara batu tadi kembali ke posisinya. Tanah kembali menutup, seolah tidak
pernah ada lubang merekah di atasnya satu detik lalu.
Norland segera memasukkan tiga buah batu mulia Emerald, Amethys, Onyx pada
Peti Kayu. Maka terbukalah Peti Kayu tersebut. Di dalamnya terdapat sebuah harta
karun rahasia. Sampai saat ini banyak orang memburu harta karun tersebut.
Sebelum menghilang, dia menyisakan semua petunjuk tentang harta karun tersebut
melalui tulisan dalam buku catatannya yang tersebar di penjuru dunia. "One Piece
does exist".
```
Dalam pengerjaannya saya membuat 3 buah file script .c sesuai sub soal yang berjumlah tiga sebagai berikut :

```c
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define MOD 20
#define row 4
#define col 2
#define col2 5
 
int mat1[row][col], mat2[col][col2], res[row][col2], (*hasil)[col2];
pthread_t tid[5];
 
pid_t child;

 
void *multiply(void *arg){
    pthread_t id = pthread_self();
	int temp = 0;
 
	// for(int i=0; i<5; i++) 
	// 	if(pthread_equal(id, tid[i])){
    //         for(int j=0 ; j < 4;j++)
    //         hasil[j][4-i] = (mat1[j][i]*mat2[i][4-i]) + (mat1[j][1]*mat2[1][4-i]);
    //     }

	if(pthread_equal(id, tid[0])){
        for (int i=0; i<4; i++) {
            hasil[i][4] = (mat1[i][0]*mat2[0][4]) + (mat1[i][1]*mat2[1][4]);
        }
    }
    else if(pthread_equal(id, tid[1]))
    {
        for (int i=0; i<4; i++) {
            hasil[i][3] = (mat1[i][0]*mat2[0][3]) + (mat1[i][1]*mat2[1][3]);
        }
    }
    else if(pthread_equal(id, tid[2]))
    {
        for (int i=0; i<4; i++) {
            hasil[i][2] = (mat1[i][0]*mat2[0][2]) + (mat1[i][1]*mat2[1][2]);
        }
    }
    else if(pthread_equal(id, tid[3]))
    {
        for (int i=0; i<4; i++) {
            hasil[i][1] = (mat1[i][0]*mat2[0][1]) + (mat1[i][1]*mat2[1][1]);    
        }
    }
    else 
    {
        for (int i=0; i<4; i++) {
            hasil[i][0] = (mat1[i][0]*mat2[0][0]) + (mat1[i][1]*mat2[1][0]);
        }
    }

	return NULL;
}
 
void main(){
	key_t key = 1234;
	srand(time(NULL));
	
	int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
	// res[][] = (int*) shmat(shmid,(void*)0,0);
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			mat1[i][j] = rand()%MOD+1;
			mat2[j][i] = rand()%MOD+1;
		}
		if(i==(row-1)){
			for(int j=0; j<col; j++){
			mat2[j][i+1] = rand()%MOD+1;
			}
		}
	}
 
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			printf("%d ", mat1[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for(int i=0; i<col; i++){
		for(int j=0; j<col2; j++){
			printf("%d ", mat2[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	hasil=  shmat(shmid,NULL,0); 
	// idku hehe[row][col2];
	for(int i=0; i<5; i++){
        int err=pthread_create(&(tid[i]), NULL, &multiply, NULL); //membuat thread
		if(err!=0) //cek error
		{
			printf("\n can't create thread : [%s]",strerror(err));
		}
        
	}

	for(int i=0; i<5; i++){
		pthread_join(tid[i], NULL);
	}
 
	// printf("\n");
	// for(int i=0; i < 5; i++){
	// 		pthread_join(tid[i], NULL);
	// 		// hasil[i][j]=hehe[i][j].res;
	// }
    // printf("Matriks hasil:\n");
    for(int i=0; i<4; i++){
        for(int j=0; j<5; j++)
        {
            printf("%d ", hasil[i][j]);
        }
        printf("\n");
    }
 sleep(5);
 shmdt(hasil); 
 shmctl(shmid, IPC_RMID, NULL);
}
```
```c
#include <stdio.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
// Maximum number of digits in output 
// #define MAX 500 

int (*hasil)[5],fac[4][5];

pthread_t tid[5];

void* sum(void* p) {
   pthread_t id = pthread_self();
	int temp = 0;
 
	for(int i=0; i<5; i++) 
		if(pthread_equal(id, tid[i])){
            for(int j=0 ; j < 4;j++)
                for(int k=(int)hasil[j][4-i] ; k>0 ; k--){
                    // printf(" k: %d \n",k);
                    fac[j][4-i]+=k;
                }
        }
	return NULL;
}

// int multiply(int x, int res[], int res_size); 

// This function finds factorial of large numbers 
// and prints them 
// void* factorial(void *args) 
// { 
//     int res[MAX]; 
//     int n = (intptr_t)args;
//     // Initialize result 
//     res[0] = 1; 
//     int res_size = 1; 
  
//     // Apply simple factorial formula n! = 1 * 2 * 3 * 4...*n 
//     for (int x=2; x<=n; x++) 
//         res_size = multiply(x, res, res_size); 
  
//     // cout << "Factorial of given number is \n"; 
//     for (int i=res_size-1; i>=0; i--) 
//     printf("%d",res[i]);
//         // cout << res[i]; 
// } 
  
// This function multiplies x with the number  
// represented by res[]. 
// res_size is size of res[] or number of digits in the  
// number represented by res[]. This function uses simple  
// school mathematics for multiplication. 
// This function may value of res_size and returns the  
// new value of res_size 
// int multiply(int x, int res[], int res_size) 
// { 
//     int carry = 0;  // Initialize carry 
  
//     // One by one multiply n with individual digits of res[] 
//     for (int i=0; i<res_size; i++) 
//     { 
//         int prod = res[i] * x + carry; 
  
//         // Store last digit of 'prod' in res[]   
//         res[i] = prod % 10;   
  
//         // Put rest in carry 
//         carry  = prod/10;     
//     } 
  
//     // Put carry in res and increase result size 
//     while (carry) 
//     { 
//         res[res_size] = carry%10; 
//         carry = carry/10; 
//         res_size++; 
//     } 
//     return res_size; 
// } 
void main()
{
    key_t key = 1234;
    

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    hasil = shmat(shmid, NULL, 0);

    // printf("Program 1 : %d\n", *value);
    for(int i=0; i<4; i++){
        for(int j=0; j<5; j++)
        {
            printf("%d ", hasil[i][j]);
            // hasil[i][0]=1;
            // hasil[i][1]=2;
            // hasil[i][2]=3;
            // hasil[i][3]=4;
            // hasil[i][4]=5;
        }
        printf("\n");
    }
    printf("\n");

   	for(int i=0; i<5; i++){
        int err=pthread_create(&(tid[i]), NULL, &sum, NULL); //membuat thread
		if(err!=0) //cek error
		{
			printf("\n can't create thread");
		}
	}

    for(int i=0; i<5; i++){
        pthread_join(tid[i], NULL);
    }

    for(int i=0; i<4; i++){
        for(int j=0; j<5; j++)
        {
            printf("%d ", fac[i][j]);
        }
        printf("\n");
    }

    // int coba=1;
    // for(int res=1 ; res<=hasil[1][1] ; res++){
    //  printf("\n%d ", res);
	// 		coba=coba*res;
    //  printf("\n%d ", coba);
    // }
    // int a[1]=100;
    // factorial(a[1]);
    // printf("\n%d ", factorial(100));

        shmctl(shmid, IPC_RMID, NULL);
}
```
```c
    #include<stdio.h> 
    #include<unistd.h> 
    #include<sys/types.h> 
     
    int main() 
    { 
     
    	int pip[2];
    	pid_t p; 
     
    	if (pipe(pip)==-1) { 
    		fprintf(stderr, "Pipe Failed" ); 
    		return 1; 
    	} 
     
    	p = fork(); 
     
    	if (p < 0) 
    	{ 
    		fprintf(stderr, "fork Failed" ); 
    		return 1; 
    	} 
     
    	if (p > 0) { 
    	    // closing normal stdin 
            close(0); 

            // making stdin same as a[0] 
            dup(pip[0]); 

            // closing writing part in parent, 
            // we don't need of it at this time 
            close(pip[1]); 

            // executing wc 
            execlp("wc","wc","-l",NULL); 
    	} 
    	else if(p == 0){ 
    	    // closing normal stdout 
            close(1); 

            // making stdout same as a[1] 
            dup(pip[1]); 

            // closing reading part of pipe 
            // we don't need of it at this time 
            close(pip[0]); 

            // executing ls  
            execlp("ls","ls",NULL); 

    	} 
    } 
```

Dalam script pertama membuat sebuah program yang mengalikan dua buah matrix. Saya disini membuat sebuah matriks 4x2 dan 2x5 yang mana isinya di mod 20 kemudian ditambah 1 agar setiap angka dalam matriks adalah angka 1-20. Kemudian membuat sebuah thread yang akan mengalikan setiap angkanya dan terakhir mengirim hasil matriks ke dalam shared memory agar bisa dibaca oleh program kedua.

Dalam script kedua membuat sebuah program untuk menjumlahkan setiap angka di dalam matriks dengan angka itu sendiri dikurang 1 sampai angkanya 0. Misal 3 maka akan berubah menjadi 3+2+1+0 yaitu 6. Untuk menjumlahkan setiap angka didalam matriks saya menggunakan thread. Matriks awal didapat dari hasil program sebelumnya dengan menggunakan shared memory yang kemudia diberi jeda dengan sleep agar dapat di proses oleh program kedua ini.

Untuk script ketiga tidak ada hubungannya dengan program sebelumnya, yaitu membuat pipe. Saya menggunakan fork agar program dapat melakukan pipe yang kemudian dibantu oleh fungsi dup untuk hasilnya.

Berikut gambar ketika program dijalankan:

![soal4](https://user-images.githubusercontent.com/58405725/79046414-0363ac80-7c3b-11ea-9307-f83e066c2dbc.png)
