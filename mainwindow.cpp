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

    ui->radioButton->setChecked(true);

    QString val;
    QFile file;
    file.setFileName(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray sigarette = jsonObject["elenco"].toArray();
    double tot_kg = 0.0;

    for (int i=0; i<sigarette.size(); i++) {
        QJsonObject tmp = sigarette.at(i).toObject();
        ui->tableWidget->insertRow(i);
        QTableWidgetItem *item =  new QTableWidgetItem(tmp["nome"].toString());
        item->setTextAlignment(Qt::AlignCenter);
        QTableWidgetItem *item_2 =  new QTableWidgetItem(tmp["codice"].toString());
        item_2->setTextAlignment(Qt::AlignCenter);
        if (tmp["quantita"].toString().toInt() != 0){
            QTableWidgetItem *item_3 =  new QTableWidgetItem(tmp["quantita"].toString());
            item_3->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i, 2, item_3);
            QTableWidgetItem *item_5 =  new QTableWidgetItem(tmp["totale"].toString());
            item_5->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i, 3, item_5);
            tot_kg += tmp["totale"].toString().toDouble();
        }

        ui->tableWidget->setItem(i, 0, item);
        ui->tableWidget->setItem(i, 1, item_2);
    }

    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();

    ui->label_2->setText(QString::number(tot_kg) + "kg");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refresh(){

    double tot = 0.0;

    QString val;
    QFile file;
    file.setFileName(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray sigarette = jsonObject["elenco"].toArray();

    for (int i=0; i<sigarette.size(); i++) {
        QJsonObject tmp = sigarette.at(i).toObject();
        if (tmp["quantita"].toString().toInt() != 0){
            QTableWidgetItem *item =  new QTableWidgetItem(tmp["quantita"].toString());
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i, 2, item);
            QTableWidgetItem *item_2 =  new QTableWidgetItem(tmp["totale"].toString());
            item_2->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i, 3, item_2);
            tot += tmp["totale"].toString().toDouble();
        }
        else{
            ui->tableWidget->setItem(i, 2, nullptr);
            ui->tableWidget->setItem(i, 3, nullptr);
        }
    }

    ui->label_2->setText(QString::number(tot) + "kg");
}

void MainWindow::add(int n){

    QString val;
    QFile file;
    file.setFileName(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray sigarette = jsonObject["elenco"].toArray();

    QJsonObject tmp = sigarette[ui->tableWidget->currentRow()].toObject();
    tmp["quantita"] = QString::number(tmp["quantita"].toString().toInt() + n);
    if (ui->radioButton->isChecked())
        tmp["totale"] = QString::number(tmp["totale"].toString().toDouble() + n*0.2);
    if (ui->radioButton_2->isChecked())
        tmp["totale"] = QString::number(tmp["totale"].toString().toDouble() + n*0.3);
    if (ui->radioButton_3->isChecked())
        tmp["totale"] = QString::number(tmp["totale"].toString().toDouble() + n*ui->lineEdit->text().toDouble());
    sigarette.replace(ui->tableWidget->currentRow(), tmp);

    jsonObject.insert("elenco", sigarette);
    jsonResponse.setObject(jsonObject);
    file.open(QIODevice::ReadWrite | QIODevice::Text| QFile::Truncate);
    file.write(jsonResponse.toJson());
    file.close();

    refresh();
}

void MainWindow::on_pushButton_3_clicked()
{
    add(-1);
}


void MainWindow::on_pushButton_2_clicked()
{
    add(1);
}


void MainWindow::on_pushButton_4_clicked()
{
    add(2);
}


void MainWindow::on_pushButton_5_clicked()
{
    add(-2);
}


void MainWindow::on_pushButton_6_clicked()
{
    add(5);
}


void MainWindow::on_pushButton_7_clicked()
{
    add(-5);
}


void MainWindow::on_pushButton_clicked()
{
    QString val;
    QFile file;
    file.setFileName(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray sigarette = jsonObject["elenco"].toArray();

    QJsonObject tmp = sigarette[ui->tableWidget->currentRow()].toObject();
    tmp["quantita"] = QString::number(0);
    tmp["totale"] = QString::number(0);
    sigarette.replace(ui->tableWidget->currentRow(), tmp);

    jsonObject.insert("elenco", sigarette);
    jsonResponse.setObject(jsonObject);
    file.open(QIODevice::ReadWrite | QIODevice::Text| QFile::Truncate);
    file.write(jsonResponse.toJson());
    file.close();

    refresh();
}


void MainWindow::on_radioButton_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit->setDisabled(true);
}


void MainWindow::on_radioButton_2_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit->setDisabled(true);
}


void MainWindow::on_radioButton_3_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit->setEnabled(true);
}


void MainWindow::on_pushButton_8_clicked()
{
    QString val;
    QFile file;
    file.setFileName(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray sigarette = jsonObject["elenco"].toArray();

    for (int i=0; i<sigarette.size(); i++) {
        QJsonObject tmp = sigarette[i].toObject();
        tmp["quantita"] = QString::number(0);
        tmp["totale"] = QString::number(0);
        sigarette.replace(i, tmp);
    }

    jsonObject.insert("elenco", sigarette);
    jsonResponse.setObject(jsonObject);
    file.open(QIODevice::ReadWrite | QIODevice::Text| QFile::Truncate);
    file.write(jsonResponse.toJson());
    file.close();

    refresh();
}

