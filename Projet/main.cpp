#include "mainwindow.h"
#include "uvmanager.h"
#include "exception.h"
#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Profiler profiler;
    profiler.show();
    return app.exec();
}
