#include "dialog_add.h"
#include "ui_dialog_add.h"
#include "exercises.h"
#include "exerciseslink.h"
#include "listexercises.h"
#include "QString"
#include "QAbstractButton"


Dialog_Add::Dialog_Add(QWidget *parent,  Exercises* exer, int type) :
    QDialog(parent, Qt::WindowCloseButtonHint),
    ui(new Ui::Dialog_Add) {
    ui->setupUi(this);
    type_ = type;
    if (type==2)
        exercise = new ExercisesLink(*((ExercisesLink*)exer));

    else if (type==1)
        exercise = new Exercises(*exer);
    else
        exercise = NULL;
    ui->setupUi(this);
    //ui->name->setText(Exercises::NAME_DEFAULT);
    //ui->time->setValue(Exercises::TIME_DEFAULT);
    //ui->calories->setValue(Exercises::CALORY_DEFAULT);
    //ui->techniques->setText(ExercisesLink::LINK_DEFAULT);
    // setDialogWindow(type_);
    if (type_)
      setValues();
}

Dialog_Add::~Dialog_Add()
{
    if (exercise)
        delete exercise;
    delete ui;
}

void Dialog_Add::setValues() {
    ui->name->setText(QString::fromStdString(exercise->GetName()));
    ui->time->setValue(exercise->GetTime());
    ui->calories->setValue(exercise->GetCalory());
    if (type_ == 2) {
        ExercisesLink *link = (ExercisesLink*)exercise;
        ui->techniques->setText(QString::fromStdString(link->GetLink()));
       }
}

Exercises* Dialog_Add::getExercise() const {
    return exercise;
}

void Dialog_Add::setDialogWindow(int type) {
    ui->type->setCurrentIndex(type);
    int k = 1;
    if (type != 2)
        k = 0;
    ui->name->setVisible(k);
    ui->time->setVisible(k);
    ui->calories->setVisible(k);
    ui->label->setVisible(k);
    ui->label_3->setVisible(k);
    ui->label_4->setVisible(k);
    if (type == 0)
        k = 0;
    else
        k = 1;
    ui->techniques->setVisible(k);
    ui->label_5->setVisible(k);
}

void Dialog_Add::on_buttonBox_clicked(QAbstractButton *button) {
    if (button->text() == tr("Reset")) {
            setDialogWindow(type_);
            if (type_)
                setValues();
        }
        else if (button->text() == tr("Cancel")) {
            this->reject();
            this->close();
        }
        else {
            //Сохранить
            int type = ui->type->currentIndex();
            if (exercise)
                delete exercise;
            if (type == 0)
                exercise = NULL;
            else {
                std::string name = ui->name->text().toStdString();
                double time = ui->time->text().toDouble();
                double calory = ui->calories->text().toDouble();
                if (type == 2) {
                    std::string link = ui->techniques->text().toStdString();
                    exercise = new ExercisesLink(name, time, calory, link);
                }
                else
                    exercise = new Exercises(name, time, calory);
            }
            this->accept();
            this->close();
        }
    }

void Dialog_Add::on_type_currentIndexChanged(int index) {
    setDialogWindow(index);
}
