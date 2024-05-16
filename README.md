# pipex

This project consists in replicating the Unix pipe ```|``` unix through a program in C.

### Usage

Pipex requires at the very least 2 commands, an example would be:
```
$ ./pipex input_file command1 command2 ... commandn output_file
```
Where command1 command2 .... commandn contains the commands and it's options such as ```ls -l```.
The result will be written to the output_file, in the case where it doesn't exist, the file will be created.

Pipex imitates the behavior of this shell command:
```
$ < input_file command1 | command2 | ... | commandn > output_file
```

### Pipex heredoc execution
You can also run pipex with a heredoc, like this:
```
$ ./pipex here_doc LIMITER command1 command2 ... commandn output_file
```
You will then be asked to input text which will be used as input for the commands. In this case, the specified output file will not be overwritten but appended, which replicates the behavior ```>>``` in shell.
```
$ << LIMITER command1 | command2 | ... | commandn >> output_file
```
