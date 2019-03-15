#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = NULL);
    ~MainWindow();

public:
    void paintEvent(QPaintEvent *);

private:
    int radius;

private:
    Ui::MainWindow *ui;

private slots:
    void on_horizontalSlider_valueChanged(int value);
};

#endif // MAINWINDOW_H
