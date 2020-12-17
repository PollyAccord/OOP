#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "exercises.h"
#include "dialog_add.h"
#include "exerciseslink.h"
#include "listexercises.h"
#include <string.h>
#include <QHeaderView>
#include <QStringLiteral>
#include <QAbstractItemModel>
#include <QListWidgetItem>
#include <QFileDialog>
#include <QString>
#include <QJsonParseError>
#include <QMessageBox>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    list = NULL;
    ui->setupUi(this);
    ui->label_8->setVisible(false);
    ui->achieve->setVisible(false);
    ui->clearall->setEnabled(false);
    ui->delete_2->setEnabled(false);
    ui->pushButton_2->setEnabled(true);
    ui->name->setEnabled(false);
    ui->time->setEnabled(false);
    ui->calories->setEnabled(false);
    ui->techniques->setEnabled(false);
    ui->type->setVisible(false);
    ui->add_button->setVisible(false);
    //ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //  ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::TotalTime() {
    double sum = 0;
    for (auto i = 0; i<list->getLength(); i++) {
        sum += list->GetExercise(i)->GetTime();
    }
    ui->label_4->setText(QString::number(sum));
}

void MainWindow::TotalCalories() {
    double sum = 0;
    for (auto i = 0; i<list->NumberOfExercises(); i++) {
        sum += list->GetExercise(i)->GetTime()*list->GetExercise(i)->GetCalory();
    }
    ui->label_5->setText(QString::number(sum));
    ui->label_9->setText(QString::number(ui->aim->value() - sum));
    if (ui->label_9->text().toDouble() == 0) {
        ui->label_8->setVisible(1);
        ui->achieve->setVisible(1);
        ui->pushButton_2->setEnabled(false);
    }
}

void MainWindow::on_pushButton_clicked() {
    aim = ui->aim->value();
    QMessageBox::information(this, "Message", "Цель задана!");
    ui->aim->setEnabled(0);
    ui->pushButton->setEnabled(0);
    ui->label_9->setText(QString::number(aim));
}

int MainWindow::getRowNumber() const {
    return ui->size->text().toInt();
}

void MainWindow::on_pushButton_2_clicked() {
    int n = getRowNumber();
    ui->pushButton_2->setEnabled(false);
    ui->size->setEnabled(false);
    if (list)
        delete list;
    if (n <=0) {
        QMessageBox::critical(this, "Error", "Невозможное количество!");
        ui->size->setEnabled(true);
        ui->pushButton_2->setEnabled(true);
    }
    else {
        list = new ListExercises(n);
        ui->type->setVisible(true);
        ui->add_button->setVisible(true);
        QMessageBox::information(this, "Message", "Задано количество упражнений");
        //  ui->count->setText(QString::number(n));
        ui->clearall->setEnabled(true);
        ui->delete_2->setEnabled(true);
        ui->add_button->setEnabled(true);
        //setListWidget(n);
    }
}

void MainWindow::on_clearall_clicked() {
    for (int i; i<ui->size->text().toInt(); i++) {
        list->deleteExercise(i);
    }
    ui->listWidget->clear();
    // setListWidget(0);
    ui->count->setText("0");
    ui->clearall->setEnabled(false);
    ui->delete_2->setEnabled(false);
    ui->pushButton_2->setEnabled(true);
    ui->size->setEnabled(true);
}

void MainWindow::on_delete_2_clicked() {
    list->deleteExercise(ui->listWidget->currentRow());
}

void MainWindow::on_add_button_clicked() {
    std::string temp;
    // Exercises *exercise;
    // Dialog_Add d(this, exercise, 0);
    // Dialog_Add(this, exercise);
    list->getLength();
    type_ = ui->type->currentIndex();
    if (type_ == 1) {
        ui->count->setText(QString::number(ui->count->text().toInt()+1));
        std::string name = ui->name->text().toStdString();
        double time = ui->time->text().toDouble();
        double calories = ui->calories->text().toDouble();
        Exercises exercise(name, time, calories);
        temp = exercise.GetName()+", " + std::to_string(exercise.GetTime())+std::to_string(exercise.GetCalory());
        list->SetExercise(ui->count->text().toInt()-1, &exercise);
        ui->listWidget->addItem(temp.c_str());
    }
    else if (type_ == 2) {
        ui->count->setText(QString::number(ui->count->text().toInt()+1));
        std::string name = ui->name->text().toStdString();
        double time = ui->time->text().toDouble();
        double calories = ui->calories->text().toDouble();
        std::string link = ui->techniques->text().toStdString();
        ExercisesLink *exerlink;
        exerlink->SetName(name);
        exerlink->SetTime(ui->time->text().toDouble());
        exerlink->SetCalory(calories);
        exerlink->SetLink(link);
        std::cout << exerlink;
        temp = exerlink->GetName()+", " + std::to_string(exerlink->GetTime())+", "+std::to_string(exerlink->GetCalory())+", "+exerlink->GetLink();
        list->SetExercise(ui->count->text().toInt()-1, exerlink);
        ui->listWidget->addItem(temp.c_str());
    }
    if (ui->count->text().toInt() == list->getLength())
        ui->add_button->setEnabled(false);
    else
        ui->add_button->setEnabled(true);
}


void MainWindow::on_type_currentIndexChanged(int index) {
    type_ = index;
    if (type_ == 1) {
        ui->name->setEnabled(true);
        ui->time->setEnabled(true);
        ui->calories->setEnabled(true);
    }
    else if (type_ == 2) {
        ui->techniques->setEnabled(true);
        ui->name->setEnabled(true);
        ui->time->setEnabled(true);
        ui->calories->setEnabled(true);
    }
    else if (type_ == 0) {
        ui->name->setEnabled(false);
        ui->time->setEnabled(false);
        ui->calories->setEnabled(false);
        ui->techniques->setEnabled(false);
    }
}

void MainWindow::on_restart_clicked() {
    list = NULL;
    ui->label_8->setVisible(false);
    ui->achieve->setVisible(false);
    ui->clearall->setEnabled(false);
    ui->delete_2->setEnabled(false);
    ui->pushButton_2->setEnabled(true);
    ui->name->setEnabled(false);
    ui->time->setEnabled(false);
    ui->calories->setEnabled(false);
    ui->techniques->setEnabled(false);
    ui->type->setVisible(false);
    ui->aim->setEnabled(true);
    ui->pushButton->setEnabled(true);
    ui->size->setEnabled(true);
    ui->add_button->setVisible(false);
    ui->size->setValue(0);
    ui->aim->setValue(0);
    ui->label_9->setText("0");
    ui->name->setText("");
    ui->techniques->setText("");
    ui->time->setValue(0);
    ui->calories->setValue(0);
    on_clearall_clicked();
}

//открытие файла
void MainWindow::on_action_triggered() {
    QString filename = QFileDialog::getOpenFileName(this, "Open MeteostationCollection", ".", "JSON files (*.json)");
    if (filename.isEmpty())
        QMessageBox::critical(this, "Error", "File is empty!");
    else
        try {
        ListExercises* templist = new ListExercises(ListFromJson(filename));
        if (list)
            delete list;
        list = templist;
        ui->clearall->setEnabled(true);
        ui->delete_2->setEnabled(true);
    }  catch (std::exception) {
        QMessageBox::critical(this, "Error", "Error reading the file!");
    }
}

//сохранение файла
void MainWindow::on_action_2_triggered() {
    int i, j;
    QString filename = QFileDialog::getSaveFileName(this, "Save file", ".", "JSON files (*.json)");
    for (i=0; i<list->getLength() && list->GetExercise(i); i++);
    if (list->GetExercise(i) == NULL)
        QMessageBox::critical(this, "Error", "Unable to save such collection! Try again!");
    else {
        if (filename.isEmpty())
            QMessageBox::critical(this, "Error", "No collection!");
        else {
            if (list && filename.endsWith(".json"))
                ListToJson(filename, *list);
            else if (!filename.endsWith(".json"))
                QMessageBox::critical(this, "Error", "Unsuitable format!");

        }
    }
}
