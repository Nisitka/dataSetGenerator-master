#-------------------------------------------------
#
# Project created by QtCreator 2023-02-16T08:43:28
#
#-------------------------------------------------

QT       += core gui printsupport opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dataSetGenerator-master
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -lOpengl32 -lglu32

SOURCES += main.cpp\
    core.cpp \
    backend/buildertraildrones.cpp \
    backend/drone.cpp \
    backend/geoblock.cpp \
    backend/geogenerator.cpp \
    backend/managerrls.cpp \
    backend/map.cpp \
    backend/painterimage.cpp \
    backend/ray.cpp \
    backend/rls.cpp \
    GUI/designer.cpp \
    GUI/gui.cpp \
    GUI/mainwindow.cpp \
    GUI/map3dwindow.cpp \
    GUI/mapopenglwidget.cpp \
    GUI/optdronewindow.cpp \
    GUI/optmapgeneratorwindow.cpp \
    GUI/optrlswindow.cpp \
    GUI/paintermapimage.cpp \
    GUI/runwindow.cpp \
    GUI/visualinfowidget.cpp \
    GUI/visualmap3d.cpp \
    GUI/drawArea/areadrawwidget.cpp \
    GUI/drawArea/drawareatool.cpp \
    GUI/drawArea/toolsetrls.cpp \
    GUI/drawArea/tooldefault.cpp \
    GUI/drawArea/toolmovemap.cpp \
    GUI/drawArea/toolzoommap.cpp \
    GUI/drawArea/toolpredrect.cpp \
    GUI/drawArea/toolpredtrail.cpp \
    GUI/drawArea/toolvismap.cpp \
    GUI/drawArea/tooleditmap.cpp \
    backend/managerdrones.cpp \
    backend/trail.cpp \
    GUI/plotwidget.cpp \
    GUI/drawArea/drawtask.cpp

HEADERS  += \
    core.h \
    backend/buildertraildrones.h \
    backend/drone.h \
    backend/geoblock.h \
    backend/geogenerator.h \
    backend/managerrls.h \
    backend/map.h \
    backend/painterimage.h \
    backend/ray.h \
    backend/rls.h \
    GUI/designer.h \
    GUI/gui.h \
    GUI/mainwindow.h \
    GUI/map3dwindow.h \
    GUI/mapopenglwidget.h \
    GUI/optdronewindow.h \
    GUI/optmapgeneratorwindow.h \
    GUI/optrlswindow.h \
    GUI/paintermapimage.h \
    GUI/runwindow.h \
    GUI/visualinfowidget.h \
    GUI/visualmap3d.h \
    GUI/drawArea/areadrawwidget.h \
    GUI/drawArea/drawareatool.h \
    GUI/drawArea/toolsetrls.h \
    GUI/drawArea/tooldefault.h \
    GUI/drawArea/toolmovemap.h \
    GUI/drawArea/toolzoommap.h \
    GUI/drawArea/toolpredrect.h \
    GUI/drawArea/toolpredtrail.h \
    GUI/drawArea/toolvismap.h \
    GUI/drawArea/tooleditmap.h \
    backend/managerdrones.h \
    backend/trail.h \
    GUI/plotwidget.h \
    GUI/drawArea/drawtask.h

FORMS    += GUI/UI/mainwindow.ui \
    GUI/UI/map3dwindow.ui \
    GUI/UI/optdronewindow.ui \
    GUI/UI/optmapgeneratorwindow.ui \
    GUI/UI/optqfunwindow.ui \
    GUI/UI/optrlswindow.ui \
    GUI/UI/visualinfowidget.ui

DISTFILES += \
    resurs/earchIcon.png \
    resurs/imgIcon.png \
    resurs/mapIcon.png \
    resurs/netIcon.png \
    resurs/qFunIcon.png \
    resurs/rlsIcon.png \
    neuronModel/commands.txt \
    neuronModel/READ ME.txt \
    neuronModel/buildTrain.py \
    neuronModel/cnn.py \
    neuronModel/model.py \
    neuronModel/t.py \
    neuronModel/testARGV.py \
    neuronModel/usedNet.py \
    resurs/Thumbs.db \
    resurs/copy.png \
    resurs/downVector.png \
    resurs/drone1.png \
    resurs/droneFinish.png \
    resurs/droneStart.png \
    resurs/editEarthTool.png \
    resurs/genFiles.png \
    resurs/hand.png \
    resurs/hand3D.png \
    resurs/handDrone.png \
    resurs/icon3D.png \
    resurs/leftVector.png \
    resurs/machinery.png \
    resurs/new.png \
    resurs/offRLS.png \
    resurs/onRLS.png \
    resurs/plane.png \
    resurs/radarBlue.png \
    resurs/radarGreen.png \
    resurs/rightVector.png \
    resurs/RLS.png \
    resurs/save.png \
    resurs/startWindow.png \
    resurs/toolEarthDown.png \
    resurs/toolEarthMove.png \
    resurs/toolEarthUp.png \
    resurs/trail1.png \
    resurs/trail2.png \
    resurs/upVector.png \
    resurs/zoom.png \
    resurs/zoom2.png \
    resurs/zoomTool.png

RESOURCES += \
    res.qrc
