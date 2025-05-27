# REPL
Create a REPL for a given command line program that takes sub arguments.

For Example:

Create a git shell where the default command `git status` runs if the user presses enter with no sub command given.
```
$ repl git status
git>
```

Create a docker shell that runs `docker ps` if no sub command is given.
```
$ repl docker ps
docker>
```
