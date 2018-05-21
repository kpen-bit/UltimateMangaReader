#-------------------------------------------------
#
# Project created by QtCreator 2018-05-11T21:24:34
#
#-------------------------------------------------

#CONFIG += windows
#CONFIG += kobo

windows {
    DEFINES += DESKTOP WINDOWS

    LIBS += -L"D:/dev/lib/win32/OpenSSL/lib" -l"libeay32"
    LIBS += -L"D:/dev/lib/win32/OpenSSL/lib" -l"ssleay32"

    INCLUDEPATH += D:/dev/lib/win32/OpenSSL/include

    DEFINES += Q_COMPILER_INITIALIZER_LISTS
}
kobo {
    DEFINES += KOBO

    include(../free/common/common.pri)


    LIBS  += -L../build-free-Kobo-Release/common -lcommon
}

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UltimateMangaReader
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



INCLUDEPATH += $$PWD/widgets $$PWD/mangasources
DEPENDPATH  += $$PWD/widgets $$PWD/mangasources



RESOURCES += \
    images.qrc

FORMS += \
    widgets/favoriteswidget.ui \
    widgets/mainwidget.ui \
    widgets/homewidget.ui \
    widgets/mangainfowidget.ui \
    widgets/mangareaderwidget.ui

HEADERS += \
    mangasources/abstractmangasource.h \
    mangasources/mangapanda.h \
    widgets/favoriteswidget.h \
    widgets/mainwidget.h \
    widgets/mangaimagecontainer.h \
    configs.h \
    downloadfilejob.h \
    downloadimageandrescalejob.h \
    downloadmanager.h \
    downloadstringjob.h \
    mangachapter.h \
    mangaindex.h \
    mangainfo.h \
    preloadqueue.h \
    readingstate.h \
    ReadingStateManager.h \
    widgets/homewidget.h \
    widgets/mangainfowidget.h \
    widgets/mangareaderwidget.h \
    widgets/cscrollbar.h \
    mangasources/mangadex.h \
    mangasources/mangatown.h

SOURCES += \
    mangasources/abstractmangasource.cpp \
    mangasources/mangapanda.cpp \
    widgets/favoriteswidget.cpp \
    widgets/mainwidget.cpp \
    widgets/mangaimagecontainer.cpp \
    configs.cpp \
    downloadfilejob.cpp \
    downloadimageandrescalejob.cpp \
    downloadmanager.cpp \
    downloadstringjob.cpp \
    main.cpp \
    mangachapter.cpp \
    mangaindex.cpp \
    mangainfo.cpp \
    preloadqueue.cpp \
    readingstate.cpp \
    ReadingStateManager.cpp \
    widgets/homewidget.cpp \
    widgets/mangainfowidget.cpp \
    widgets/mangareaderwidget.cpp \
    widgets/cscrollbar.cpp \
    mangasources/mangadex.cpp \
    mangasources/mangatown.cpp


