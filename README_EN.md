# Minishell 2024

Welcome to the fascinating world of Bash! Our project is quite complex on its own, but today we'll explain a bit about what we did, what helped us achieve the result, and of course, the path we walked to get there. Right off the bat, it's worth noting that our minishell is far from being the best you'll see, but what really matters is the learning gained throughout this challenging process.

Communication with your partner will be key, as the executor needs to create a structure that the parser can understand and work in parallel to provide the requested structure. This step is crucial in the project: separating the responsibilities of each.

# Brief Introduction to Minishell

Minishell is a simplified Unix shell program that provides a command-line interface for users to interact with the operating system. It serves as a basic shell implementation with limited functionality compared to full-fledged shells like Bash or Zsh.

This program allows users to execute various commands and manage processes within the operating system. It supports features such as command execution, input/output redirection, pipeline execution, environment variable management, and basic error handling.

While Minishell may lack some advanced features found in more comprehensive shells, it offers a lightweight and straightforward environment for executing commands and performing basic system operations. It is often used for educational purposes or as a starting point for building more complex shell programs.

Overall, Minishell provides a practical and fundamental command-line interface that allows users to interact with the operating system efficiently.

## Parsing

To start the project, we need to take the user's input, which will be provided as a string, and manipulate it to derive the meaning of the words and create what is commonly known as commands.

Each command is a simple word that provides meaning. We have different types of words and hierarchies that we need to consider. In this case, we will need to handle commands, variables, pipes, and other special characters that give meaning to the code.

The process to do this is quite simple. We will start by breaking down and conquering the string, creating something like a dictionary where we store words or characters with special meanings, and then group them with specific tags.

This will allow us to manipulate the words and characters later based on the tags assigned to the structure. Some tags are taken as displayed in the manual.

The following is a brief description of the shell’s operation when it reads and executes a command. Basically, the shell does the following:

1. Reads its input from a string supplied as an argument to the user’s terminal. For this, we will use the function `readline`.
2. Breaks the input into words and operators, obeying the quoting rules. These tokens are separated by metacharacters. We will separate the string into words, based on spaces, and check if it is a pipe or not. This will help us handle each part of the command line properly, as you know, every pipe is an independent process.
3. Parses the tokens into simple and compound commands. After we get each word and token with their specific tag, whether it is a variable, a command, a word, or a redirection, we will be able to handle the commands.
4. Performs the various shell expansions, breaking the expanded tokens into lists of filenames, commands, and arguments. This is very important as we need to check, for example, the variables, and if we get `$USER`, we will need to expand to `juan-pma` in my case. The same logic applies to all the environment variables.
5. Performs any necessary redirections and removes the redirection operators and their operands from the argument list. We will give meaning to each redirection to be considered in the execution part.
6. Passes the structure with the commands to the execution part to handle the rest of the project.

By following this sequence, Minishell ensures that user inputs are correctly interpreted and executed, maintaining the functionality expected from a basic Unix shell.
## Execution

After completing the parse and delivering the necessary structures, the first step is to handle the heredoc. We execute all heredocs before starting execution, as we use them with pipes. Next, we have our execution routine that always checks whether it's a builtin or an executable. It's worth noting a specific case: when we have only one command and it's a builtin. However, let's focus on the general execution routine.

Within this routine, we check if it's necessary to create pipes, i.e., if there's more than one command. We create a child process and, within it, handle the redirection structures and their commands. It's crucial to understand that these steps must be performed within the child process. After that, we determine from where we'll read and where we'll write and then execute our command. We must be careful with file descriptor leaks or with incorrectly closing file descriptors at inappropriate times.

## Builtins

I believe the most complex builtin to implement is `export`, since it's used in various scenarios. We chose to create a copy of the environment, along with a structure containing three different tokens. This helps us display the environment differently, even while consuming the same structure. The most challenging part was creating the routine that checks if the key exists and, depending on the case, whether we add a value or just concatenate. I confess that, due to the complexity of various specific cases, some were not handled correctly. The other builtins are simpler, as they rely on external functions. For example, `cd` already has a function to redirect to another location according to the provided path, `pwd` is a function that returns the current directory, and `exit` only requires conversion of the provided number, as exit statuses range from 0 to 255.

## Final Thoughts

In my opinion, the execution of our project was very good. Despite some flaws, we managed to fulfill the most important aspects: commitment to the project, meeting defined deadlines, and organization. These were the key elements that allowed us to complete the project with a sense of accomplishment.

## Result

![RESULT](https://i.imgur.com/0twltqs.png)

### Useful Links

[Video Presentation](https://youtu.be/yHDzFRWmLGA?si=WkXmLU5iD3UsIq9r)

[Mind Map - Minishell](https://github.com/zstenger93/minishell/blob/master/mindmap.png)

Thank you all, and best of luck! :)

Diegmore and Juan-pma  
42 Lisboa

