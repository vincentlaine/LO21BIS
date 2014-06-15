#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>

class Profiler : public QMainWindow{
    Q_OBJECT
public:
    explicit Profiler(QWidget *parent = 0);
signals:
public slots:
    void openChargerUV();
    void openChargerCursus();
    void openUV();
    void ajoutUV();
    void openCursus();
    void ajoutCursus();
};

#endif // MAINWINDOW_H
