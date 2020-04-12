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