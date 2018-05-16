SOURCES += \
    main.cpp \
    algorithm.cpp \
    mainwindow.cpp \
    psoparameters.cpp \
    curvedialog.cpp

HEADERS += \
    algorithm.h \
    mainwindow.h \
    psoparameters.h \
    curvedialog.h


QT += widgets
QT += charts

FORMS += \
    mainwindow.ui \
    psoparameters.ui \
    curvedialog.ui

RESOURCES += \
    resource.qrc
RC_ICONS = app.ico
