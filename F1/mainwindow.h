#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLineEdit;
class QPushButton;
class QTableWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void browseDirectory();
    void startSearch();

private:
    void searchFiles(const QString &dirPath, const QString &pattern);

    QLineEdit *dirEdit;
    QLineEdit *filterEdit;
    QPushButton *browseBtn;
    QPushButton *searchBtn;
    QTableWidget *table;
};

#endif
