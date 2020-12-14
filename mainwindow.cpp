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
    ui->listWidget->resizeMode();
    //  ui->listWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //  ui->listWidget.set ->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item) {
    Exercises *exercise = list->GetExercise(int (ui->listWidget->currentItem()->text().toInt())); //надо получить индекс элемента
    int k;
    if (!exercise)
        k = 0;
    else
        k = exercise->getType()+1;
    Dialog_Add d(this, exercise, k);
    if (d.exec()) {
        list->SetExercise(int (ui->listWidget->currentItem()->text().toInt()), d.getExercise());
        setListWidget(list->getLength());
    }
}

void MainWindow::TotalTime() {
    double sum = 0;
    for (auto i = 0; i<list->NumberOfExercises(); i++) {
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

//Изменение размеров коллекции
void MainWindow::setListWidget(int n) {
        if (n>0) {
            ui->listWidget->setCurrentRow(n);
            QListWidgetItem *item = 0;
            for (int i = 0; i<n; i++) {
             //  item = new QListWidgetItem(QString().setNum(i), list);
               // item->setFlags(item->flags() | Qt::ItemIsEditable);
                QAbstractItemModel *model = ui->listWidget->model();
                model->setData(model->index(i,0), QStringLiteral("#%1").arg(i));
                ui->listWidget->item(i)->setFlags(Qt::ItemIsEnabled);

//              QListWidgetItem* newItem1 = new QListWidgetItem();
//                newItem1->setText("Упражнение №"+QString::number(i+1));
//                ui->listWidget->addItem(newItem1);
//                ui->listWidget->item(i)->setFlags(Qt::ItemIsEnabled);
            }
        }
    ui->count->setText(QString::number(n));
    ui->clearall->setEnabled(true);
}

void MainWindow::on_pushButton_clicked() {
    aim = ui->aim->value();
    QMessageBox::warning(this, "Message", "Цель задана!");
    ui->aim->setEnabled(0);
    ui->pushButton->setEnabled(0);
    ui->label_9->setText(QString::number(aim));
}

//загрузка файла
void MainWindow::on_readfile_clicked() {
    QString filename = QFileDialog::getOpenFileName(this, "Open MeteostationCollection", ".", "JSON files (*.json)");
    if (filename.isEmpty())
        QMessageBox::critical(this, "Error", "File is empty!");
    else
        try {
        ListExercises* templist = new ListExercises(ListFromJson(filename));
        if (list)
            delete list;
        list = templist;
        int n = list->getLength();
        setListWidget(n);
        ui->clearall->setEnabled(true);
        ui->delete_2->setEnabled(true);
    }  catch (std::exception) {
        QMessageBox::critical(this, "Error", "Error reading the file!");
    }
}

//сохранение файла
void MainWindow::on_savefile_clicked() {
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

int MainWindow::getRowNumber() const {
    return ui->size->text().toInt();
}

void MainWindow::on_pushButton_2_clicked() {
    int n = getRowNumber();
    if (list)
        delete list;
    if (n <=0) {
        QMessageBox::critical(this, "Error", "Impossible size!");
    }
    else {
        list = new ListExercises(n);
        setListWidget(n);
    }
}

void MainWindow::on_clearall_clicked() {
    delete list;
    setListWidget(0);
    ui->count->setText(0);
    ui->clearall->setEnabled(false);
    ui->delete_2->setEnabled(false);
}

void MainWindow::on_delete_2_clicked() {
    list->deleteExercise(int (ui->listWidget->currentItem()->text().toInt()));
    setListWidget(list->NumberOfExercises());
}
