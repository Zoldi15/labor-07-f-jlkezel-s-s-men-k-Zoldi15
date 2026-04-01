#include "mainwindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QFileDialog>
#include <QDirIterator>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QProgressDialog>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    dirEdit = new QLineEdit(QDir::currentPath(), this);
    dirEdit->setPlaceholderText("Könyvtár útvonala...");

    browseBtn = new QPushButton("Tallózás", this);

    filterEdit = new QLineEdit(this);
    filterEdit->setPlaceholderText("Keresett szöveg (üres = minden fájl)");

    searchBtn = new QPushButton("Keresés", this);

    table = new QTableWidget(this);
    table->setColumnCount(2);
    table->setHorizontalHeaderLabels({"Fájlnév", "Méret (byte)"});
    table->horizontalHeader()->setStretchLastSection(true);

    QHBoxLayout *dirLayout = new QHBoxLayout;
    dirLayout->addWidget(dirEdit);
    dirLayout->addWidget(browseBtn);

    QHBoxLayout *searchLayout = new QHBoxLayout;
    searchLayout->addWidget(filterEdit);
    searchLayout->addWidget(searchBtn);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(dirLayout);
    mainLayout->addLayout(searchLayout);
    mainLayout->addWidget(table);

    central->setLayout(mainLayout);

    connect(browseBtn, &QPushButton::clicked,
            this, &MainWindow::browseDirectory);

    connect(searchBtn, &QPushButton::clicked,
            this, &MainWindow::startSearch);
}

MainWindow::~MainWindow() {}

void MainWindow::browseDirectory()
{
    QString dir = QFileDialog::getExistingDirectory(
        this,
        "Válassz könyvtárat",
        dirEdit->text()
        );

    if (!dir.isEmpty())
        dirEdit->setText(dir);
}

void MainWindow::startSearch()
{
    table->setRowCount(0);

    searchFiles(dirEdit->text(), filterEdit->text());
}

void MainWindow::searchFiles(const QString &dirPath, const QString &pattern)
{
    QDirIterator it(dirPath, QDir::Files, QDirIterator::Subdirectories);

    int total = 0;
    while (it.hasNext()) {
        it.next();
        total++;
    }

    QProgressDialog progress("Fájlok feldolgozása...", "Mégse", 0, total, this);
    progress.setWindowModality(Qt::WindowModal);

    QDirIterator it2(dirPath, QDir::Files, QDirIterator::Subdirectories);

    int processed = 0;

    while (it2.hasNext()) {

        QString filePath = it2.next();
        QFileInfo info(filePath);
        QFile file(filePath);

        bool match = false;

        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {

            QTextStream in(&file);
            QString content = in.readAll();

            if (pattern.isEmpty()) {
                match = true;
            } else {
                match = content.contains(pattern.trimmed(), Qt::CaseInsensitive);
            }

            file.close();
        }

        if (match) {
            int row = table->rowCount();
            table->insertRow(row);

            table->setItem(row, 0, new QTableWidgetItem(info.fileName()));
            table->setItem(row, 1, new QTableWidgetItem(QString::number(info.size())));
        }
    }
}
