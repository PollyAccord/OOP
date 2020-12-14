#ifndef DIALOG_ADD_H
#define DIALOG_ADD_H
#include "exercises.h"
#include "exerciseslink.h"
#include "listexercises.h"
#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class Dialog_Add;
}

class Dialog_Add : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Add(QWidget *parent = nullptr, Exercises* exer=NULL, int type=0);
     Exercises *getExercise() const;
    ~Dialog_Add();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_type_currentIndexChanged(int index);

private:
    Ui::Dialog_Add *ui;
    Exercises *exercise;
    void setDialogWindow(int type_);
    void setValues();
    int type_;
};

#endif // DIALOG_ADD_H
