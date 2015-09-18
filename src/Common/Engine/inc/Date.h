#ifndef DATE_H
#define DATE_H

#include <string>
#include <ctime>

struct nyears
{
    nyears ( unsigned long long int m):m(m){}
    unsigned long long int m;
};

struct nmonths
{
    nmonths ( unsigned long long int m):m(m){}
    unsigned long long int m;
};

struct ndays
{
    ndays ( unsigned long long int m):m(m){}
    unsigned long long int m;
};

class Date
{
public:
    Date();
    Date(const std::string& str);
    Date(const time_t & rawtime);
    Date(struct tm * timeinfo);
    virtual ~Date();

    static Date today();
    std::string toSqlFmt() const;
    std::string toStrFmt() const;
    Date getStartOfMonth() const;
    Date getEndOfMonth() const;

    int operator-(const Date& ) const;
    bool operator>=(const Date& ) const;
    bool operator<=(const Date& ) const;
    bool operator==(const Date& ) const;
    Date& operator=(const std::string& );

    Date operator+(const ndays& ) const;
    Date operator+(const nmonths& ) const;
    Date operator+(const nyears& ) const;
    Date operator-(const ndays& ) const;
    Date operator-(const nmonths& ) const;
    Date operator-(const nyears& ) const;

    Date& operator+=(const ndays& );
    Date& operator+=(const nmonths& );
    Date& operator+=(const nyears& );
    Date& operator-=(const ndays& );
    Date& operator-=(const nmonths& );
    Date& operator-=(const nyears& );
private:
    time_t m_dateData;

    const static unsigned int m_SEC_PER_DAY = 60 * 60 * 24;
};

ndays operator"" _days ( unsigned long long int n );
nmonths operator"" _months ( unsigned long long int n );
nyears operator"" _years ( unsigned long long int n );
#endif // DATE_H
