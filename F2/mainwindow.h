#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openFile();

private:
    void setupMenu();
    void loadCSV(const QString &filePath);

    QTableWidget *tableWidget;
};

#endif // MAINWINDOW_H
