
name: Kanran Peng


Inpliment: the mysh will take no argument, it can preform like regular shell.
    it can run the unix build in command, such as ls, echo, touch, rm...
    it can run other executable file in the working dir
        use cd to change dir
        use pwd to show current dir
    
    wildcard: use * to replace letters, support wildcard on exe file name, argument, input file, output file

    pipe: connect 2 program together, use the first program's output as the second program's input

    then/else: check the last process's exit statues, if exit 1 else will run current exe file, if exit 0 then will run current exe file
    


Testcase: 
    1. run Unix program: tested ls, touch... 

        mysh> ls
        mysh> touch filename.txt
        mysh> cd bat   //bat and foo is for testing the cd, cd.. , pwd


    2. run simple one program with no argument, no redirection
    
        mysh> world

            world will just print one line out

    3. run program takes arguments and input and output redirection

        mysh> hello here is the arguments < a.txt > b.txt

            hello will take argv{"hello", "here", "is", "the", "argments"}
            scanf from a.txt
            then write output in b.txt


    4. run program with wildcard 

        mysh> h*O here is the argments < a*t > b*t

            this will do the same thing as 3

        
        mysh> hello *.txt < a.txt
            this will test if wild card can find all the file should be found, hello will print out it's arguments
            it shoudl be [hello] [a.txt] [b.txt] [c.txt]



    5. runprogram with pipe

        mysh> arg | pipe

            arg will output an int, and pipe will scanf an int, and print it out



    6. then else, ec will exit0, ef will exit 1

        mysh> ec
        mysh> then ef   //ef will run

        mysh> ec
        mysh> else ef  //ef will not run

        mysh> ef
        mysh> then ec   //ec will not run
    
        mysh> ef
        mysh> else ec    //ec will run

        mysh> ef
        mysh> then ec
        mysh> then ec     //ec will not run since second ec is not running


    7. oter test cases
        including use wildcard on the test 2 to 6




Makefile: 
    it will compile all codes in this folder, including the mysh.c source code, and also test files.
    make will compile:
        mysh.c        =>  mysh
        arg.c         =>  arg
        pipe.c        =>  pipe
        ec.c          =>  ec
        ef.c          =>  ef
        hello.c       =>  hello
        world.c       =>  world

