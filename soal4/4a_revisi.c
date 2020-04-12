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