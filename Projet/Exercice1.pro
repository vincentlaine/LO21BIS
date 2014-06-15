QT += widgets

QT += xml
QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11

#LIBS += C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A\Lib


SOURCES += \
    main.cpp \
    UVManager.cpp \
    UV.cpp \
    #Inscription.cpp
    UVwindow.cpp \
    mainwindow.cpp \
    CursusManager.cpp \
    CursusWindow.cpp \
    Cursus.cpp

HEADERS += \
    Etudiant.h \
    UV.h \
    #Inscription.h \
    filiere.h \
    semestre.h \
    semestre_etranger.h \
    UVManager.h \
    profile.h \
    exception.h \
    ProfilManager.h \
    UVwindow.h \
    mainwindow.h \
    CursusWindow.h \
    Cursus.h \
    CursusManager.h

RESOURCES +=

FORMS +=
