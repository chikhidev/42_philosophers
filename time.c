#include "main.h"

void	sleep_for(int time)
{
	usleep(time * 1000);
}

size_t	get_time()
{
    struct timeval		tv;
    unsigned long long	time;

    gettimeofday(&tv, NULL);
    time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return (time);
}
