#include "main.h"

void	sleep_for(int time)
{
	int	seconds;

	seconds = 0;
	while (seconds < time)
	{
		usleep(1000);
		seconds++;
	}
}

size_t	get_time()
{
    struct timeval		tv;
    unsigned long long	time;

    gettimeofday(&tv, NULL);
    time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return (time);
}
