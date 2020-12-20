## ![ASK Shell](https://i.imgur.com/Sk5asn7.gif)
by Abhijeet Saha, Steven Lee, Kristoff Misquitta\
TNPG: Team ASK
---
### Features
- Can fork and execute commands
- Multiple commands at once!
- Basic Piping (only one pipe per command)
- Redirection? 
- Cd?
- 
---
### Attempted Features
---
### Bugs
- Error messages may sometimes not be displayed
- Leftover children (?)
- two ;; breaks
---
### Files & Function Headers:
#### run.c
- Handles all functions that execute commands
```
/*======== int len_arr() ==========
Inputs: char **input
Returns: Number of elements in a string array

Counts the number of elements in a string array 
Returns 0 if there are none 
====================*/

/*======== void run()  ==========
Inputs: char **args
Returns: nothing. 

Takes in arguments (first argument is the program)
Runs it in a forked child process 
====================*/

/*======== void run_pipes() ==========
Inputs: char **pipe_args
Returns: nothing.

If the command isn't a pipe, it runs the command normally
If the command is a pipe (singular) it runs the first command in 
a forked child process and pipes the stdout into the stdin of 
the second command, which is run in the parent process 
====================*/

/*======== void run_commands() ==========
Inputs: char **commands
Returns: nothing

Inputs commands, runs them sequentially 
====================*/
```
#### parse.c
- Handles all parsing functions
```
/*======== char **parse_commands() ==========
Inputs: char *line
Returns: Parsed commands

Splits line by semicolon into commands 
====================*/

/*======== char **parse_pipes() ==========
Inputs: char *command
Returns: Commands in a pipe 

Splits commands by pipe "|" 
====================*/

/*======== char **parse_args() ==========
Inputs: char *command
Returns: Parsed arguments 

Splits command into arguments.
First argument is the program. 
====================*/
```
#### main.c
- Handles making sure everything runs
```
/*======== int main() ==========
Inputs: nothing
Returns: nothing

Puts together the entire thing 
Makes the shell run
====================*/

```
