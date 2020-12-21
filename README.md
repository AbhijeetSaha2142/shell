## ![ASK Shell](https://i.imgur.com/Sk5asn7.gif)
by Abhijeet Saha, Steven Lee, Kristoff Misquitta\
TNPG: Team ASK

### Features
- Can fork and execute commands
- Multiple commands at once!
- Basic Piping (only one pipe per command)
- Redirection? 
- Homemade cd and exit 
---
### Attempted Features
- Double redirection, but doesn't work. 
- Pipe chaining, but didn't work, so removed.
---
### Bugs
- Error messages may sometimes not be displayed
- Double redirection (ex. cat < makefile > out.txt) does not work (results in a seg fault)
- two ;; breaks
- Not really a bug but limited to 100 characters per line. 
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

/*======== void run_redirs() ==========
Inputs: char **commands, char *args
Returns: nothing

Inputs commands and args (args are > and < in a string).
Handles redirections by setting stdin and stdout to files. 
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
/*======== int count_tokens() ==========
Inputs: char *line, char symbol
Returns: Number of tokens

Counts number of tokens separated by symbol
====================*/

/*======== char *trim() ==========
Inputs: char *str
Returns: str without the spaces at beginning and end

Removes spaces at beginning and end of str.
Note str has to be mutable.
====================*/

/*======== char **parse_commands() ==========
Inputs: char *line
Returns: Parsed commands

Splits line by semicolon into commands 
====================*/

/*======== char **parse_redirs() ==========
Inputs: char *command
Returns: Parsed by < and > 

Splits line by > and <
====================*/

/*======== char *parse_redirs2() ==========
Inputs: char *command
Returns: >s and <s

Returns the >s and <s in order in a string. 
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
