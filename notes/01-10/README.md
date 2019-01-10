## Running the Compiler

See the project [overview](../../project/overview.md) for details on running the compiler and p-code machine.

## GCC, Linking, and Makefiles

`gcc` uses several tools convert your source file to an executable program, including the compiler, assembly, and linker.

1. `gcc -S` only compiles the program to assembly, which can be seen in the resulting `.s` file.
1. `gcc -c` compiles and assembles the program into an object file (`.o`)
1. gcc file1.o file2.o will execute the linker (`ld`)

Makefiles enable _incremental compilation_ automatically.  By
examining the timestamps of the compiled object files, only those
source files that have changed get recompiled, saving considerable
time when compiling large program. See an example
[here](code/linking).

### More Reading

- <https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html>

- <https://randu.org/tutorials/c/make.php>

- <https://stackoverflow.com/questions/6666805/what-does-each-column-of-objdumps-symbol-table-mean>

- <https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html>

## Using git

Clone wants to copy a project to your local machine.

Commit to "save" changes.  Push to upload changes to the GitHub copy.

### Clone

On your development machine, download or _clone_ the skeleton repository for the project:

    git clone https://github.com/cop3402spring19/project-USERNAME.git

This only needs to be done once (unless you want to develop on multiple machines).

### Basic Workflow with Commit and Push

The most common use-case for this class is to record or _commit_ changes to your local repository, then upload or _push_ those changes to github, syncing it with your local repository.

Let's assume you have been editing _lexer.c_.  To commit, do

    git commit lexer.c

An editor will pop up requesting a description of the changes.  This description can also be specified on the command-line as follows:

    git commit -m "DESCRIPTION OF CHANGES" lexer.c

In order to sync the github repository, upload or _push_ the changes:

    git push

It is sound practice to make small, frequent commits that are well-documented.

### Checking the State of the Local Repository

It is very useful to freqently check the state of your local repository with

    git status
    
This will summarize the changes made since the last commit, as well as the difference from the last known state of the github repository.

It is good practice to use _git diff_ to see what changes have been made since the last commit.

    git diff lexer.c
    
This will show you what has been added or removed since the last commit for _lexer.c_.

    git diff
    
will show you all changes in the directory.


### Useful extras

Check the history of commits with

    git log
    
which can also be used with a particular file

    git log parser.c

If you use multiple machines, receive the latest changes with

    git pull

### More Reading

- <https://guides.github.com/activities/hello-world/>
- <https://rogerdudler.github.io/git-guide/>
- <https://www.atlassian.com/git/tutorials/using-branches>
- <https://www.atlassian.com/git/tutorials/comparing-workflows>
