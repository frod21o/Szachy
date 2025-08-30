QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Figures/bishop.cpp \
    Figures/checkerspiece.cpp \
    Figures/checkersqueen.cpp \
    Figures/emptyspace.cpp \
    Figures/figure.cpp \
    Figures/king.cpp \
    Figures/knight.cpp \
    Figures/pawn.cpp \
    Figures/queen.cpp \
    Figures/rook.cpp \
    Figures/specialchecker.cpp \
    Figures/specialqueen.cpp \
    boarddata.cpp \
    boarddisplay.cpp \
    boardhistory.cpp \
    checkersboard.cpp \
    checkersrules.cpp \
    chessboard.cpp \
    clock.cpp \
    main.cpp \
    mainwindow.cpp \
    movesnapshot.cpp \
    sgamemodboard.cpp \
    specialrules.cpp

HEADERS += \
    Figures/bishop.h \
    Figures/checkerspiece.h \
    Figures/checkersqueen.h \
    Figures/emptyspace.h \
    Figures/figure.h \
    Figures/king.h \
    Figures/knight.h \
    Figures/pawn.h \
    Figures/queen.h \
    Figures/rook.h \
    Figures/specialchecker.h \
    Figures/specialqueen.h \
    boarddata.h \
    boarddisplay.h \
    boardhistory.h \
    checkersboard.h \
    checkersrules.h \
    chessboard.h \
    clock.h \
    mainwindow.h \
    movesnapshot.h \
    sgamemodboard.h \
    specialrules.h

FORMS += \
    checkersrules.ui \
    mainwindow.ui \
    specialrules.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
