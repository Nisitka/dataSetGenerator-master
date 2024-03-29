#ifndef DRAWAREATOOL_H
#define DRAWAREATOOL_H

#include <QMouseEvent>
#include <QCursor>
#include <QObject>
#include <QToolButton>

#include "drawtask.h"

class areaDrawWidget;

class drawAreaTool: public QObject
{
    Q_OBJECT
signals:
    //
    void pickSignal(int id);

public slots:
    // Назначить инструмент выбранным
    void assign();

public:
    drawAreaTool(areaDrawWidget*, int id, QObject *parent = 0);

    int getId() const;

    enum keyMouse{left, right, mid};
    enum statusMouse{press, release};

    virtual void mousePress(QMouseEvent* mouse) = 0;
    virtual void mouseRelease(QMouseEvent* mouse) = 0;
    virtual void mouseMove(QMouseEvent* mouse) = 0;

    virtual void procDrawTask() { /* ... */ }

    virtual void wheelEvent(QWheelEvent *event);

    virtual void init();
    virtual void end() = 0;

    void getCoordMouse(int& idX, int& idY);

    int getStatMouse();
    int getLastKeyMouse();

    QToolButton* getButton();

protected:

    //
    void setButton(const QPixmap& pixButton, const QString& nameButton);

    //
    QToolButton* button;

    // Ключ  инструмента в drawArea
    int id;

    // Кнопки
    static int lastKeyMouse;
    static int statMouse;

    // Курсор
    static int xPressMouse; // последние координаты нажатия
    static int yPressMouse;
    static int xMouse;      // последние координаты (относительно карты)
    static int yMouse;
    static int xIdMouse;    // в индексах карты
    static int yIdMouse;
    static int pXo;         // левый верх-й угол карты при нажатии/отпускании мыши
    static int pYo;

    //
    int idX, idY;
    double k;

    // к чему принадлежат инструменты
    areaDrawWidget* drawArea;

    //
    QCursor cursor;

private:

};

#endif // DRAWAREATOOL_H
