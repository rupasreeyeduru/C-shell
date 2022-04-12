Executing:

make

./a.out

----

cd.c contains cd function which handles different cases of cd

echo.c contains echo function which prints the ouput removing spaces,tabs

exec.c contains exec,Sig,fg,bg,signals,Ctrlz,Ctrlc functions 
 - exec uses fork,execvp,wait etc to handle foreground and background processes
 - Sig uses kill to send a signal to a process
 - fg implements fg id command
 - bg implements bg id command
 - signals intializes signals
 - Ctrlc signal handler function fot CtrlC
 - Ctrlz signal handler function for CtrlZ
headers.h contains all headers required

input.h declares struct matrix which stores array of arguments and no of arguments

input.c contains tokenize commands,tokenize input and execute functions(repeat included here):
  - tokenize input seperates input into commands based on ;
  - tokenize commands seperates arguments based on " "
  - execute calls function required to execute a command based on its arguments
  
jobs.c contains intializejobs,addjob,jobs :
  - jobs implement jobs command,addjob adds new job to joblist,intializejobs intializies joblist
jobs.h declares struct jobs

ls.c contains ls function which handles different cases of ls

main.c calls intializejobs,signals, prompt and takeinput function:
  - struct path stores previouspath,homepath and current path of shell reuired to change directories
  
pinfo.c  contains pinfo function which prints information about a process such as pid,status etc

pipeline.c contains pipeline function whichimplements pipelining

redirect.c containd redirect function which handles input/output redirection

prompt.c contains prompt_print dunction which prints username,machinename and current directory of shell
prompt.h declares struct path

pwd.c contains pwd function which shows present working directory.

Assuming max no of tokens and argument length as 100
