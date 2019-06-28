#ifndef HEAD_TOOLS_SHOT_DETECT
#define HEAD_TOOLS_SHOT_DETECT
#include <sys/types.h>
#include <sys/stat.h>

#include <stdio.h>
#include <iosfwd>
#include <fstream>

#include <iostream>
#include <iomanip>
#include <sstream>

#include <ctime>      // display date and time
#include <cmath>      // floor
#include <chrono>
#include <string>
#include <vector>

#define MAKE_DIRS(dir_str) mkdir(dir_str.c_str(), 0755)
using namespace std;

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::milliseconds milliseconds;

inline double elapsed_time_ms( Clock::time_point from)
{
Clock::time_point now = Clock::now();
milliseconds ms = std::chrono::duration_cast<milliseconds>( now - from );
return (double)ms.count();
}

inline double print_elapsed_time( Clock::time_point from, const char* prefix)
{
int msec = (int) elapsed_time_ms(from);
int sec = msec/1000;
printf("%s: Elapsed time %02dmin:%02ds:%04dms\n", prefix, sec/60, sec%60, msec%1000);

return msec / 1000.0;
}


template <typename T, typename S>
T fill_cast_ts_hhmmssmss(const S& hh, const S& mm, const S& ss, const S& mss, const char c)
{
        T result;
        std::ostringstream inter;
        inter << std::setw(2) << std::setfill(c) << hh << ":"
			  << std::setw(2) << std::setfill(c) << mm << ":"
			  << std::setw(2) << std::setfill(c) << ss << "."
			  << std::setw(4) << std::setfill(c) << mss;
        result = inter.str();
        return result;
}

template <typename T, typename S>
T fill_cast_ts_hhmmss(const S& hh, const S& mm, const S& ss, const char c)
{
        T result;
        std::ostringstream inter;
        inter << std::setw(2) << std::setfill(c) << hh << ":"
			  << std::setw(2) << std::setfill(c) << mm << ":"
			  << std::setw(2) << std::setfill(c) << ss;
        result = inter.str();
        return result;
}

template <typename T, typename S>
T fill_cast_ts_mmssmss(const S& mm, const S& ss, const S& mss, const char c)
{
        T result;
        std::ostringstream inter;
        inter << std::setw(2) << std::setfill(c) << mm << ":"
			  << std::setw(2) << std::setfill(c) << ss << "."
			  << std::setw(4) << std::setfill(c) << mss;
        result = inter.str();
        return result;
}

inline std::string second2string(double sec, const std::string& format) {
    //char buf[512];
    int hh, mm, ss, mss;
    hh  = (int) floor( sec/3600 );
    mm  = (int) floor( sec/60 ) % 60;
    ss  = (int) sec % 60;
    mss = (int) 10000*(sec - floor(sec));
    //printf("hh : %d, mm : %d, ss : %d, mss : %d\n", hh, mm, ss, mss);
    std::string time_stmp = "";
    if( format == "hh:mm:ss.mss" ) {
      //sprintf( buf, "%02d:%02d:%02d.%04d", (hh),(mm), (ss), (mss) );
	  time_stmp = fill_cast_ts_hhmmssmss<std::string, int>(hh, mm, ss, mss, '0');
    }
    else if( format == "hh:mm:ss" ) {
      //sprintf( buf, "%02d:%02d:%02d.%04d", (hh),(mm), (ss), (mss) );
	  time_stmp = fill_cast_ts_hhmmss<std::string, int>(hh, mm, ss, '0');
    }
    else if( format == "mm:ss.mss" ) {
      //sprintf( buf, "%02d:%02d.%04d", (60*hh+mm),(ss),(mss) );
	  time_stmp = fill_cast_ts_mmssmss<std::string, int>(mm, ss, mss, '0');
    }
	std::string ret = time_stmp;
    return ret;
}

#endif
