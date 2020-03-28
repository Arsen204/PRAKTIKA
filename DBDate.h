#ifndef PRAKTIKA_DBDATE_H
#define PRAKTIKA_DBDATE_H

#include <cstring>
#include <ostream>
using namespace std;

class DBDate {
private:
    friend string DateToStr(const DBDate &date);

    friend ostream &operator<<(ostream &out, const DBDate &date);

    int m_day, m_month, m_year;//дата (текущая)
public:
    DBDate(string date);//формат строки: dd.mm.yyyy
    DBDate(int d, int m, int y) : m_day(d), m_month(m), m_year(y) {};

    DBDate() : m_day(0), m_month(0), m_year(0) {};//конструктор по умолчанию
    DBDate(const DBDate &dat) : m_day(dat.m_day), m_month(dat.m_month), m_year(dat.m_year) {}

    int GetDay() const;

    int GetMonth() const;

    int GetYear() const;

    static bool IsLeapYear(int year); //год високосный?
    static int GetDaysInMonth(int month, int year);//Количество дней в месяце
    int DaysInCurYear() const;//Количество дней от начала года до текущей даты
    bool operator==(const DBDate &date) const;

    bool operator<(const DBDate &date) const;

    bool operator>(const DBDate &date) const;

    bool operator<=(const DBDate &date) const;

    bool operator>=(const DBDate &date) const;

    bool operator!=(const DBDate &date) const;

    DBDate &operator+=(int days);//Прибавляет к текущей дате days дней
    DBDate &operator-=(int days);//Вычитает из текущей даты days дней
    int operator-(const DBDate &date) const;//Количество дней между текущей датой и date. Если текущая дата < date, результат -1.
};
#endif
