#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QStringList>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void showNewQuote();

private:
    void loadQuotes();
    void showRandomQuote();
    QString getRandomQuote();

    QLabel *quoteLabel;
    QPushButton *button;

    QStringList quotes;
    int lastIndex = -1;
};

#endif
