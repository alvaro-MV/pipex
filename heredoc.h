#ifndef HERE_DOC_H
# define HERE_DOC_H

# include "pipex.h"
# include "lib/include/get_next_line.h"

# define HERE_MASK O_RDWR | O_CREAT | O_APPEND

int	here_doc(char *delimiter);

#endif
