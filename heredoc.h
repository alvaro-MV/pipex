#ifndef HERE_DOC_H
# define HERE_DOC_H

# include "pipex.h"
# include "lib/include/get_next_line.h"

# define HERE_MASK O_APPEND | O_CREAT | O_WRONLY

int		here_doc(char *delimiter);
void	execute_pipe_hd(char **path, char **argv, int infd);
void	execute_child_hd(char **argv, char **path, int pipefd[2]);

#endif
