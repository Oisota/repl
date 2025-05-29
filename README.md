# REPL
Create a REPL for a given command line program that takes sub arguments.

For Example:

Create a git shell where the default command `git status` runs if the user presses enter with no sub command given.
```sh
$ repl git status
git>
```

Create a docker shell that runs `docker ps` if no sub command is given.
```sh
$ repl docker ps
docker>
```

It is recommended to wrap this program with `rlwrap` to get command history and other nice things:
```sh
$ rlwrap -c repl git status
git>
```
