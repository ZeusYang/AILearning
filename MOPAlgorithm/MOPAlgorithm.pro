QT += widgets
QT += datavisualization

HEADERS += \
    Algorithm/MOP_Algorithm.h \
    Algorithm/NSGA_II_Algorithm.h \
    Display.h \
    Setting.h \
    Algorithm/MOEA_D_Algorithm.h

SOURCES += \
    main.cpp \
    Algorithm/MOP_Algorithm.cpp \
    Algorithm/NSGA_II_Algorithm.cpp \
    Display.cpp \
    Setting.cpp \
    Algorithm/MOEA_D_Algorithm.cpp

FORMS += \
    Display.ui \
    Setting.ui

