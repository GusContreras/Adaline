#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Init errorX
    count = 0;

    // error graph
    ui->errorPlot->addGraph();
    ui->errorPlot->xAxis->setRange(0,200);
    ui->errorPlot->yAxis->setRange(0,0.6);

    //initial factor and iterations
    ui->inputF->setText("0.5");
    ui->inputG->setText("30");
    ui->inputE->setText("0.008");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_inicializar_clicked()
{
    adalin.rand();
    printWn();
}

void MainWindow::on_loadFile_clicked()
{
    QString filename =  QFileDialog::getOpenFileName(
          this,
          "Open Document",
          QDir::currentPath(),
          "All files (*.*) ;; Document files (*.doc *.rtf);; PNG files (*.png)");

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
    }

    QStringList wordList;
    QString line;
    while (!file.atEnd()) {
        line = file.readLine();
        wordList = line.split(',');

        Point dat = Point(wordList);
        pointVector.append(dat);

    }
    adalin = Adaline(wordList.length());

    qDebug() << "Archivo Cargado";
}

void MainWindow::on_ADALINE_clicked()
{
    clearError();
    QString fString = ui->inputF->text();
    QString GS = ui->inputG->text();
    QString Dstring = ui->inputE->text();

    double factor = fString.toDouble();
    int G = GS.toInt();
    double desired = Dstring.toDouble();

    if(fString == "")
    {
        factor = 0.5;
        ui->inputF->setText("0.5");
    }
    if(GS == "")
    {
        G = 30;
        ui->inputG->setText("800");
    }
    if(Dstring == "")
    {
        desired = 0.008;
    }

    ui->errorPlot->xAxis->setRange(0,G);
    int iteraciones;
    double done = false;
    double error;
    double cont;

    for(int r = 0; r < G; r++)
    {

        cont = 0.0;

        for(int i=0; i < pointVector.size(); i++)
        {

            double s =  adalin.functionS(pointVector[i].Data);
            error = double(pointVector[i].Class) - s;
            adalin.updateA(pointVector[i].Data,factor,error);
            cont += error * error;

        }

        cont = cont / double(pointVector.size());
        errorY.append(double(cont));
        errorX.append(count);
        count++;

        printWn();
        ui->outputIteracion->setText(" Error: " + QString::number(cont));

        plotError();
        if(cont < desired)
        {
            done = true;
            iteraciones = r;
            break;
        }
    }
    if(done)
    {
        QString respuesta = "Se alcanzó el error deseado en " + QString::number(iteraciones) + " iteraciones";
        ui->outputIteracion->setText(respuesta);
    }
    else
    {
        QString respuesta = "El Adaline No alcanzó el error deseado, el error alcanzado es de: " + QString::number(cont);
        ui->outputIteracion->setText(respuesta);
    }
}

void MainWindow::on_clasificar_clicked()
{
    double x1,x2,x3,x4;
    QVector<double> vect;
    x1 = ui->inputX1->text().toDouble();
    x2 = ui->inputX2->text().toDouble();
    x3 = ui->inputX3->text().toDouble();
    x4 = ui->inputX4->text().toDouble();

    vect.append(x1);
    vect.append(x2);
    vect.append(x3);
    vect.append(x4);
    vect.append(-1.0);

    int test = adalin.functionZ(vect);
    if(test > 0.0)
    {
        ui->outputResultado->setText("El billete es Falso");
    }
    else
    {
        ui->outputResultado->setText("El billete es Verdadero");
    }
}

void MainWindow::plotError()
{
    ui->errorPlot->graph(0)->setData(errorX,errorY);
    ui->errorPlot->replot();
    ui->errorPlot->update();
}

void MainWindow::clearError()
{
    ui->errorPlot->graph(0)->data()->clear();
    ui->errorPlot->replot();
    ui->errorPlot->update();

    errorX.clear();
    errorY.clear();
    count = 0;
}

void MainWindow::printWn()
{
    ui->outputW0->setText("W0 = " + QString::number(adalin.weights[4]));
    ui->outputW1->setText("W1 = " + QString::number(adalin.weights[0]));
    ui->outputW2->setText("W2 = " + QString::number(adalin.weights[1]));
    ui->outputW3->setText("W3 = " + QString::number(adalin.weights[2]));
    ui->outputW4->setText("W4 = " + QString::number(adalin.weights[3]));
}
