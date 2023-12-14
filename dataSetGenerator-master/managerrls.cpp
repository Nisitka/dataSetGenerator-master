#include "managerrls.h"

#include <QDebug>

#include <QRect>

managerRLS::managerRLS(Map* map_)
{
    map = map_;

    idCurRLS = -1;
}

void managerRLS::addRLS(QPoint* posRLS)
{
    RLS* rls = new RLS(map, posRLS);
    listRLS.append(rls);

    // завершение генерации вертикального сегмента
    connect(rls,  SIGNAL(readyVector(int)), // номер сегмента
            this, SLOT(readyVecRLS()));

    // запрос данных ЗО графика
    connect(rls,  SIGNAL(exportGraphicData(double*, double*, int)),
            this, SIGNAL(exportGraphicData(double*, double*, int)));

    // настройка пар-ов моделирования сигнала
    connect(rls,  SIGNAL(startSetOpt(int)),
            this, SIGNAL(startSetOpt(int)));
    connect(rls,  SIGNAL(readySetRay(int)),
            this, SIGNAL(readySetRay(int)));
    connect(rls,  SIGNAL(readyOptZDvert()),
            this, SIGNAL(readyOptZDvert()));

    createReadyRLS();
    qDebug() << "create RLS!";
}

void managerRLS::searchBestPosRLS(int idXo, int idYo, int W, int L, int idMaxH)
{
    startSearchBestPos(W, L, W*L);

    int countMaxZD = listRLS.at(idCurRLS)->getCountMaxBlocksZD();
    int countCurZD;
    double* pK = new double[W*L];
    double maxK = 0.0f;
    double k;
    int bestX, bestY;
    for (int x=0; x<W; x++)
    {
        for (int y=0; y<L; y++)
        {
            countCurZD = listRLS.at(idCurRLS)->getCurrentBlocksZD(idXo + x, idYo + y,
                                                                  idMaxH);
            k = (double) countCurZD / countMaxZD;
            pK[x*L + y] = k;

            if (k > maxK)
            {
                maxK = k;
                bestX = idXo + x;
                bestY = idYo + y;
            }
        }
    }

    readySearchBestPos(bestX, bestY, pK);
}

void managerRLS::updateVisInfoRLS()
{
    /*
    int idX, idY, w, h;
    listRLS.at(idCurRLS)->getRectPosition(idX, idY, w, h);
    updateVisInfoMap(idX, idY, w, h);
    */
    updateVisInfoMap(0, 0, map->getWidth(), map->getLength());
}

void managerRLS::delRLS(int id)
{
    RLS* rls = listRLS.at(id);

    int idX, idY, w, h;
    rls->getRectPosition(idX, idY, w, h);

    // завершение генерации вертикального сегмента
    disconnect(rls,  SIGNAL(readyVector(int)), // номер сегмента
               this, SLOT(readyVecRLS()));

    // запрос данных ЗО графика
    disconnect(rls,  SIGNAL(exportGraphicData(double*, double*, int)),
               this, SIGNAL(exportGraphicData(double*, double*, int)));

    // настройка пар-ов моделирования сигнала
    disconnect(rls,  SIGNAL(startSetOpt(int)),
               this, SIGNAL(startSetOpt(int)));
    disconnect(rls,  SIGNAL(readySetRay(int)),
               this, SIGNAL(readySetRay(int)));
    disconnect(rls,  SIGNAL(readyOptZDvert()),
               this, SIGNAL(readyOptZDvert()));

    delete rls;
    listRLS.removeAt(id);

    emitSignalAllRLS();
    updateVisInfoMap(idX, idY, w, h);
}

void managerRLS::setPositionRLS(int idX, int idY)
{
    RLS* rls = listRLS.at(idCurRLS);
    rls->clearZD();

    QRect* rects = new QRect[2]; // области, которые надо будет перерисовать
    int idXo, idYo, w, h;
    rls->getRectPosition(idXo, idYo, w, h);
    rects[0].setRect(idXo, idYo, w, h);

    rls->setPosition(idX, idY);
    emitSignalAllRLS(); // перемодулируем сигнал всех РЛС

    rls->getRectPosition(idXo, idYo, w, h);
    rects[1].setRect(idXo, idYo, w, h);
    updateVisInfoMap(rects, 2); // обновляем визуальную информацию на карте
}

void managerRLS::setRLS(int id)
{
    if (id >= 0)
    {
        idCurRLS = id;

        // обновляем график
        listRLS.at(idCurRLS)->getDataGraphic();

        // обновляем остальные данные об РЛС
        int Rmax, Xpos, Ypos, Hzd;
        bool working;
        listRLS.at(idCurRLS)->getOpt(Rmax, Xpos, Ypos, Hzd, working);
        updateOptGui(Rmax, Xpos, Ypos, Hzd, working);

        qDebug() << "set RLS: " << id;
    }
}

void managerRLS::offRLS()
{
    RLS* rls = listRLS.at(idCurRLS);

    rls->off();
    emitSignalAllRLS();

    // обновляем визуальную информацию на карте
    int idX, idY, w, h;
    rls->getRectPosition(idX, idY, w, h);
    updateVisInfoMap(idX, idY, w, h);
}

void managerRLS::emitSignalAllRLS()
{
    int sizeLoading = 0;
    for (int i=0; i<listRLS.size(); i++)
    {
        if (listRLS.at(i)->isWorking())
            sizeLoading += listRLS.at(i)->getCountHorVectors();
    }

    startGenerateZD(sizeLoading);
    curVecReady = 0;

    for (int i=0; i<listRLS.size(); i++)
    {
        listRLS.at(i)->emitSignal();
    }

    finishGenerateZD();
}

void managerRLS::runRLS(int idX, int idY, int H)
{
    int sizeLoading = 0;
    for (int i=0; i<listRLS.size(); i++)
        sizeLoading += listRLS.at(i)->getCountHorVectors();

    startGenerateZD(sizeLoading);
    curVecReady = 0;

    for (int i=0; i<listRLS.size(); i++)
    {
        if (i == idCurRLS)
        {
            listRLS.at(i)->setPosition(idX, idY);
            listRLS.at(i)->emitSignal(H);
        }
        else
        {
            listRLS.at(i)->emitSignal();
        }
    }

    // обновляем визуальную информацию на карте
    int idXo, idYo, w, h;
    listRLS.at(idCurRLS)->getRectPosition(idXo, idYo, w, h);
    updateVisInfoMap(idXo, idYo, w, h);
    finishGenerateZD();
}

void managerRLS::runRLS(int H)
{
    int sizeLoading = 0;
    for (int i=0; i<listRLS.size(); i++)
        sizeLoading += listRLS.at(i)->getCountHorVectors();

    startGenerateZD(sizeLoading);
    curVecReady = 0;

    for (int i=0; i<listRLS.size(); i++)
    {
        if (i == idCurRLS)
        {
            listRLS.at(i)->emitSignal(H);
        }
        else
        {
            listRLS.at(i)->emitSignal();
        }
    }

    // обновляем визуальную информацию на карте
    int idX, idY, w, h;
    listRLS.at(idCurRLS)->getRectPosition(idX, idY, w, h);
    updateVisInfoMap(idX, idY, w, h);
    finishGenerateZD();
}

void managerRLS::readyVecRLS()
{
    curVecReady++;
    readyVector(curVecReady);
}

void managerRLS::getDataGraphic()
{
    listRLS.at(idCurRLS)->getDataGraphic();
}

void managerRLS::setOptZDvert(int Rmax, int countVertVectors, int countPointsDV)
{
    listRLS.at(idCurRLS)->setOptZDvert(Rmax, countVertVectors, countPointsDV);
}