#include "Date.h"
#include <iostream>

ndays operator"" _days ( unsigned long long int n )
{
    return ndays(n);
}
nmonths operator"" _months ( unsigned long long int n )
{
    return nmonths(n);
}
nyears operator"" _years ( unsigned long long int n )
{
    return nyears(n);
}

Date Date::today()
{
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime (&rawtime);

    strftime (buffer,80,"%F",timeinfo);
    return Date(buffer);
}

Date::Date(): m_dateData(0)
{
    //ctor
}

Date::Date(const std::string& str)
{
    struct tm * timeinfo;
    int year, month, day;

    sscanf(str.c_str(), "%d-%d-%d", &year, &month, &day);

    time (&m_dateData);
    timeinfo = localtime (&m_dateData);
    timeinfo->tm_year   = year - 1900;
    timeinfo->tm_mon    = month - 1;
    timeinfo->tm_mday   = day;
    timeinfo->tm_hour   = 1;
    timeinfo->tm_min    = 0;
    timeinfo->tm_sec    = 0;


    /* call mktime: timeinfo->tm_wday will be set */
    m_dateData = mktime (timeinfo);

}

Date::~Date()
{
    //dtor
}

std::string Date::toSqlFmt() const
{
    return "'" + toStrFmt() + "'";
}

std::string Date::toStrFmt() const
{
    char buffer[80];
    struct tm * timeinfo;

    timeinfo = localtime (&m_dateData);
    strftime (buffer, 80, "%F", timeinfo);

    return std::string(buffer);
}

int Date::operator-(const Date& rhs) const
{
    return difftime(m_dateData, rhs.m_dateData) / m_SEC_PER_DAY;
}

bool Date::operator>=(const Date& rhs) const
{
    return (m_dateData >= rhs.m_dateData);
}

bool Date::operator<=(const Date& rhs) const
{
    return (m_dateData <= rhs.m_dateData);
}

Date& Date::operator=(const std::string& rhs)
{
    *this = Date(rhs);

    return *this;
}

Date Date::operator+(const ndays& n) const
{
    Date date;

    date.m_dateData = m_dateData + n.m * m_SEC_PER_DAY;
    return date;
}

Date Date::operator-(const ndays& n) const
{
    Date date;

    date.m_dateData = m_dateData - n.m * m_SEC_PER_DAY;
    return date;
}

Date Date::operator+(const nyears& n) const
{
    struct tm * timeinfo;
    Date date;

    timeinfo = localtime (&m_dateData);
    timeinfo->tm_year   += n.m;

    date.m_dateData = mktime (timeinfo);
    return date;
}

Date Date::operator-(const nyears& n) const
{
    struct tm * timeinfo;
    Date date;

    timeinfo = localtime (&m_dateData);
    timeinfo->tm_year   -= n.m;

    date.m_dateData = mktime (timeinfo);

    return date;
}

Date Date::operator+(const nmonths& n) const
{
    struct tm * timeinfo;
    Date date;

    timeinfo = localtime (&m_dateData);
    timeinfo->tm_mon   += n.m;

    date.m_dateData = mktime (timeinfo);

    return date;
}

Date Date::operator-(const nmonths& n) const
{
    struct tm * timeinfo;
    Date date;

    timeinfo = localtime (&m_dateData);
    timeinfo->tm_mon   -= n.m;

    date.m_dateData = mktime (timeinfo);

    return date;
}

Date& Date::operator+=(const nmonths& n)
{
    struct tm * timeinfo;

    timeinfo = localtime (&m_dateData);
    timeinfo->tm_mon   += n.m;

    m_dateData = mktime (timeinfo);

    return *this;
}

Date Date::getStartOfMonth() const
{
    struct tm * timeinfo;
    Date date;

    timeinfo = localtime (&m_dateData);
    timeinfo->tm_mday   = 1;

    date.m_dateData = mktime (timeinfo);

    return date;
}
