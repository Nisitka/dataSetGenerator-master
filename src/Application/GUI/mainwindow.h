#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>

#include <QDockWidget>

#include "visualinfowidget.h"
#include "optmapgeneratorwindow.h"

namespace Ui {
class mainWindow;
}

class mainWindow : public QMainWindow
{
    Q_OBJECT

signals:


public:
    explicit mainWindow(QWidget *parent = 0);

    void addTask(QWidget* widget,
                 const QPixmap& pix,
                 const QString& nameButton,
                 const QString& nameWindow,
                 Qt::DockWidgetArea showPosition = Qt::TopDockWidgetArea);

    ~mainWindow();

private slots:


private:
    // панели окон
    QToolBar* toolBar; //

    // окно визулизатора данных
    QDockWidget* dockVisualInfo;

    Ui::mainWindow *ui;
};

#endif // MAINWINDOW_H
