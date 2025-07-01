# minishell

## Introduction

**minishell** is a simplified Unix shell implemented in C. It demonstrates how a shell works at a fundamental level, including parsing commands, managing processes, connecting commands with pipes, and handling input/output redirection.

---

## Concepts and How minishell Works

### 1. Tokenization

- minishell reads the user's command line input and splits it into tokens (words and operators).
- It handles quotes so that text inside `'` or `"` is treated as one piece.
- Example:  
  Input: `echo "Hello World" | grep Hello > out.txt`  
  Tokens: `echo`, `"Hello World"`, `|`, `grep`, `Hello`, `>`, `out.txt`

### 2. Parsing

- After tokenization, minishell organizes the tokens to understand the structure:  
  - Which are commands  
  - Their arguments  
  - Where pipes or redirections are used
- Parsing creates an internal representation so the shell knows how to execute the command chain correctly.

### 3. Processes and Execution

- minishell uses `fork()` to create new processes for commands.
- **Built-in commands** (like `cd`, `exit`) are handled directly in the shell process.
- **External commands** (like `ls`, `grep`):  
    1. minishell forks a child process  
    2. The child process runs the command with `execve()`  
    3. The parent waits for the child to finish

### 4. Pipes

- Pipes (`|`) let the output of one command be the input of another.
- minishell sets up pipes using `pipe()`.
- It connects the standard output of the left process to the standard input of the right process.

### 5. Redirections

- minishell supports redirections:
  - Input: `< file`
  - Output: `> file`
  - Append: `>> file`
- It adjusts file descriptors before running a command so input or output is read/written from the correct file.

### 6. Environment Variables

- minishell manages environment variables internally.
- You can use and modify them with `export`, `unset`, etc.
- minishell expands variables like `$USER` before executing commands.

### 7. Signal Handling

- minishell handles signals like `Ctrl+C` to interrupt a running command, similar to a real shell.

### 8. Error Handling

- minishell reports errors for invalid commands, syntax problems, or system errors with clear messages.

---

## How to Use minishell

1. **Compile:**  
   Run `make` in the project directory to build the shell.

2. **Start minishell:**  
   Run `./minishell` to launch.

3. **Type commands:**  
   You can use most basic shell commands, pipes, and redirections as in a normal shell.

4. **Exit:**  
   Use the command `exit` to quit.

---

## Teamwork

This project was developed by **Ayoub** and **Otman** working together.

- **Ayoub** focused on building the parsing part (input reading, tokenization, and command structure).
- **Otman** focused on the execution part (process management, pipes, redirections).
- We collaborated on integration, debugging, and ensuring the shell worked smoothly.

### What We Learned Working as a Team

- How to split a big project into smaller, manageable parts and assign responsibilities.
- The importance of clear communication, especially when integrating parsing and execution components.
- How to use version control (Git) for collaborative development and code review.
- How to resolve merge conflicts and work towards a common goal.
- The value of peer review and helping each other debug and improve code quality.

---

## Summary

minishell is an educational project that demonstrates:
- How to split and interpret user input
- How to manage processes and connect them with pipes
- How to handle file redirections, environment variables, and signals
- The basics of building a command-line shell in C
- The importance of teamwork in software development
