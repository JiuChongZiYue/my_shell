#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>




typedef struct Pros {
   char* proname;
   char** proargv;
   char* proin;
   char* proout;

   int isthenelse;
   int isin;
   int isout;
} Pro;


int wildcard (char*** strli, char* target, int starLocation, int strlenAfter, int strlenBefore, char* strA, char* strB){
    // check for wildcards
    //int returnval = 0;
    char** strlist = *strli;


    char cwd [100] ;
    getcwd(cwd, 100);
    //printf("current path is: %s\n", cwd);

    DIR* dir = opendir (cwd);


    struct dirent* entity;
    entity = readdir(dir);

    int howMany = 0; // how many match find

    int strlistLast = 0; //the NULL line 


    for (int i = 0; strlist[i] != NULL; i++){
        //printf ("current i is %d, this is how many lines in strlist", i);

        strlistLast = i;
    }


    while (entity != NULL){
        //printf("%s\n",entity->d_name);

        char* filename = entity->d_name;

        char temp[100];

        int beforeMatch = strncmp(filename, strB, strlen(strB)  );

        // find last letters of filename

        int xx = 0;

        while (xx < strlenAfter){
            // grab the last strlenafter letter in to a new str

            temp [xx] = filename [strlen(filename) - strlenAfter + xx];
            temp [xx +1] = '\0';

            xx++;
        }

        int afterMatch = strcmp(temp, strA  );

        //printf("first match is %d, second match is %d\n" , beforeMatch, afterMatch);

        if ( beforeMatch == 0 && afterMatch == 0){
            if (howMany == 0){
                //we find the first match 
                howMany +=1;

                strlist[starLocation] = realloc(strlist[starLocation], strlen(filename) + 5);

                strcpy (strlist[starLocation] , filename);

            }else{
                howMany +=1;
                strlist[strlistLast] = (char*) malloc ( (strlen(filename) + 5) * sizeof(char)         );

                strcpy (strlist[strlistLast] , filename);
                strlist[strlistLast + 1] = NULL;

                strlistLast += 1;
            }
        
        }








        entity = readdir(dir);
    }

    return howMany;

}


int isstar (char*** strli){
    //check if there is * in a string
    int returnval = 0;
    
    char *ret;

    // ret = (char* ) malloc (100 * sizeof(char));
    // ret[0] = '\0';

    

    char** strlist = *strli;

    //printf("\n\n\nnow in the isstar\n");

    
    int i = 0;
    while (strlist [i] != NULL){

        //printf("134                                     the i in strlist is [%s]\n", strlist[i]);


        ret = strchr(strlist[i], '*');

        //printf("111111 ret is %s\n", ret);

        // if ret is "\0", no * in there

        if ( ret == NULL    ){
            // ret is "\0", do nothing
            //printf("ret is 0\n");



        }else{
            // call wildcard
            int retlen = strlen (ret);
            int strlenAfter = retlen - 1;
            int strlenBefore = strlen(strlist[i]) - retlen;
            char strB [100] = "\0";
            char strA [100] = "\0";

            for (int j =0; j < strlenBefore; j++){
                // str before *
                strB[j] = strlist[i][j];
                strB[j + 1] = '\0';
            }
            int jj = 0;
            for (int j = strlen(strlist[i]) - retlen + 1 ; j < strlen(strlist[i]) ; j++){
                // str after *
                strA[jj] = strlist[i][j];
                strA[jj + 1] = '\0';
                jj++;
            }

            returnval = wildcard (strli,    strlist[i], i, strlenAfter, strlenBefore, strA, strB );
        }

        
        i++;
    }


    return returnval;
}



int main(int argc, char *argv[]) {
    //this is how to read commands
    char command [100];
    char buff;
    char tokenArray[100][100];

    int exitStaue = 0;  // check if anything went wrong during running the code
    int exitStaue1 = 1; // check if exit by exit command


    for (int tutu = 0; tutu < 100; tutu ++){
        tokenArray[tutu][0] = '\0';
    }
    

    
    //int x = 1; // become 0 when recieve "exit\n" command

    printf("Welcome to mysh!\n");

    while(exitStaue1){
        //printf("%d\n", exitStaue1);
        //begin the new command recursive mode 
        for (int tutu = 0; tutu < 100; tutu ++){
            //empty tokenArray
            tokenArray[tutu][0] = '\0';
        }
    
  

        printf("mysh> ");
        if (fgets(command, 100, stdin) == NULL) {
            break;
        }

        //printf("the new command is %s\n", command);

        if (command[0] == 'c' && command[1] == 'd' && command[2] == ' '){
            // receive cd  try to open the name after it 


            //printf(" in the check\n");
            char newDir [100] = "\0";
            char d = ' ';
            int i = 3;
            d = command[i];
            while (d != '\n'){
                
                
                strncat(newDir, &d, 1);
                
                i++;
                d = command[i];
            }

            //printf("[%s]\n", newDir);
            int dirExist = chdir(newDir);

            if (dirExist == 0){
                printf("change dir successed\n");

            }else if (dirExist == -1){
                printf("WARNING: change dir failed\n");
                exitStaue =1;
            }
            
            continue;


        }else if (strcmp ("exit\n", command) == 0){
            // receive the exit command, break the loop
            exitStaue1 = 0; // correct exit

            printf("THANK YOU! GOOD BYE!\n");
            break;
            
        }else if (strcmp ("pwd\n" , command) == 0){
            // receive pwd, show the path
            char cwd [100];
            printf("current path is: %s\n", getcwd(cwd, 100));
            continue;

        }




        int ii = 0;
        int jj = 0;
        int totalProcessNeed = 1;


        char x = command[0];
        while (x != '\n'){
            // this is the loop we make tockenArray

            if (  isalpha(x) || x == '*') {
                //read a letter keep read to till meet non letter
                
                strncat(tokenArray[jj], &x, 1);
                ii +=1;
                x = command [ ii ];

                while ( isalpha(x) || (x == '.' )   || x == '*'     ){
                     
                    strncat(tokenArray[jj], &x, 1);
                    ii ++;
                    x = command [ii];
                }


                //printf("1 %d[%s]     x holding [%c], jj holding line %d\n" ,jj, tokenArray[jj], x, jj);
                jj +=1; // tokenArray move to new line
                continue;


            }else if( x == '<'){
                // get < new token
                strncat (tokenArray [jj], &x, 1);
                jj +=1;
                ii +=1;
                //printf("2 %d[%s]     x holding [%c], jj holding line %d\n" ,jj, tokenArray[jj], x, jj);

            }else if(x == '>'){
                //strncat (tokenArray [jj], &x, 1);

                tokenArray[jj][0] = '>'; 
                tokenArray[jj][1] = '\0';
                jj +=1;
                ii ++;

                //printf("3 %d[%s]     x holding [%c], jj holding line %d\n" ,jj, tokenArray[jj], x, jj);

            }else if (isspace(x)){
                ii ++;

                //printf("4 %d[%s]     x holding [%c], jj holding line %d\n" ,jj, tokenArray[jj], x, jj);
            }else if(x == '|') {
                tokenArray[jj][0] = '|'; 
                tokenArray[jj][1] = '\0';
                jj +=1;
                ii ++;
                totalProcessNeed +=1;
            }


            x = command [ ii ];


        }

        // printf("331                         out of token loop of making tokens\n");

        // for (int c = 0; c < jj; c++){
        //     printf("total    %d [%s]\n",c,  tokenArray[c]);
        // }

        // got all the tokens









        Pro pro[totalProcessNeed];

        for (int f = 0; f < totalProcessNeed; f++){
            pro[f].isthenelse = 0;
            pro[f].isin = 0;
            pro[f].isout = 0;
        }

        int xxx = 0;// going thought the tokenArray


        for (int cc = 0; cc < totalProcessNeed; cc++){
            // making the struct pro for each process
            
            if ((strcmp (tokenArray[xxx], "then" )   != 0 ) &&        (strcmp (tokenArray[xxx], "else" )   != 0 )                ){
                //set the pro name

                pro[cc].proname = (char*)malloc (sizeof(char) *50);
                strcpy (pro[cc].proname,  tokenArray[xxx]      );

                //printf("set proname to [%s]\n", pro[cc].proname);

                char** proname ;

                proname = (char**)malloc(2*sizeof(char*));

                proname[0] = pro[cc].proname;
                proname[1] = NULL;

                //printf("try to do proname [%s] [%s]", proname[0], proname[1]);

                isstar(   &proname   );
                


                int argvcount = 0;
                pro[cc].proargv = (char**)malloc(sizeof(char*)*50);
                pro[cc].proargv[0] = NULL;



                pro[cc].proargv[argvcount] = (char*)malloc(sizeof(char)*50);
                strcpy (pro[cc].proargv[argvcount], tokenArray[xxx]);


                argvcount ++;

                xxx +=1;


                while (  (0 != strcmp(tokenArray[xxx], "<"))   && (0 != strcmp(tokenArray[xxx], ">") )    && (0 !=strcmp(tokenArray[xxx], "|") )              ){
                    // next not < or > or |     edit proargv s

                    if (  0 == strcmp (tokenArray[xxx], "\0")){
                        break;
                    }
                    pro[cc].proargv[argvcount] = (char*)malloc(sizeof(char)*50);



                    //printf("token argv is %s\n",tokenArray[xxx]);
                    strcpy (pro[cc].proargv[argvcount], tokenArray[xxx]);
                    


                    //printf("the cc is %d, argcacont is %d,   inside is [%s]\n", cc, argvcount, pro[cc].proargv[argvcount]);
                    argvcount +=1;


                    pro[cc].proargv[argvcount] = NULL;

                    xxx+= 1;


                }

                isstar(   &(pro[cc].proargv) );


                //printf ("216 [%s]\n", tokenArray[xxx]);

                if ((0 == strcmp(tokenArray[xxx], "<"))){
                    pro[cc].proin = (char*)malloc(sizeof(char)*50);
                    xxx+=1;
                    pro[cc].isin = 1;
                    strcpy (pro[cc].proin, tokenArray[xxx]);

                    //printf("stdin [%s]\n", pro[cc].proin);
                    xxx +=1 ;

                    char** proinput ;

                    proinput = (char**)malloc(2*sizeof(char*));

                    proinput[0] = pro[cc].proin;
                    proinput[1] = NULL;

                    //printf("442 try to do proname [%s] [%s]", proinput[0], proinput[1]);

                    isstar(   &proinput   );

                }

                //xxx+=1;


                if ((0 == strcmp(tokenArray[xxx], ">"))){
                    pro[cc].proout = (char*)malloc(sizeof(char)*50);
                    xxx+=1;
                    pro[cc].isout =1;
                    strcpy (pro[cc].proout, tokenArray[xxx]);
                    //printf("               stdout [%s]\n", pro[cc].proout);
                    xxx +=1;





                    char** prooutput ;

                    prooutput = (char**)malloc(2*sizeof(char*));

                    prooutput[0] = pro[cc].proout;
                    prooutput[1] = NULL;

                    //printf("470 try to do proname [%s] [%s]", prooutput[0], prooutput[1]);

                    isstar(   &prooutput   );

                }



                if ((0 == strcmp(tokenArray[xxx], "<"))){
                    pro[cc].proin = (char*)malloc(sizeof(char)*50);
                    xxx+=1;
                    pro[cc].isin = 1;
                    strcpy (pro[cc].proin, tokenArray[xxx]);

                    //printf("2 %d stdin [%s]\n", xxx, pro[cc].proin);
                    xxx+= 1;





                    char** proinput ;

                    proinput = (char**)malloc(2*sizeof(char*));

                    proinput[0] = pro[cc].proin;
                    proinput[1] = NULL;

                    //printf("498 try to do proname [%s] [%s]", proinput[0], proinput[1]);

                    isstar(   &proinput   );

                }



                if ((0 == strcmp(tokenArray[xxx], "|"))){

                    xxx+=1;

                }
            }
            else{
                // the first word in command is "then" or "else"
                // we read then or else

                // set isthenelse, if it is then, set to 1      ; if it is else set to 2     ; if not set it is 0;
                if (   strcmp (tokenArray[xxx], "then" ) == 0     ){
                    //read then, 1

                    pro[cc].isthenelse = 1;
                }
                if (    strcmp (tokenArray[xxx], "else" ) == 0    ){
                    //read else, 2
                    pro[cc].isthenelse = 2;
                } 
                xxx++; cc--;
            }









        }





        int y = 0 ;
        int j = 0; // track which line we are in

        int wstatus; //check last child process exit status

        // printf("totalProcessNeed is %d\n", totalProcessNeed);





        // creat 2 pipes
        int fd[2];

        if (pipe(fd) == -1 ){
            printf("WARNING: pipe not work\n");
            exitStaue = 1;
        }

        

        while (y < totalProcessNeed){
            // try to open a different process 

            

            int id = fork();
            if ( id == 0 ){
                // here is the child process 

                if (pro[y].isthenelse == 1){
                    // then, only run when last one success, need successful == 0
                    int successful = WIFEXITED(wstatus) && WEXITSTATUS (wstatus);
                    if (successful != 0){
                        // last child failed, skip this child

                        printf("WARNING: recieve then, but last child failed, skip this code\n");

                        j ++;

                        y +=1;
                        exit(1);
                        //continue;

                    }
                }

                if (pro[y].isthenelse == 2){
                    // else, only run when last one failed, need successful == 1
                    int successful = WIFEXITED(wstatus) && WEXITSTATUS (wstatus);
                    if (successful != 1){
                        // last child failed, skip this child
                        printf("WARNING: recieve else, but last child successed, skip this code\n");

                        j ++;

                        y +=1;
                        exit(1);
                        //continue;

                    }
                }
            
                






                //printf("we are in the child, curren j is %d    pro name is [%s]\n", j,pro[y].proname);
                char setName[100] = "\0";
                strncat (setName, pro[y].proname, 97);

                //printf("the program name is [%s][%d][%d]\n", setName, pro[y].isin, pro[y].isout  );

                char setStdinName[100];
                setStdinName[0] = '\0';



                if (totalProcessNeed > 1 && ( y%2 == 0)    ){
                    // there are more than 1 programs, we must use pipe
                    //we are in the first program, use the pipe[1] to write outputs
                    dup2(fd[1], 1);

                }
                

                if (totalProcessNeed > 1 && ( y%2 == 1)    ){
                    // there are more than 1 programs, we must use pipe
                    //we are in the second program, use the pipe[0] to read inputs
                    dup2(fd[0], 0);

                }
                



                if (pro[y].isin == 1 ){
                    // need to change stdin

                    //printf(" we are in the stdin,  [%s]\n", pro[y].proin);
                    
                    strncat (setStdinName, pro[y].proin, 97);
                    int chStdinFile = open(setStdinName, O_RDONLY);

                    if (chStdinFile == -1){
                        return -1;
                    }

                    dup2(chStdinFile, 0);
                }



                setStdinName[0] = '\0';
                if (pro[y].isout == 1){
                    // need to change stdout

                    //printf(" we are in the stdout, [%s]\n", pro[y].proout);
                    char setStdoutName[100] = "\0";
                    setStdoutName[0] = '\0';
                    strncat (setStdoutName, pro[y].proout, 97);

                    int chStdoutFile = open(setStdoutName, O_WRONLY | O_CREAT | O_TRUNC, 0640);


                    if (chStdoutFile == -1){
                        return -1;
                    }

                    dup2(chStdoutFile, 1);
                }


                //printf("set name is [%s]   stdin [%s]    stdout[%s]\n", setName, pro[y].proin, pro[y].proout);

                // result  != -1 if the exe file is in curren dir
                int result = execv( setName, pro[y].proargv );



                if (result == -1){
                    // exe file not in local dir, need to look into 3 bin
                    
                    char tryname[100]  = "/usr/local/bin/\0";

                    strcat(tryname, setName);
                    
                    int changeResult = access(tryname , F_OK);

                    if (changeResult ==-1){
                        // look in second bin
                        strcpy(tryname , "/usr/bin/\0" );
                        strcat(tryname, setName);
                    
                        int changeResult = access(tryname , F_OK);

                        if (changeResult == -1){
                            // look in third bin

                            strcpy(tryname , "/bin/\0" );
                            strcat(tryname, setName);
                    
                            int changeResult = access(tryname , F_OK);

                            if (changeResult == -1){
                                printf ("WARNING: file name [%s] not found\n", setName);
                                exitStaue = 1;
                                exit(1);
                            }



                        }

                    }


                    char currenCwd [100];


                    //printf("the cwd is :[%s]\n", getcwd(currenCwd, 100));
                    //printf("%s\n", tryname);

                    result = execv( tryname, pro[y].proargv  );
                }

                

            }else{
                //printf("we are in the parent \n");
                wait(&wstatus);
            }
            
            
            j ++;

            y +=1;
        }




        for (int tutu = 0; tutu < 100; tutu ++){

            //clean up the command
            tokenArray[tutu][0] = '\0';
        }


    }


    return exitStaue;
}