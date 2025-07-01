# minishell

## Introduction

**minishell** is a simplified Unix shell implementation in C. It is designed to help understand how fundamental components of a shell work, such as parsing commands, managing processes, and handling input/output.

## Concepts and How minishell Works

### 1. Tokenization

- **Tokenization** is the first step after reading user input.
- The shell splits the command line into meaningful pieces called tokens (e.g., command names, arguments, operators like |, <, >).
- It handles quotes (`'`, `"`) so that arguments with spaces are kept together.
- Example:  
  Input: `echo "Hello World" | grep Hello > out.txt`  
  Tokens: `echo`, `"Hello World"`, `|`, `grep`, `Hello`, `>`, `out.txt`

### 2. Parsing

- After tokenization, minishell parses the tokens to understand the command structure.
- It builds a representation (like a tree or list) to know what the user wants:  
  - Which are commands
  - What arguments they have
  - Where pipes or redirections are used

### 3. Processes and Execution

- For each command (especially when separated by pipes), minishell creates one or more processes using `fork()`.
- The shell distinguishes between:
    - **Built-in commands** (like `cd`, `exit`) which run in the shell process itself
    - **External commands** (like `ls`, `grep`) which require creating a new child process
- For external commands, minishell:
    1. Forks a new process
    2. In the child, replaces the process image with the command using `execve()`
    3. The parent waits for its children to finish

### 4. Pipes

- Pipes (`|`) allow the output of one command to become the input of the next.
- minishell sets up a pipe (using `pipe()`) between the processes.
- It redirects the standard output (`stdout`) of the left command to the pipe's write end, and the standard input (`stdin`) of the right command to the pipe's read end.
- Example:  
  `ls | grep .c`  
  - `ls` writes its output into the pipe  
  - `grep .c` reads that output as input

### 5. Redirections

- minishell supports input (`<`), output (`>`) and append (`>>`) redirections.
- Before executing a command, it sets up file descriptors so input/output goes to or from the right files.

### 6. Environment Variables

- minishell keeps track of environment variables.
- You can use and modify them with `export`, `unset`, etc.
- Commands can access variables using `$VAR` syntax, which minishell expands before execution.

### 7. Signal Handling

- minishell manages signals like `Ctrl+C` (SIGINT) for interruption, mimicking standard shells.

### 8. Error Handling

- Errors in parsing, execution, or system calls are reported clearly to the user.

## Summary

minishell is an educational project that demonstrates:
- How to split and interpret user input
- How to manage processes and connect them with pipes
- How to handle file redirections, environment variables, and signals
- The basics of building a command-line shell from scratch in C
