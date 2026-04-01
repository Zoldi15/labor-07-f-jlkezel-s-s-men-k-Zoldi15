#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    tableWidget = new QTableWidget(this);
    setCentralWidget(tableWidget);

    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    setupMenu();
    resize(800, 600);
}

MainWindow::~MainWindow() {}

void MainWindow::setupMenu()
{
    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    QMenu *fileMenu = new QMenu("File", this);
    menuBar->addMenu(fileMenu);

    QAction *openAction = new QAction("Open File...", this);
    fileMenu->addAction(openAction);

    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Open CSV File",
        "",
        "CSV Files (*.csv)"
        );

    if (!fileName.isEmpty()) {
        loadCSV(fileName);
    }
}

void MainWindow::loadCSV(const QString &filePath)
{
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);

    tableWidget->clear();

    if (!in.atEnd()) {
        QString headerLine = in.readLine();
        QStringList headers = headerLine.split(",");

        tableWidget->setColumnCount(headers.size());
        tableWidget->setHorizontalHeaderLabels(headers);
    }

    int row = 0;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList values = line.split(",");

        tableWidget->insertRow(row);

        for (int col = 0; col < values.size(); col++) {
            tableWidget->setItem(row, col, new QTableWidgetItem(values[col]));
        }

        row++;
    }

    file.close();
}
