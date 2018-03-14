/*************************************************************************
    > File Name: util.h
    > Author: berli
    > Mail: berli@tencent.com 
    > Created Time: 2018年03月14日 星期三 18时56分13秒
 ************************************************************************/
#ifndef UTIL_2018_03_14
#define UTIL_2018_03_14

#include<iostream>
#include "ip_finder.hpp"
#include "easylogging++.h"
using namespace std;

class util
{
public:
	static string getRIp(const string&asStr)
	{
		auto data = getRemoteIp(asStr);
		string lsIp(get<0>(data));
		lsIp += ":";
		lsIp += to_string(get<1>(data));
		return lsIp;
	}

	static tuple<string, int> getRemoteIp(const string&asStr)
	{
		const string flags = "remote address = ::ffff:";
		size_t pos = asStr.find(flags);
		pos += flags.size();
		if(pos != string::npos)
		{
			string ip;
			int    port;
			size_t pos1 = asStr.find(":", pos);
			if( pos1 != string::npos)
			{
				ip = asStr.substr(pos, pos1 - pos);
				port = atoi( asStr.substr(pos1+1).c_str());
				return make_tuple(ip, port);
			}
			else
				return make_tuple("", 0);
		}
		else
			return make_tuple("", 0);

	};

	static string getLocation(const string&asStr)
	{
		auto data = getRemoteIp(asStr);
		is::common::location::ip_finder loIP;

		string country, area;
		int liRet = loIP.initialize("qqwry.dat");
		if( liRet != 0)
		{
			LOG(ERROR)<<"initialize qqwry.dat failed!"<<endl;
			return country;//null
		}
		bool ret = loIP.get_ip_original_info(get<0>(data), country, area);

		if( ret)
		{
			string country1, area1;
			loIP.gb2312toutf8(country,country1);
			loIP.gb2312toutf8(area, area1);

			return (country1+area1);
		}
		return country;//null
	}
};

#endif

