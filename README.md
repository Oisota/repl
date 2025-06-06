# REPL
Create a REPL for a given command line program that takes sub arguments.
This program uses [GNU Readline](https://tiswww.case.edu/php/chet/readline/rltop.html) to provide file completion and command history.

For Example:

Create a git shell where the default command `git status` runs if the user presses enter with no sub command given.
```sh
$ repl -d status git
git>
```

Create a docker shell that runs `docker ps` if no sub command is given.
```sh
$ repl -d ps docker
docker>
```
