#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

#define token " \t\r\n\a"
#define token2 ";"


/*
 *CSCI 485: C-Shell
 *
 *Authors: Ian Nevills, James Laubach, James Smith
 *
 *Project: A unix shell in C
 *
 *
 *
 */

int execution(char *argv[]){// takes in a pointer of pointer array

  pid_t pd;
  pd = fork();
  if(pd == 0){
    if (execvp(argv[0],argv) < 0) {
      perror("SeaShellError!:");
      exit(1);
    } 
  }// if fork fails = error messg and exit
  
  else
    {wait(NULL);}

  
  return 0;

}

void bufferclear(char inputlineraw[]){//Takes in pointer to array
  int x=0;
  
  if(x<512){
    inputlineraw[x]='\0';
    //prepares array by replacing garbage with null characters

     x=x+1;
  }
}

void readline(char inputlineraw[]){
  
  char c;
  int x = 0;
  c=getchar();//initial priming read for while loop
  
  while(c!='\n'){//fills up inputlineraw with characters from c, up to 512 characters
    
    if(x<512){
      inputlineraw[x]=c;
    }
    
    c=getchar();//next read 
    x=x+1;
  }
  inputlineraw[x]='\0';
  printf("\n");
 
  
  
}
int parseline(char inputlineraw[]){//takes string pointer
  int i = 0;
  char *arr;
  
  char *b[512];
  if(inputlineraw[0]=='\0' || inputlineraw==NULL){//handles empty buffer
    return 0;
  }
 
  arr = strtok(inputlineraw,token2);//priming strtok for the while loop, token2=";"
  while(arr!=NULL){//fills by with tokens from arr, taken from inputlineraw
    b[i]=arr;
    arr=strtok(NULL,token2);
    i++;
  }
 
 
  int k = 0;
 
  char **c;
  char *arr1;

  char *exit="quit";
 
  while(k<i){//very large loop, uses strtok on individual elements of b and calls execute
    
    c = (char**) malloc (512);//allocate memory for c
    int l = 0;
    
    while(l<512){//allocate memory for 2d part of c
      c[l]=(char*)malloc(i+1);
     
      l++;
    }
    
    int g = 0;
    
    arr1=strtok(b[k],token);//priming read for while loop of b at index j
    
    while(arr1!=NULL){//strtok over b[k] and tokens into c
      c[g]=arr1;
      arr1=strtok(NULL,token);
      g++;
    }
    
    c[g]=NULL;//set last entry to NULL, prevents "ls cannot access directory " "" error, unsure if this is correct
    
    k++;//iterates k so that next b can be used
    
    if(strncmp(c[0],exit,4)==0){//if c[0] == "quit", exits program loop by sending 1 to status in main loop
      printf("\nGOODBYE!\n");
      return 1;
    }
    
    else{//calls execution
      
      execution(c);
      printf("\n");
      }
 
       
      
     
    free(c);//deletes c so that previous commands no longer exist
  }
  
  return 0;

}

void ShelLoop(void)//contains driver loop
{
    int bit = 512;  
    char inputlineraw [bit];
    int status=0;

   

    
    while(status==0){//main diver loop
      bufferclear(inputlineraw);
      printf ("SeaShell>>>");
      readline(inputlineraw);
      
      status=parseline(inputlineraw);
     
      printf("\n");
    }
    
}

int main(int argc, char *argv[]){
  if(argv[1]!=NULL){//file call
    FILE *ptr;
    char *a;
    a = (char*) malloc(512);
    char *b;
    b = strtok(argv[1],"[]");
   
    if(fopen(b,"r")==NULL){
        printf("Error: File not found\n");
	exit(1);
      }
    ptr=fopen(b,"r");
    
    fgets(a,512,ptr);
   
    fclose(ptr);
    
    parseline(a);
  }
  else{//interactive call
    ShelLoop();

  }


    return EXIT_SUCCESS;
}
