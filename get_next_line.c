#include "get_next_line.h"

static void	enqueue(t_tracker **tracker, char *buffer)
{
	t_tracker	*node;
	t_tracker	*tail;

	node = (t_tracker *)malloc(sizeof(t_tracker));
	if (!node)
		return ;
	node->buffer = buffer;
	node->next = NULL;
	tail = train_tail(*tracker);
	if (!tail)
		*tracker = node;
	else
		tail->next = node;
}

static void	train_of_buffer(t_tracker **tracker, int fd)
{
	char		*buffer;
	uint32_t	bread;

	while (!check_line(*tracker))
	{
		buffer = (char *)malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return ;
		bread = read(fd, buffer, BUFFER_SIZE);
		if (bread <= 0)
		{
			free(buffer);
			return ;
		}
		buffer[bread] = 0;
		enqueue(tracker, buffer);
	}
}

static char	*extract_line(t_tracker *tracker)
{
	uint32_t	line_size;
	char		*line;

	line_size = get_line_size(tracker);
	line = (char *)malloc(line_size + 1);
	if (!line)
		return (NULL);
	unite_wagon(tracker, line);
	return (line);
}

void	train_clean(t_tracker **tracker)
{
	t_tracker	*tail;
	t_tracker	*fetsh_wagon;
	char		*buffer;
	uint32_t	i;
	uint32_t	j;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	fetsh_wagon = (t_tracker *)malloc(sizeof(t_tracker));
	if (!buffer || !fetsh_wagon)
		return ;
	tail = train_tail(*tracker);
	i = 0;
	while (tail->buffer[i] && tail->buffer[i] != NEW_LINE)
		i++;
	j = 0;
	while (tail->buffer[++i])
		buffer[j++] = tail->buffer[i];
	buffer[j] = 0;
	fetsh_wagon->buffer = buffer;
	fetsh_wagon->next = NULL;
	free_wagons(tracker, fetsh_wagon, buffer);
}

char	*get_next_line(int fd)
{
	static	t_tracker	*tracker;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	train_of_buffer(&tracker, fd);
	if (!tracker)
		return (NULL);
	line = extract_line(tracker);
	train_clean(&tracker);
	return (line);
}
