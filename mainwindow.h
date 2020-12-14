#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QHeaderView>
#include <QStringLiteral>
#include <QAbstractItemModel>
#include <QFileDialog>
#include <QString>
#include <QJsonParseError>
#include <QMessageBox>
#include <QListWidgetItem>
#include "exercises.h"
#include "exerciseslink.h"
#include "listexercises.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = NULL);
    ~MainWindow();

private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void setListWidget(int n);

    void on_pushButton_clicked();

    void on_readfile_clicked();

    void on_savefile_clicked();

    void on_pushButton_2_clicked();

    void TotalCalories();
    void TotalTime();


    int getRowNumber() const;

    void on_clearall_clicked();

    void on_delete_2_clicked();

private:
    Ui::MainWindow *ui;
    ListExercises *list;
    int aim;
};
#endif // MAINWINDOW_H
