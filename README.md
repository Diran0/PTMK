# PTMK
Выполнение тестового задания на вакансию Программист (Junior - младший разработчик)

----------------------------------------------------------------------------------

В папке ProgramCpp содержатся все файла, которые использовались для проекта в Visual Studio. \
  Файл ProgramCpp/ProgramCpp.cpp содержит весь написанный код программы. \
В папке Debug содержится готовый .exe файл для запуска программы, а также пустая база данных с названием, которое используется в данной программе. \
\
-----------------------------------------------------------------------------------  \
\
Инструкция по использованию программы:  \
При запуске открывается консольное окно с info-списком всех доступных пользователю команд: \
    info - Заново открывает список доступных команд\
    myApp 1 - В базе данных создаётся таблица, согласно заданию\
    myApp 2 ХХХ ХХХХ-ХХ-ХХ Х - В таблицу, если она создана, добавляется записть с указанными данными в формате ФИО ГГГГ-ММ-ДД П\
    myApp 3 - Выводится полная таблица, отсортированная по ФИО, в которую добавлен возраст\
    myApp 4 - Добавление в таблицу 100 записей, имеющих вид Fxx xxxx-xx-xx M (Мужского пола с фамилией начинающейся на Ф)\
По желаню также можно включить добавление 1.000.000 случайных записей (с годом рождения от1930 до 2009), однако это очень долгий процесс, который может занять несколько часов.\
    myApp 5 - Отображение из таблицы записей в формате Fxx xxxx-xx-xx M (Мужского пола с фамилией начинающейся на Ф) и время, ушедшее на это.\
    myApp 6 - Удаление таблицы с данными\
    exit - закрытие программы\
После каждого использования команды пользователю выводится на экран Done, что означает, что программа котова принимать следующую команду.\
\
--------------------------------------------------------------------------------------\
\
Тестовое задание заключается в следующем:
Написать консольное приложение или php скрипт, который будет запускаться из консоли.
По каждому пункту оно должно принимать параметр командной строки и выполнять соответствующий пункт.
По ходу задания будут примеры. Для ФИО использовать английский язык. Решать проблему с отображением русского языка в консоли, если возникает, не нужно.
Приложение/скрипт должно подключаться к базе данных.

В качестве СУБД можно использовать любую SQL СУБД или MongoDB.
В качестве среды разработки можете использовать любой известный вам язык программирования.

В приложении должно быть:
1. Создание таблицы с полями представляющими ФИО, дату рождения, пол.

Пример запуска приложения:
myApp 1
Для php:
php myApp.php 1
Для java:
java myApp.class 1
или
java myApp.jar 1

2. Создание записи. Использовать следующий формат:
myApp 2 ФИО ДатаРождения Пол

3. Вывод всех строк с уникальным значением ФИО+дата, отсортированным по ФИО , вывести ФИО, Дату рождения, пол, кол-во полных лет.
Пример запуска приложения:
myApp 3

4. Заполнение автоматически 1000000 строк. Распределение пола в них должно быть относительно равномерным, начальной буквы ФИО также. Заполнение автоматически 100 строк в которых пол мужской и ФИО начинается с "F".
Пример запуска приложения:
myApp 4

5. Результат выборки из таблицы по критерию: пол мужской, ФИО начинается с "F". Сделать замер времени выполнения.
Пример запуска приложения:
myApp 5
Вывод приложения должен содержать время.

6. Произвести определенные манипуляции над базой данных для ускорения запроса из пункта 5. Убедиться, что время исполнения уменьшилось. Объяснить смысл произведенных действий. Предоставить результаты замера до и после.
\
-----------------------------------------------------------------------------\
\
При выполнении задания не было определено, какие манипуляции можно совершить для ускорения пункта 5. В любом случае для базы данных на 100 кортежей время первого вызова команды было в промежутке от 0.042 до 0.051 сек.\
