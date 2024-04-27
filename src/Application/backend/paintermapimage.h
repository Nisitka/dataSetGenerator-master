#ifndef PAINTERMAPIMAGE_H
#define PAINTERMAPIMAGE_H

#include <QObject>
#include <QImage>
#include <QColor>

#include "map.h"

class painterMapImage : public QObject
{
    Q_OBJECT

signals:
    //
    void finish();

    //
    void resized();

    // земля отредактирована
    void readyEditEarth(int idXo, int idYo, int size);

    // информируем об завершении создании текстуры для 3D рельефа
    void readyTexture(int idXo, int idYo, int numW, int numL);

public slots:

    //
    void updateFull();

    //
    void updateSizeMap();

    // поднять землю
    void upEarth(int idX, int idY, int R);

    // опустить землю
    void downEarth(int idX, int idY, int R);

    // расчет цвета пикселя всего изображения
    void run();

    // расчет выбранной области
    void runToRect(int idX, int idY, int w, int h);
    void runToRect(const QRect& rect);

    // расчет выбранных областей
    void runToRects(QRect* rects, int count);

    // узнать цвет по индексу высоты (и записать его в отправленную ячейку)
    void heightToColor(QColor* setColor, int numLayer);

    // создать текстуру для 3D карты
    void buildTexture();

    // установить область создания текстуры
    void setRectTexture(int idXo, int idYo, int numW, int numL);

public:
    // сформировать текстуру высоты рельефа в области
    QImage* buildImageEarth(const QRect& rect);

    //
    QImage* getImage();


    painterMapImage(Map*);

private:
    // область для создания текстуры 3D рельефа
    int idXo;
    int idYo;
    int numW;
    int numL;

    void updateSizeImage();

    QImage* img;
    Map* map;

    int Wmap;
    int Lmap;
    int Hmap;

    // вычислить цвет по высоте (т.е. номеру слоя)
    QColor colorHeight(int numLayer);
    int dHeight;
    const QVector <QColor> colors =
    {
        QColor(129, 203, 140), QColor(174, 225, 150), QColor(224, 245, 180),
        QColor(249, 244, 180), QColor(251, 228, 148), QColor(250, 216, 118),
        QColor(252, 189, 96),  QColor(254, 179, 96),  QColor(247, 153, 79),
        QColor(221, 128, 69),  QColor(209, 105, 54),  QColor(215, 92, 61),
        QColor(184, 40, 37),   QColor(169, 27, 27),   QColor(134, 21, 21),
    };

};

#endif // PAINTERMAPIMAGE_H