#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <unistd.h> 
#include <string.h> 

void error(){
  printf("Wrong command, try another one\n"); 
}
void execute(char  *arr[64]){
  pid_t pid; 

  pid = fork(); 

  if( pid > 1){
    //   waitpid(pid, NULL, 0); 
  }
 
  if(pid ==  0){           
    //   printf("\nin child\n");           
   if(execvp(arr[0], arr)==-1)
          error(); 
  } 
}

void parse(char *ln[64], int num){ 
    int ii; 
    char *s=" \t\n";    
    char *token;         
    char *arr[64]; 
    int n=0; 
    
    int nm=0;
 
 for(ii=0; ii<num; ii++){

    token= strtok(ln[ii],s);  
     
    while(token != NULL ){                                              

      arr[n] = token;             
      n++; 
      token= strtok(NULL,s); 	            
    }    
  
  n++;   
  arr[n-1]= NULL;     
  execute(arr); 
  n=0;
 
  
 }//end for 
while( nm != num) {
    wait(NULL);  
    nm++;
    //printf("%d\n", nm); 
 }
}


void parseComma(char *ln){ 
  char *sm=";\n"; 
  char *token;
  int num=0; 
  char * argv[64]; 

  token = strtok(ln,sm);  
  
 while(token != NULL ){                                                                    
      argv[num]=token;
      num++;      
      token= strtok(NULL,sm); 	  
 }

 if(strcmp(argv[0], "exit")==0){
    printf("Good-bye!\n");
    exit(0); 
 }

  parse(argv, num);           
}

int main (int argc, char *argv[]) {

  if(argc > 1){

    FILE *fp; 

    char line[1024]; 

    fp= fopen(argv[1], "r"); 
    
    if(fp==NULL){
      perror("Error in file");
      return(-1);
    }
   
   while(fgets(line, sizeof(line), fp)){
    
     parseComma(line);
   
   }// end while 
 }
else{

   char line[1024]; 

   printf("\nCommand -> "); 

   while(fgets(line, sizeof(line), stdin)){
    
   parseComma(line);
   
   printf("Command -> "); 
  
   }
 }//end else 

}//end main
  
