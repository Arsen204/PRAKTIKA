#include "dbmsLib.h"

int menu(){
    cout<<"================= МЕНЮ ===================\n";
    cout<<"\t1 - Чтение таблиц БД\n";
    cout<<"\t2 - Печать таблицы БД\n";
    cout<<"\t3 - \n";
    cout<<"\t4 - \n";
    cout<<"\t5 - \n";
    cout<<"\t6 - \n";
    cout<<"\t7 - \n";
    cout<<"\t8 - \n";
    cout<<"\t10 - Выход\n";
    int choice;
    cout<<"Выберите действие\n";
    cin>>choice;
    while(cin.fail()){
        cout<<"Недопустимое действие. Повторите выбор\n";
        cin.clear();
        cin.ignore(10,'\n');
        cin>>choice;
    }
    return choice;
}

int main(){
    system("chcp 1251>nul");
    string dbName("LibraryTxt");
    cout<<dbName<<endl;
    string tabName("Students");
    dbmsLib::DBTableTxt tab;
    string path="..\\"+dbName+"\\";
    string str("11.02.2020");
    dbmsLib::DBDate today(str);
    int screenWidth=78;

    vector <int> indexes;
        int ind;
        while (true) {
            switch (menu()) {
                case 1:
                    tab.ReadDBTable(path + tabName + ".txt");//Чтение таблиц БД.
//БД хранится в папке "..\\"+dbName+".
//Имя БД оканчивается или на Txt, если таблицы БД хранятся в текстовых файлах,
//Каждая таблица хранится в отдельном файле с именем = <имя таблицы>+".txt"
//Структура файла:
//Первая строка файла содержит имя таблицы и имя столбца с первичным ключем
//Вторая строка файла - заголовок таблицы
//Все последующие строки - записи таблицы.
                    break;
                case 2:
                    tab.PrintTable(screenWidth);//Печать таблицы БД (screenWidth-ширина экрана)
                    break;
                case 3:
                    tab.WriteDBTable(path + tabName + ".txt");
                    break;
                case 4:
                    tab.AddRow(tab.CreateRow(), tab.GetSize());
                    break;
                case 5:
                    *(string *) tab[2]["Group"] = "IU5-21";
                    break;
                case 6:
                    ind = 3;
                    indexes = tab.IndexOfRecord(&ind, "StudentID");
                    cout << *(string *) tab[indexes[0]]["Name"] << endl;
                    break;
                case 7:
                    tab.ReadDBTable(path + "Books" + ".txt");
                    for (int i = 0; i < tab.GetSize(); i++) {
                        (*(int *) tab[i]["Quantity"])++;
                    }
                    tab.PrintTable(screenWidth);
                    tab.WriteDBTable(path + "Books" + ".txt");
                    break;
                case 8:
                    break;
                case 10:
                    return 0;//завершение работы
                default:
                    cout<<"Недопустимое действие. Повторите выбор\n";
                    break;
            }
        }
}