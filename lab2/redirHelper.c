void redirInput(char *input);
void redirOutput(char *input);
int checkForCd (char *cmd);
int printWolfie();
int checkForWolfie();
int checkForExit (char *cmd);
#define MAX_INPUT_BUFF_BUFF 1024
/**
*redirInput small method for handling input redirection
**/
void redirInput(char *input) {
	FILE *fd = fopen(input, "ab+");
	#define MAX_INPUT_BUFF_BUFF 1024
	int fd_in = fd->_fileno;
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
}

int checkForCd (char *cmd){
  char *cursor = NULL;

  char cwd[MAX_INPUT_BUFF_BUFF];
  char cmdTemp[MAX_INPUT_BUFF_BUFF];

  char *theCWD = getcwd(cwd,sizeof(cwd));
  if (strncmp("cd\n",cmd,2) == 0){
    cursor = cmd; //Make a cursor to the CMD string
    cursor += 3; // Move the cursor past 'cd ' onto the argument for CD
    strcpy( cmdTemp , cursor ); // Copy the value at location into the cmdTemp string (this now holds CD arguments)
    cursor = cmdTemp; // The copied over value still has '\n' so we make a cursor it
    cursor += strlen(cmdTemp)-1; // Move the cursor to the end -1 (The location of the '\n')
    *cursor = '\0';  // Replace the '\n' with Null terminator
  if (strcmp( cmd , "cd\n") == 0){ // Base case CD needs to implement root CD
      chdir(getenv("HOME"));
      theCWD = getcwd (cwd,sizeof(cwd));
      cursor = theCWD + strlen(theCWD);
      *cursor = ' ';
      cursor++;
      *cursor = '\0';
  } else if ( chdir ( cmdTemp ) < 0){
          printf("ERROR OPENING DIRECTORY:%s \n",cmdTemp);
          return 1;
          } else {
                    theCWD = getcwd (cwd,sizeof(cwd));
                    cursor = theCWD + strlen(theCWD);
                    *cursor = ' ';
                    cursor++;
                    *cursor = '\0';
                    printf("Success changing.. New CWD %s \n",theCWD);
                  }

  return 0;
  } else return 1;

}

int checkForExit (char *cmd){
  char *EXIT_CMD =  "exit\n";
  if(!strncmp(cmd,EXIT_CMD,4)) {
    exit(0);
    return 0;
  }
  return 1;
}


int printWolfie(){
  char wolfieBuffer[255];
  char *colors[] = {"\x1B[0m","\x1B[31m","\x1B[32m","\x1B[33m","\x1B[34m","\x1B[35m","\x1B[36m","\x1B[37m"};
  FILE * fd;
  if ((fd = fopen("catWolfieSAFE.txt","r")) < 0){
    printf("Error opening");
    return 1;
  }
  //fgets(wolfieBuffer,125,fd);
  int index =1;
  int iterator =0;
  int colorCounter =0;
  srand(time(NULL));
  while(index != 0){
    for (iterator =1;iterator < 24;iterator++){

    printf("\n");
    }
    for (iterator =1;iterator < 24;iterator++){
    colorCounter = rand() % 8;
    index = (int) fgets(wolfieBuffer,125,fd);
    if(index!=0){

    printf("%s%s",colors[colorCounter] ,wolfieBuffer);
    }
    }

    sleep(1);
  }
    return 0;
}

int checkForWolfie(char *buff){

	if (!strcmp(buff,"wolfie\n")){
		printWolfie();
		return 0;
	} else return 1;
}
/**
*redirInput small method for handling input redirection
**/
void redirOutput(char *input) {
	FILE *fd = fopen(input, "ab+");
	int fd_in = fd->_fileno;
	dup2(fd_in, STDOUT_FILENO);
	close(fd_in);
}
