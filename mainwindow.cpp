#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFile"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonArray"

extern QString filepath;
QString filepath = "C:/Users/Oscar/Desktop/ordine_tabacco/database.json";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString val;
    QFile file;
    file.setFileName(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray sigarette = jsonObject["elenco"].toArray();
    QJsonArray sigaretti = jsonObject["SIGARETTI"].toArray();
    QJsonArray tabacco = jsonObject["TABACCO"].toArray();

    for (int i=0; i<sigarette.size(); i++) {
        QJsonObject tmp = sigarette.at(i).toObject();
        ui->tableWidget->insertRow(i);
        QTableWidgetItem *item =  new QTableWidgetItem(tmp["nome"].toString());
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i, 0, item);
    }

    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->resizeColumnsToContents();

}

MainWindow::~MainWindow()
{
    delete ui;
}

