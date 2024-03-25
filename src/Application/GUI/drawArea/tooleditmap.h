#ifndef TOOLEDITMAP_H
#define TOOLEDITMAP_H

#include "GUI/drawArea/drawareatool.h"

#include <QWheelEvent>
#include <QPixmap>

class ToolEditMap: public drawAreaTool
{
    Q_OBJECT
signals:
    // Поднять землю в указанной области
    void upEarth(int idX, int idY, int R);

    // Опустить землю в указанной области
    void downEarth(int idX, int idY, int R);

public:
    ToolEditMap(areaDrawWidget*, int id);

    void mousePress(QMouseEvent* mouse) override;
    void mouseRelease(QMouseEvent* mouse) override;
    void mouseMove(QMouseEvent* mouse) override;
    void wheelEvent(QWheelEvent *event) override;

    void procDrawTask(QPainter& painter) override;

    void init() override;
    void end() override;

private:
    //
    void editEarth();

    //
    void updateSizeCursor();

    QPixmap upCurPixmap;
    QPixmap downCurPixmap;
    QPixmap moveCurPixmap;

    // Размер кисти
    int r;
    int R; // размер курсора инструмента

    int const minSIZE = 4;
};

#endif // TOOLEDITMAP_H
