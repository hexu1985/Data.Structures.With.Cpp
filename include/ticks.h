#ifndef TICK_COUNT
#define TICK_COUNT

#ifdef __GNUC__
#include <sys/types.h>
#include <sys/times.h>

long TickCount(void)
{
	struct tms accumTime;

	times(&accumTime);
	return accumTime.tms_utime + accumTime.tms_stime;
}
#endif  // __GNUC__

#ifdef __BORLANDC__

#include <time.h>

long TickCount(void)
{
	return (clock()/CLK_TCK)*60;
}

#endif  // __BORLANDC__

#endif  // TICK_COUNT
