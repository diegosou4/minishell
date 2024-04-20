# Minishell 2024

Welcome to the fascinating world of Bash! Our project is quite complex on its own, but today we'll explain a bit about what we did, what helped us achieve the result, and of course, the path we walked to get there. Right off the bat, it's worth noting that our minishell is far from being the best you'll see, but what really matters is the learning gained throughout this challenging process.

Communication with your partner will be key, as the executor needs to create a structure that the parser can understand and work in parallel to provide the requested structure. This step is crucial in the project: separating the responsibilities of each.

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

[GitHub Repository - Minishell](https://github.com/zstenger93/minishell/blob/master/mindmap.png)

Thank you all, and best of luck! :)

Diegmore and Juan-pma  
42 Lisboa

