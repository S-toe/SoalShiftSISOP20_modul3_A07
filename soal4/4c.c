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