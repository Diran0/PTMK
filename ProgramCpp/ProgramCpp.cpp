#include <iostream>
#include "sqlite3.h"
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

int callback(void* NotUsed, int argc, char** argv, char** azColName) //функция вывода полученного от базы данных Select
{
    cout << "|";
    for (int i = 0; i < argc; i++) {
        cout << argv[i] ;
        cout << " | ";
        }
    cout << endl;
    return 0;
}

void info() //функция вывода информации о командах
{
    cout << "Enter :" << endl;
    cout << " - \"info\" to show info" << endl;
    cout << " - \"myApp 1\" to create table" << endl;
    cout << " - \"myApp 2\" to add new people in forrmat [FIO YYYY-MM-DD G]" << endl;
    cout << " - \"myApp 3\" to output database" << endl;
    cout << " - \"myApp 4\" to create random 100 male who fename is F and 1.000.000 peoples" << endl;
    cout << " - \"myApp 5\" to output males, whith fename is F" << endl;
    cout << " - \"myApp 6\" to drop table" << endl;
    cout << " - \"exit\" to close program" << endl;
}
    
int getrand(int min, int max) //функция для создания случайных значений в указанном промежутке
{
    int num = min + rand() % (max - min + 1);
    return num;
}

int main()
{
    sqlite3 *db;
    int base = sqlite3_open("data1.db", &db); // подключение к базе данных под названием data1.db по метке db
    string zapros; 
    string fio;
    string dat;
    string gen;
    string sqls;
    string cflag;
    bool flag = false;  // флаг для определения необходимости пользователю ввода 1000000 случайных имён
    char* zErrMsg = 0;
    int j;
    clock_t start, end;
     info();
    while (zapros != "exit")  //начало основного цикла программы. Программа завершается при вводе пользователем команды exit
    {
            flag = false; 
            getline(cin, zapros);
            if (zapros.find("myApp ") == 0)  //при вводе пользователем myApp используется одна из основных программ
        {
            int numb = (zapros[6] - 48); 
            switch (numb)  //проверка какую именно из заданных программ нужно выполнить для пользователя
            {


            case 1:  //создание таблицы в базе данных
                sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS Table1 (FIO CHAR(3), Birth DATE, Gender CHAR(3));", callback, 0, &zErrMsg);
                break;


            case 2:  //добавление данных в таблицу
                fio = zapros.substr(8, 3);  //вычленение символов для занесения в ФИО
                dat = zapros.substr(12, 10); //вычленение символов для занесения в дату рождения
                gen = zapros.substr(23, 1); //вычленение символов для занесения в пол
                sqls = "INSERT INTO Table1 VALUES (\"" +  fio +  "\", \"" +  dat +  "\", \"" +  gen +  "\");";
                cout << sqls.c_str() << endl;  //отображение для пользователя того, какие данные будут внесены
                sqlite3_exec(db, sqls.c_str(), callback, 0, &zErrMsg);
                break;


            case 3:  //отображение всей таблицы с сортировкой по ФИО
                cout << "|Name|    Birth   | G | Age|" << endl;
                sqls = "SELECT FIO, Birth, Gender, (strftime('%Y-%m-%d', 'now') - strftime( Birth)) AS Year FROM Table1 order by FIO ;";
                sqlite3_exec(db, sqls.c_str(), callback, 0, &zErrMsg);
                break;


            case 4:  //создание случайных записей
                cout << "Create random 1.000.000 peoples?(y/n)";
                cin >> cflag;
                if ((cflag == "y") or (cflag == "Y"))  //если пользователь не соглашается(не отвечает y/Y) на добавление 1000000 случайных записей, то флаг не поменяется потому что он итак запрещает это по-умолчанию
                {
                    flag = true;
                }

                if (flag)  //создание большого количества случайных строк
                {
                    for (int i = 0; i < 1000000; i++) {
                        fio = (char)getrand(65, 90);
                        fio = fio + (char)getrand(65, 90);
                        fio = fio + (char)getrand(65, 90); //рандомизация инициалов из заглавных букв по таблице ASCII
                        dat = to_string(getrand(1930, 2009)) + "-";  // год выбирается между 1930 и 2009, что было выбрано по усмотрению программиста
                        int m = getrand(1, 12); //выбирается случайный номер месяца
                        if (m < 10) {
                            dat = dat + "0" + to_string(m) + "-";  //для нормального отображения месяца, номер делается двузначным
                        }
                        else {
                            dat = dat + to_string(m) + "-";
                        }
                        int d;
                        if (m = 2) {  //здесь и в следующей связке if-else определяется сколько дней должно быть в месяце
                            d = getrand(1, 28);
                        }
                        else {
                            if ((m = 1) or (m = 3) or (m = 5) or (m = 7) or (m = 8) or (m = 10) or (m = 12)) {
                                d = getrand(1, 31);
                            }
                            else {
                                d = getrand(1, 30);
                            }
                        }

                        if (d < 10) {
                            dat = dat + "0" + to_string(d); // для нормального отображения, даты делаются двузначными
                        }
                        else {
                            dat = dat + to_string(d);
                        }

                        gen = (char)(7 * (10 + getrand(0, 1)));  //пол выбирается случайно из двух чисел и приводится к Ascii коду со значением либо 70, либо 77 для выбора F или M
                        sqls = "INSERT INTO Table1 VALUES (\"" + fio + "\", \"" + dat + "\", \"" + gen + "\");";
                        sqlite3_exec(db, sqls.c_str(), callback, 0, &zErrMsg);
                    }
                }
                for (int i = 0; i < 100; i++)  // аналогично добалению случайных записей(цикл выше), за исключением рандомизации фамилии и пола
                {
                    fio = "F";
                    fio = fio + (char)getrand(65, 90);
                    fio = fio + (char)getrand(65, 90);
                    dat = to_string(getrand(1930, 2009)) + "-";
                    int m = getrand(1, 12);
                    if (m < 10) {
                        dat = dat + "0" + to_string(m) + "-";
                    }
                    else {
                        dat = dat + to_string(m) + "-";
                    }
                    int d;
                    if (m = 2) {
                        d = getrand(1, 28);
                    }
                    else { 
                        if ((m = 1) or (m = 3) or (m = 5) or (m = 7) or (m = 8) or (m = 10) or (m = 12)) {
                            d = getrand(1, 31);
                        }
                        else {
                            d = getrand(1, 30);
                        }
                    }

                    if (d < 10) {
                        dat = dat + "0" + to_string(d);
                    }
                    else {
                        dat = dat + to_string(d);
                    }

                    gen = "M";
                    sqls = "INSERT INTO Table1 VALUES (\"" + fio + "\", \"" + dat + "\", \"" + gen + "\");";
                    sqlite3_exec(db, sqls.c_str(), callback, 0, &zErrMsg);
                }
                
                break;


            case 5:  // функция вывода определённых заданием записей
                cout << "|Name|    Birth   | G |" << endl;
                sqls = "SELECT * FROM Table1  WHERE FIO LIKE \"F%\" AND Gender like \"M\" ;";
                start = clock();  //начало записи времени
                sqlite3_exec(db, sqls.c_str(), callback, 0, &zErrMsg);
                end = clock();  //конец записи времени

                printf("Time is %.04f second(s)\n", (((double)end - start) / ((double)CLOCKS_PER_SEC)));

                break;


            case 6:  //дополнительная функция, не предусмотренная заданием, которая имеет место быть среди основных
                //функция для сброса таблицы с данными
                sqlite3_exec(db, "DROP TABLE IF EXISTS Table1;", callback, 0, &zErrMsg);
                break;


            default:
                cout << "Error, try again\n";
                break;
            }
        }
        else
        {
            if (zapros == "info") {  //вывод команд, доступных для управления программой
                info();
            }
        }
            cout << "Done" << endl;  //обозначение для пользователя, что он может делать новый вызов
    
    }
    sqlite3_close(db);
}