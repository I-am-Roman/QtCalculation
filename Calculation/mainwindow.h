#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    // объявим метод, который будет наполнен необходимыми
    // функциями
    // потом все объявляенные функциин еобходимо будет реализовать в .cpp
private slots:
    // нажатие на числа
        void digits_numbers();
     // нажатие на точку
        void on_point_clicked();
    // операция "%" и "+/-"
        void operations();
    // очистка экрана
        void on_delete_2_clicked();
    // получение результата
        void on_equal_clicked();
    // математические операции "/", "х", "-", "+"
        void math_operations();
};
#endif // MAINWINDOW_H
