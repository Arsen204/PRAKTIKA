#include "DBDate.h"

int DBDate::GetDay() const {
    return m_day;
}

int DBDate::GetMonth() const {
    return m_month;
}

int DBDate::GetYear() const {
    return m_year;
}

DBDate::DBDate(string date) {
    m_day = stoi(date.substr(0, 2));
    m_month = stoi(date.substr(3, 2));
    m_year = stoi(date.substr(6, 4));
}

string DateToStr(const DBDate &date) {
    return to_string(date.m_day) + to_string(date.m_month) + to_string(date.m_year);
}

ostream &operator<<(ostream &out, const DBDate &date) {
    if (date.m_day < 10) out << "0";
    out << date.m_day << ".";
    if (date.m_month < 10) out << "0";
    out << date.m_month << ".";
    out<<date.m_year;
    return out;
}

bool DBDate::IsLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int DBDate::GetDaysInMonth(int month, int year) {
    if (month < 8 && month % 2 == 1) return 31;
    if (month >= 8 && month % 2 == 0) return 31;
    if (month == 2) return DBDate::IsLeapYear(year) ? 29 : 28;
    return 30;
}

bool DBDate::operator<(const DBDate &date) const {
    if (m_year != date.m_year) return m_year < date.m_year;
    if (m_month != date.m_month) return  m_month < date.m_month;
    return m_day < date.m_day;
}

bool DBDate::operator>(const DBDate &date) const {
    return date < *this;
}

bool DBDate::operator==(const DBDate &date) const {
    return !(date > *this || date < *this);
}

bool DBDate::operator<=(const DBDate &date) const {
    return !(date < *this);
}

bool DBDate::operator>=(const DBDate &date) const {
    return !(date > *this);
}

bool DBDate::operator!=(const DBDate &date) const {
    return !(*this == date);
}

int DBDate::DaysInCurYear() const {
    return (DBDate(*this) - DBDate(1,1,m_year));
}

int DBDate::operator-(const DBDate &date) const {
    if (date > *this) return -1;

    int sum = 0;

    int this_days = m_day;
    for (int i = 1; i < m_month; ++i) {
        this_days += DBDate::GetDaysInMonth(i, m_year);
    }

    int date_days = date.m_day;
    for (int i = 1; i < date.m_month; ++i) {
        date_days += DBDate::GetDaysInMonth(i, date.m_year);
    }

    int flag = 0;

    if (this_days >= date_days)
        sum += this_days - date_days;
    else {
        flag = 1;
        sum += (DBDate::IsLeapYear(m_year - flag) ? 366 : 365) - date_days + this_days;
    }

    for (int i = date.m_year; i < m_year - flag; ++i)
        sum += (DBDate::IsLeapYear(i) ? 366 : 365);

    return sum;
}

DBDate &DBDate::operator+=(int days) {
    m_day +=days;

    while (m_day > DBDate::GetDaysInMonth(m_month, m_year)) {
        m_day -= DBDate::GetDaysInMonth(m_month, m_year);
        ++m_month;
        if (m_month > 12) {
            ++m_year;
            m_month = 1;
        }
    }

    return *this;
}

DBDate &DBDate::operator-=(int days) {
    m_day -= days;

    while (m_day <= 0) {
        --m_month;
        if (m_month < 1) {
            --m_year;
            m_month = 12;
        }
        m_day += DBDate::GetDaysInMonth(m_month, m_year);
    }

    return *this;
}