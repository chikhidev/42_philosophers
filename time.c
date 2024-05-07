#include "main.h"

void	sleep_for(int time)
{
    size_t  expected;

    expected = get_time() + time;

    while (1)
    {
        if (get_time() >= expected)
            return ;
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
