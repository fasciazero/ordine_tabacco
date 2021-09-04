#include "mainwindow.h"
#include "ui_mainwindow.h"

extern QString filepath;
QString filepath = "C:/Users/Oscar/Desktop/ordine_tabacco/database.json";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

