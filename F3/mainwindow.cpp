#include "mainwindow.h"

#include <QFile>
#include <QTextStream>
#include <QVBoxLayout>
#include <QRandomGenerator>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    quoteLabel = new QLabel("...", this);
    quoteLabel->setWordWrap(true);
    quoteLabel->setAlignment(Qt::AlignCenter);

    button = new QPushButton("Új idézet", this);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(quoteLabel);
    layout->addWidget(button);

    central->setLayout(layout);

    setStyleSheet(R"(
        QMainWindow {
            background-color: #1e1e2f;
        }

        QLabel {
            color: #ffffff;
            font-size: 20px;
            padding: 20px;
        }

        QPushButton {
            background-color: #4CAF50;
            color: white;
            font-size: 16px;
            padding: 10px;
            border-radius: 10px;
        }

        QPushButton:hover {
            background-color: #45a049;
        }
    )");

    loadQuotes();
    showRandomQuote();

    connect(button, &QPushButton::clicked,
            this, &MainWindow::showNewQuote);

    resize(500, 300);
}

void MainWindow::loadQuotes()
{
    QFile file("quotes.txt");

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (!line.isEmpty())
            quotes.append(line);
    }

    file.close();
}

QString MainWindow::getRandomQuote()
{
    if (quotes.isEmpty())
        return "Nincs idézet.";

    int index;

    do {
        index = QRandomGenerator::global()->bounded(quotes.size());
    } while (quotes.size() > 1 && index == lastIndex);

    lastIndex = index;
    return quotes[index];
}

void MainWindow::showRandomQuote()
{
    quoteLabel->setText(getRandomQuote());
}

void MainWindow::showNewQuote()
{
    showRandomQuote();
}
