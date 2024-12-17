#ifndef MINITALK_H
# define MINITALK_H

# define _POSIX_C_SOURCE 200112L
# define _DEFAULT_SOURCE

# include <stdio.h>
# include <signal.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

typedef struct s_header
{
	int	pid;
	int	msg_size;
}	t_header;


#endif