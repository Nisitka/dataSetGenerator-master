#ifndef VISUALINFOWIDGET_H
#define VISUALINFOWIDGET_H

#include <QWidget>

#include <QPushButton>

#include "drawArea/areadrawwidget.h"
#include "backend/map.h"

namespace Ui {
class visualInfoWidget;
}

class visualInfoWidget : public QWidget
{
    Q_OBJECT
signals:  
    void saveMap_signal(const QString& dirFile);

    void setRectPredict(int idXo, int idYo); // дискрета левого верхнего угла

    void setPointsTrail(QPoint begin, QPoint last);

public slots:
    // установить выбранную РЛС
    void setCurRLS(int idRLS);

    // добавить РЛС для отрисовки на карте
    void addRLS(QPoint* posRLS, const QString& nameNewRLS);

    // удалить РЛС с отрисовки
    void delRLS(int indexRLS);

    //
    void updateImage();

public:
    explicit visualInfoWidget(QImage* geoMap,
                              Map* map,
                              QWidget *parent = 0);

    areaDrawWidget* getDrawArea();

    ~visualInfoWidget();

protected:
    virtual void mouseMoveEvent(QMouseEvent* mouseEvent);

private slots:
    void saveMap();
    void setDirNameMap();

    void showInfoCoord(double x, double y);
    void switchVisual(int idType);

    void saveImage();

    void setDirNameImg();

private:
    // настройка визуала
    void setDesine();

    // прогнозируется ли сейчас траектория
    bool isPredictTrail;
    //
    int sizeFilter = 2;
    int numCurPoint;

    // опции сохранения изображения
    enum optSaveImg{screen, full, curRect}; // скирншот, всю карту, выделенную область
    QStringList typeSaveImg = {"сриншот", "всю карту", "выд. область"};

    // названия форматов изображений
    QString formatsImg = "*.png ;; *.jpg ;; *.bmp";

    // выбранный формат для сохранения
    QString curFormat;

    // карта (рельеф)
    Map* map;
    QString mapFormat = ".txt";

    // виджет, на котором будет происходить отрисовка изоб.
    areaDrawWidget* drawArea;

    // типы изображений
    QStringList strTypeVisual = {"Рельеф",
                                 "Образ нейронной сети",
                                 "Целевую функцию"};

    QPushButton* lastButtonTool;

    Ui::visualInfoWidget *ui;
};

#endif // VISUALINFOWIDGET_H
