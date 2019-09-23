#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "point.h"
#include "adaline.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_inicializar_clicked();

    void on_loadFile_clicked();

    void on_ADALINE_clicked();

    void on_clasificar_clicked();

private:
    Ui::MainWindow *ui;
    QVector<double> qv_x1, qv_y1;
    QVector<double> qv_x2, qv_y2;
    QVector<double> errorY, errorX;
    int count;
    Adaline adalin;
    QVector<Point> pointVector;
    void plotError();
    void clearError();
    void printWn();
};

#endif // MAINWINDOW_H
