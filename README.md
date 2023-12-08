# pipex

Recreation of the pipe shell command in C

### Running the command
---
`./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2`

Corresponds to:

`< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2`

---

`./pipex here_doc LIMITER cmd cmd1 file`

Corresponds to:

`cmd << LIMITER | cmd1 >> file`
