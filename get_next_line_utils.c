#include "get_next_line.h"

bool	check_line(t_tracker *tracker)
{
	t_tracker	*tail;
	uint32_t	i;

	if (!tracker)
		return (false);
	i = 0;
	tail = train_tail(tracker);
	while (tail->buffer[i])
	{
		if (tail->buffer[i] == NEW_LINE)
			return (true);
		i++;
	}
	return (false);
}

t_tracker	*train_tail(t_tracker *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

uint32_t	get_line_size(t_tracker *tracker)
{
	uint32_t	sz;
	uint32_t	i;

	if (!tracker)
		return (0);
	sz = 0;
	while (tracker)
	{
		i = 0;
		while (tracker->buffer[i])
		{
			if (tracker->buffer[i] == NEW_LINE)
				return (++sz);
			sz++;
			i++;
		}
		tracker = tracker->next;
	}
	return (sz);
}

void	unite_wagon(t_tracker *tracker, char *wagon)
{
	uint32_t	i;

	if (!tracker)
		return ;
	while (tracker)
	{
		i = 0;
		while (tracker->buffer[i])
		{
			if (tracker->buffer[i] == NEW_LINE)
			{
				*wagon++ = NEW_LINE;
				*wagon = 0;
				return ;
			}
			*wagon++ = tracker->buffer[i++];
		}
		tracker = tracker->next;
	}
	*wagon = 0;
}

void	free_wagons(t_tracker **tracker, t_tracker *fish_wagon)
{
	t_tracker	*tmp;

	if (!*tracker)
		return ;
	while (*tracker)
	{
		tmp = (*tracker)->next;
		free((*tracker)->buffer);
		free(*tracker);
		*tracker = tmp;
	}
	*tracker = NULL;
	if (fish_wagon && fish_wagon->buffer[0])
		*tracker = fish_wagon;
	else if (fish_wagon)
	{
		free(fish_wagon->buffer);
		free(fish_wagon);
	}
}
