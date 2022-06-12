/*Что нужно:
 * 1) Дизайн в mainwindow.ui
 * 2) Создать класс в заголовочном файлу h.
 * 3) Обявить все интересующие методы
 * 4) Реализовать их в mainwindow.cpp
 * 5) Некоторые методы реализовать через cliced() ["удаление", "запятая", "равно"]
 * 6) Решить появившиеся баги
 * */
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Calculator");
    w.show();
    return a.exec();
}
