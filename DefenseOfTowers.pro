QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Boosters.cpp \
    Tower.cpp \
    TowerBullet.cpp \
    Wall.cpp \
    castle.cpp \
    cell.cpp \
    closebutton.cpp \
    enemy.cpp \
    game.cpp \
    graph.cpp \
    healthbar.cpp \
    lose.cpp \
    main.cpp \
    mainwindow.cpp \
    map_designer.cpp \
    settings.cpp \
    structure.cpp \
    timerwidget.cpp \
    win.cpp \
    worker.cpp

HEADERS += \
    Boosters.h \
    Tower.h \
    TowerBullet.h \
    Wall.h \
    castle.h \
    cell.h \
    closebutton.h \
    enemy.h \
    game.h \
    graph.h \
    healthbar.h \
    lose.h \
    mainwindow.h \
    map_designer.h \
    settings.h \
    structure.h \
    timerwidget.h \
    win.h \
    worker.h

FORMS += \
    lose.ui \
    mainwindow.ui \
    map_designer.ui \
    settings.ui \
    win.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    gameAssets.qrc
