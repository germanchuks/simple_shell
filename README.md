# C - Simple Shell

## Description
This Simple Shell project is a simple implementation of the UNIX command-line interpreter. This project aims to develop a basic shell capable of executing user-provided commands. Its fundamental functionality is executing simple commands, but also incorporates additional features including support for command-line arguments, PATH management, essential built-in commands like exit and env, variable handling, logical operators, and more advanced functionalities like alias management, custom getline function, and file input processing.

### File Usage
File Name | Description
--- | ---
[alias_manager.c](https://github.com/germanchuks/simple_shell/blob/master/alias_manager.c) | Contains functions that are part of the shell's functionality to manage aliases and provide command history features.
[cmd_util.c](https://github.com/germanchuks/simple_shell/blob/master/cmd_util.c) | Handles external commands found in the PATH and identifies built-in commands.
[custom_str_manipulation.c](https://github.com/germanchuks/simple_shell/blob/master/custom_str_manipulation.c) | Contains custom string manipulation functions used within the shell program to perform various string operations, such as searching for characters, copying substrings, and concatenating strings.
[env_operation_handlers.c](https://github.com/germanchuks/simple_shell/blob/master/env_operation_handlers.c) | Contains actual implementation of functions which allow the shell program to interact with and manipulate environment variables, such as initializing new variables, modifying existing ones, and removing variables from the environment.
[env_variable_manager.c](https://github.com/germanchuks/simple_shell/blob/master/env_variable_manager.c) | Manages/calls functions which allow the shell program to manage environment variables, including initializing, modifying, deleting, displaying, and retrieving specific variables by name.
[history_manager.c](https://github.com/germanchuks/simple_shell/blob/master/history_manager.c) | Manages the shell's command history, allowing users to save and load previous commands.
[input_manager.c](https://github.com/germanchuks/simple_shell/blob/master/input_manager.c) | Reads and processes user input in the shell.
[linked_list_operations.c](https://github.com/germanchuks/simple_shell/blob/master/linked_list_operations.c) | Contains functions used to manage linked lists of strings.
[linked_list_utils.c](https://github.com/germanchuks/simple_shell/blob/master/linked_list_utils.c) | Contains functions provide various utilities for working with linked lists of items containing both string and numerical data, used to manage environment variables and history entries in the shell program.
[main.c](https://github.com/germanchuks/simple_shell/blob/master/main.c) | The main function of the shell program which serves as the entry point. It handles file redirection for shell commands.
[memory_management.c](https://github.com/germanchuks/simple_shell/blob/master/memory_management.c) | Contains utility function that is used to safely free memory pointed to by a pointer and then set the pointer itself to NULL.
[memory_utils.c](https://github.com/germanchuks/simple_shell/blob/master/memory_utils.c) | Contains functions which handles memory reallocation, filling a memory block with a byte value, and deallocating memory used by a string array and its strings.
[output_handlers.c](https://github.com/germanchuks/simple_shell/blob/master/output_handlers.c) | This file contains functions for printing strings and characters to file descriptors, including error messages.
[shell_cmd_processing.c](https://github.com/germanchuks/simple_shell/blob/master/shell_cmd_processing.c) | Contains functions for expanding command aliases, handling command chaining, and replacing variables with their values in the shell program. 
[shell_cmds.c](https://github.com/germanchuks/simple_shell/blob/master/shell_cmds.c) | Contains some built-in shell commands, including as exiting the shell, changing the current directory, and displaying help information.
[shell_info_manager.c](https://github.com/germanchuks/simple_shell/blob/master/shell_info_manager.c) | Contains functions which handle initializing, freeing, and clearing the data_t structure, which holds shell-related information, including command-line arguments, environment variables, and aliases.
[shell_main_loop.c](https://github.com/germanchuks/simple_shell/blob/master/shell_main_loop.c) | Contains functions related to running the main loop of the custom shell program, searching for and executing built-in commands, and locating and executing external executable commands.
[shell_output_utils.c](https://github.com/germanchuks/simple_shell/blob/master/shell_output_utils.c) | Contains utility functions for working with strings and printing to the standard output.
[shell.h](https://github.com/germanchuks/simple_shell/blob/master/shell.h) | The header file containing all function prototypes, macro definitions, data structures and the standard libraries used.
[str_conv_and_printing.c](https://github.com/germanchuks/simple_shell/blob/master/str_conv_and_printing.c) | Contains utility functions for string manipulation, error handling, and converting strings to integers. 
[str_manipulation_utils.c](https://github.com/germanchuks/simple_shell/blob/master/str_manipulation_utils.c) | Contains string manipulation functions such as comparing strings, concatenating strings, calculating the length of a string, and checking if a string starts with a specified substring.
[str_tokenization.c](https://github.com/germanchuks/simple_shell/blob/master/str_tokenization.c) | Cntains functions which handle tokenizing strings into words. 
[str_utils.c](https://github.com/germanchuks/simple_shell/blob/master/str_utils.c) | Contains utility functions for handling characters and strings, including checking if a character is an alphabet, converting string to integer, handling negative numbers, checking if a character is a delimeter, and checking if the shell is running in interactive mode. 

### Built-in Commands
The commands listed below are located in the `/bin/` path:

Command Name | Description
--- | ---
`env` | Displays the current environment variables
`setenv` | Creates or updates environment variables
`unsetenv` | Deletes an environment variable
`cd` | Changes the current working directory
`history` | Lists previously executed commands
`alias` | Lists all defined aliases
`help` | Shows the help documentation
`exit` | Terminates the shell

### Special Conditions
* The semicolon `;` acts as a command separator.
* Logical operators `||` and `&&` are supported in command lines.
* Special variables `$?` and `$$` are supported for variable replacement.
* `Ctrl+C` does not exit the shell; instead, it is treated as an `Enter` keypress.
* `#` are supported in command lines to identify comments.

### Compilation
```
$ gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
```

### Run
```
$ ./hsh
```

### Examples
`Interactive Mode`
```
$ cat test_ls_2
/bin/ls
/bin/ls
```

`Non-Interactive Mode`
```
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
```

### Bugs
No known bugs.

## Authors
* **Michael Chukwunwe** (https://github.com/stuckwithprogression)
* **German Daniel** (https://github.com/germanchuks)
