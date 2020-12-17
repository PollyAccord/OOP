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
#include <QTableWidgetItem>
#include "exercises.h"
#include "exerciseslink.h"
#include "listexercises.h"
#include "QListWidgetItem"

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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void TotalCalories();
    void TotalTime();

    int getRowNumber() const;

    void on_clearall_clicked();

    void on_add_button_clicked();

    void on_type_currentIndexChanged(int index);

    void on_delete_2_clicked();

    void on_restart_clicked();

    void on_action_triggered();

    void on_action_2_triggered();

private:
    Ui::MainWindow *ui;
    ListExercises *list;
    double aim;
    int type_ = 0;
};
#endif // MAINWINDOW_H
