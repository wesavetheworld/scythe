#include "Global.h"
#include "Util.h"

#include <sstream>
using std::stringstream;

template<> 
bool FromString<bool>(string key)
{
	if (key == "true" || key == "on" || key == "yes")
		return true;
	if (key == "false" || key == "off" || key == "no")
		return false;
	if (key == "")
		return false;
	return false;
}

string ToString(bool key, string truestring, string falsestring)
{
	if (key)
		return truestring;
	else
		return falsestring;
}

template<> int FromString<int>(string key)
{
	if (key == "")
		return 0;
	stringstream sstr(key);
	int ret=0;
	sstr >> ret;
	return ret;
}

uint EndianSwap(uint n)
{
	return ((n&0xFF)<<24) | ((n&0xFF00)<<8) | ((n&0xFF0000)>>8) | ((n&0xFF000000)>>24);
}

#include <ctime>

#ifdef WIN32
#include "windows.h"
clock_t ticker()
{
	//todo: convert to QueryPerformanceCounter
	return clock()/(CLOCKS_PER_SEC/1000);
}

void Wait_ms(uint n)
{
	Sleep(n);
}
#else
#include <unistd.h>
#include <sys/time.h>
clock_t ticker()
{
	timeval t;
	gettimeofday(&t, NULL);
	unsigned long long l = ((unsigned long long)(t.tv_sec))*1000 + t.tv_usec/1000;
	return l/1000;
}

void Wait_ms(uint n)
{
	usleep(n*1000);
}
#endif
