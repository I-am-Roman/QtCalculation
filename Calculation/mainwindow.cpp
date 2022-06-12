#include "mainwindow.h"
#include "ui_mainwindow.h"
// помещаем сюда первое число, которое введено пользователем
double num_first;
// чтобы после выбора мат.операции число оставалось
bool math = false;
// Чтобы после нажатия '=' нельзя было приписать числа
bool new_num = false;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // теперь необходимо соединить нажатие на кнопку с методом
    // connect(Что за кнопка нажата (0), Что мы должны отследить (нажатие),
    // С каким объектом работаем (с этим), Какой слот должен выполниться(digits_numbers))
    connect(ui->pushButton0,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton1,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton2,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton3,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton4,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton5,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton6,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton7,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton8,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton9,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    // проделываем тоже самое с остальными методами: operations
    connect(ui->plus_of_minus,SIGNAL(clicked()),this,SLOT(operations()));
    connect(ui->percent,SIGNAL(clicked()),this,SLOT(operations()));
    //:math_operations
    connect(ui->plus,SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->minus,SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->multiply,SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->division,SIGNAL(clicked()),this,SLOT(math_operations()));

    // делаем возможным применять к кнопке метод true
    ui->division->setCheckable(true);
    ui->plus->setCheckable(true);
    ui->multiply->setCheckable(true);
    ui->minus->setCheckable(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

// нажатие на цифры
void MainWindow::digits_numbers()
{
    // метод sender() позволяет получить именно ту кнопку, которую мы нажали
    // переменная button будет унаследоваться от QPushButton
    //(QPushButton*) - результат, полученный с sender тожу будет преобразовываться к классу QPushButton
    QPushButton* button = (QPushButton*)sender();
    // для вывода
    QString new_label;
    // здесь мы будем хранить числа
    double all_numbers;
    // если мы посчитали число (нажали 0), но НИ ОДНА из математических функций не нажата
    if(new_num && (!(ui->plus->isChecked()|| ui->minus->isChecked()|| ui->division->isChecked()|| ui->multiply->isChecked())))
    {
        new_num = false;
        all_numbers = (button->text()).toDouble();
        new_label = QString::number(all_numbers,'g',8);
        ui->result_show->setText(new_label);
        return;
    }

    if(math)
    {
        math = false;
        // очищаем текст только тогда, когда вводим новые числа
        ui->result_show->setText("");
    }


    //чтобы 0.001 не сводилось при конфертировании к 0
    if(ui->result_show->text().contains(".")&& button->text()== "0" )
    {
        new_label = ui->result_show->text()+button->text();
    }   // если была нажата какая - либо из матемитических операций, не соединяем числа
    else
    {

        // берём у нажатых кнопок текст и добавляем к нему вновь нажатых
        all_numbers = (ui->result_show->text()+button->text()).toDouble();
        // чтобы вывести результат в виде string, нужно создать новую переменную
        // и присвоить ей трансформированный double, 15 - это количество чисел, способных жить без е
        new_label = QString::number(all_numbers,'g',8);
    }
    // выводим строку

    ui->result_show->setText(new_label);
}//digits_numbers

// функция математических операций
void MainWindow::math_operations()
{
    // при нажатии на любую кнопку мы первое число
    // будем помещать в первую переменную и всё
    QPushButton* button = (QPushButton*)sender();
    num_first = ui->result_show->text().toDouble();

    QString new_label;
    new_label = QString::number(num_first,'g',8);
    // когда будет введено первое число и выбрано действие, я хочу,
    // чтобы число не исчесло, а осталось
    ui->result_show->setText(new_label);
    // определяем, что за кнопка была нажата
    button->setChecked(true);

    math = true;
}//math_operations

// операции "+/-", "%"
void MainWindow::operations()
{
    QPushButton* button = (QPushButton*)sender();
    QString new_label;
    double all_numbers;
    // добавим проверку
    if(button->text() == "+/-")
    {
        all_numbers = (ui->result_show->text()).toDouble();
        all_numbers = all_numbers * -1;
        new_label = QString::number(all_numbers,'g',8);
        ui->result_show->setText(new_label);
    }
    if(button->text() == "%")
    {
        all_numbers = (ui->result_show->text()).toDouble();
        all_numbers = all_numbers * 0.01;
        new_label = QString::number(all_numbers,'g',8);
        ui->result_show->setText(new_label);
    }
}// operations

// нажатие на "."
void MainWindow::on_point_clicked()
{
    // если у нас не было до этого точки
    if(!(ui->result_show->text().contains('.')))
        ui->result_show->setText( ui->result_show->text()+".");

}//on_point_clicked

// нажатие на AC
void MainWindow::on_delete_2_clicked()
{
    // все кнопки дезактивируем
    ui->division->setChecked(false);
    ui->plus->setChecked(false);
    ui->multiply->setChecked(false);
    ui->minus->setChecked(false);
    ui->result_show->setText("0");
}//on_delete_2_clicked

// нажатие на равенство
void MainWindow::on_equal_clicked()
{
    double labelNumder, num_second;
    QString new_label;
    num_second = ui->result_show->text().toDouble();
    // наш флаг
    new_num = true;
    if(ui->plus->isChecked())   // П Л Ю С
    {
        labelNumder = num_first + num_second;
        new_label = QString::number(labelNumder,'g',8);
        if (new_label.size() > 14)  // стоит задумать, а что же это за число
        {
                new_label = QString::number(labelNumder,'f',3);
        }
        ui->result_show->setText(new_label);
        ui->plus->setChecked(false);
    }
    else if(ui->minus->isChecked()) // М И Н У С
    {
        labelNumder = num_first - num_second;
        new_label = QString::number(labelNumder,'g',12);
        if (new_label.size() > 14)  // стоит задумать, а что же это за число
        {
                new_label = QString::number(labelNumder,'f',3);
        }
        ui->result_show->setText(new_label);
        ui->minus->setChecked(false);
    }
    else if(ui->division->isChecked())  // Д Е Л Е Н И Е
    {
        if(num_second == 0)
        {
             ui->result_show->setText("0");
             ui->plus->setChecked(false);
        }
        else
        {
        labelNumder = num_first/num_second;
        new_label = QString::number(labelNumder,'g',8);
        if (new_label.size() > 14)  // стоит задумать, а что же это за число
        {
                new_label = QString::number(labelNumder,'f',3);

        }

        ui->result_show->setText(new_label);
        ui->division->setChecked(false);
        }
    }
    else if(ui->multiply->isChecked())  // У М Н О Ж Е Н И Е
    {
        labelNumder = num_first * num_second;
        new_label = QString::number(labelNumder,'g',8);
        if (new_label.size() > 14)  // стоит задумать, а что же это за число
        {
                new_label = QString::number(labelNumder,'f',3);
        }
        ui->result_show->setText(new_label);
        ui->multiply->setChecked(false);
    }

}//on_equal_clicked

