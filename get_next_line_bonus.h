#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

# define FD_MAX 256

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define NEW_LINE '\n'

typedef struct s_tracker
{
	char				*buffer;
	struct s_tracker	*next;
}						t_tracker;

// UTILS
bool		check_line(t_tracker *tracker);
t_tracker	*train_tail(t_tracker *tracker);
uint32_t	get_line_size(t_tracker *tracker);
void		unite_wagon(t_tracker *tracker, char *wagon);
void		free_wagons(t_tracker **tracker, t_tracker *fish_wagon);
// CORE
char		*get_next_line(int fd);

#endif
