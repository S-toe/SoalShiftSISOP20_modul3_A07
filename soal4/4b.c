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
		else
		{
			pthread_join(tid[i], NULL);
		}
        
	}

    for(int i=0; i<4; i++){
        for(int j=0; j<5; j++)
        {
            printf("%d ", (fac[i][j])/(j+1));
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