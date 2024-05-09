#include "main.h"

size_t	get_time(void)
{
	struct timeval	tv;
	size_t			time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

void	sleep_for(int time)
{
	size_t	expected;

	expected = get_time() + time;
	while (get_time() < expected)
	{
		// if ()
		// return ;
	}
}
