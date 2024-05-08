#include "gis.h"

#include <QDebug>

GIS::GIS()
{
    // Отвечает за работу с рельефом карты
    geoBuilder = new geoGenerator(currentW, currentH);
    connect(geoBuilder, SIGNAL(buildFinish(int,int,int)),
            this,       SLOT(setMapSize(int,int,int)));
    connect(geoBuilder, SIGNAL(buildFinish(int,int,int)),
            this,       SIGNAL(finishBuildMap(int,int,int)));

    Map* map = geoBuilder->getMap();

    // Отвечает за отрисовку подложки
    backPainter = new painterMapImage(map, currentW, currentH);
    backgroundImg = backPainter->getImage();

    // По умолчанию находимся в левом верхнем углу
    idXpos = 0; idYpos = 0;
}

GISInformer* GIS::Informer() /* const */
{
    return this;
}

void GIS::getIdActionArea(int &idXo, int &idYo) const
{
    idXo = idXpos;
    idYo = idYpos;
}

int GIS::getH(int idX, int idY, int units) const
{
    return geoBuilder->getH(idX, idY, units);
}

Coords GIS::getCoords(int idX, int idY) const
{
    return geoBuilder->getCoords(idX, idY);
}

const QImage& GIS::getGeoImage() const
{
    return *backPainter->getImage();
}

void GIS::setPosActionArea(int idXmap, int idYmap)
{
    int posX, posY;

    posX = idXmap - (currentW / 2);
    posY = idYmap - (currentH / 2);

    // Крайнее положения
    if (posX < 0) posX = 0;
    if (posY < 0) posY = 0;
    if (posX + currentW > Wmap) posX = Wmap - currentW;
    if (posY + currentH > Lmap) posY = Lmap - currentH;

    idXpos = posX;
    idYpos = posY;

    // Адоптируем все компоненты под новую область
    initActionArea();

    // Сигнализируем об готовности новой области
    changedActionArea(idXpos, idYpos);
}

void GIS::setMapSize(int W, int L, int H)
{
    Wmap = W;
    Lmap = L;
    Hmap = H;
}

void GIS::movePosActionArea(int dX, int dY)
{
    int posX, posY;

    posX = idXpos + dX;
    posY = idYpos + dY;

    // Крайние положения
    if (posX < 0) posX = 0;
    if (posY < 0) posY = 0;
    if (posX + currentW > Wmap) posX = Wmap - currentW;
    if (posY + currentH > Lmap) posY = Lmap - currentH;

    idXpos = posX;
    idYpos = posY;

    // Адоптируем все компоненты под новую область
    initActionArea();

    // Сигнализируем об готовности новой области
    changedActionArea(idXpos, idYpos);
}

void GIS::initActionArea()
{
    geoBuilder->setPosActionArea(idXpos, idYpos);

    backPainter->setPosArea(idXpos, idYpos);
    backPainter->updateFull();
}

void GIS::openMap(const QString &dirNameFile)
{
    //geoBuilder->openMap(dirNameFile);
    initActionArea();
}

void GIS::loadTerrain(const QString &dirNameFile)
{
    geoBuilder->loadTerrain(dirNameFile);
    initActionArea();
}

void GIS::setDefaultMap()
{
    geoBuilder->buildFlatMap(currentW, currentH);
    initActionArea();
}

QImage* GIS::getBackgroundImg()
{
    return backgroundImg;
}

////////// ВРЕМЕННО
Map* GIS::getMap()
{
    return geoBuilder->getMap();
}

void GIS::updateFromRect(const QRect &rect)
{
    backPainter->runToRect(rect);

    changedMap(rect.x(),     rect.y(),
               rect.width(), rect.height());
}

void GIS::updateFromRect(int idX, int idY, int w, int h)
{
    backPainter->runToRect(idX-idXpos, idY-idYpos, w, h);

    changedMap(idX, idY, w, h);
}

void GIS::updateFromRects(QRect *rects, int countS)
{
    backPainter->runToRects(rects, countS);

    changedMap();
}

void GIS::upEarth(int idX, int idY, int R)
{
    int idXo = idX - (R / 2);
    int idYo = idY - (R / 2);
    geoBuilder->editEarth(idXo, idYo, R, R, 1);

    backPainter->runToRect(QRect(idXo-idXpos, idYo-idYpos, R, R));

    changedMap(idXo, idYo, R, R);
}

void GIS::downEarth(int idX, int idY, int R)
{
    int idXo = idX - (R / 2);
    int idYo = idY - (R / 2);
    geoBuilder->editEarth(idXo, idYo, R, R, 3, Map::down);

    backPainter->runToRect(QRect(idXo-idXpos, idYo-idYpos, R, R));

    changedMap(idXo, idYo, R, R);
}
