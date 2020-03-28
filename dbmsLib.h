#pragma once
#ifndef _dbmsLib_
#define _dbmsLib_
#include <iostream>
#include <fstream>
#include <strstream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>

using namespace std;

namespace dbmsLib
{
    class DBDate {
    private:
        static const int arrDays[13];
        friend string DateToStr(const DBDate &date);
        friend ostream &operator<<(ostream &out, const DBDate &date);
        int m_day, m_month, m_year;//дата (текущая)
    public:
        explicit DBDate(const string &date);//формат строки: dd.mm.yyyy
        DBDate(int d, int m, int y) : m_day(d), m_month(m), m_year(y) {};
        DBDate() : m_day(0), m_month(0), m_year(0) {};//конструктор по умолчанию
        DBDate(const DBDate &dat) = default;
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

    enum DBType {
        NoType,
        Int32,
        Double,
        String,
        Date
    };

    enum Condition{Undefined,Equal,NotEqual,Less,Greater,LessOrEqual,GreaterOrEqual};

    const int LENGTH = 24;

    struct ColumnDesc {
        char colName[LENGTH];
        DBType colType;
        int length;
    };

    struct Strip {
	    int nField;
	    int* fieldWidth;
    };

    typedef map<string, void*> Row;
    typedef map<string, ColumnDesc> Header;

    string GetTabNameFromPath(string path);
    string ignoreBlanc(const string str);
    void* GetValue(string value, string columnName,Header hdr);
    void* SetValue(string value, string columnName,Header hdr);
    bool comparator(DBType type,void *obj1,Condition condition,void *obj);
    int GetLength(ColumnDesc colDesc);

    class DBTableTxt{
        Header columnHeaders;
        string tableName;
        string primaryKey;
        vector<Row> data;
        string fileName;
    public:
        DBTableTxt(){}
        DBTableTxt(string tabName);
        DBTableTxt(string tabName,Header hdr,string primKey);
        const char* TypeName(DBType type);
        ~DBTableTxt(){}
        vector<int> IndexOfRecord(void* keyValue,string keyColumnName);
        string valueToString(Row& row,string columnName);
        void ReadDBTable(string tabName);
        void PrintTable(int screenWidth);
        void WriteDBTable(string tabName);
        int GetSize();
        DBType GetType(char* columnName);
        Row operator[](int ind);
        void SetFileName(string path);
        void SetTableName(string tName);
        void SetPrimaryKey(string key);
        string GetFileName();
        string GetTableName();
        string GetPrimaryKey(){return primaryKey;}
        Header GetHeader();
        void SetHeader(Header& hdr);
        Row CreateRow();
        Row GetRow(int index);
        void AddRow(Row row,int index);
        void CreateTableMaket(Strip* &strips,int &nStrip,int screenWidth);
        friend void ReadDBTable1(DBTableTxt& tab,string fileName);//fileName=path+tableName
        friend void ReadDBTable2(DBTableTxt& tab,string fileName);//fileName=path+tableName
        friend void ReadDBTable3(DBTableTxt& tab,string fileName);//fileName=path+tableName
        friend void PrintTable1(DBTableTxt& tab,int screenWidth);//fileName=path+tableName
        friend void PrintTable2(DBTableTxt& tab,int screenWidth);//fileName=path+tableName
        friend void PrintTable3(DBTableTxt& tab,int screenWidth);//fileName=path+tableName
      };

    class DBTableSet
    {
    private:
	    string dbName;
	    map<string, DBTableTxt*> db;
    public:
	    DBTableSet(){};
	    DBTableSet(string name);
	    int ReadDB();
	    void PrintDB(int numcol);
	    void WriteDB();
	    string GetDBName(){return dbName;}
	    DBTableTxt* operator[](string tableName);
    };
}
#endif