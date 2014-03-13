HEADERS += \
    common.h \
    strategy.h \
    stockparameters.h \
    seriesgen.h \
    randomgenerator.h \
    basestrategy.h \
    extras/cmath/protos.h \
    extras/cmath/mconf.h \
    extras/cprob/mconf.h \
    extras/cprob/stdtr.h \
    strategyfactory.h \
    extras/qcustomplot/qcustomplot.h \
    plotswindow.h \
    financecalculator.h \
    paramwidget.h \
    mainwindow.h

SOURCES += \
    common.cpp \
    strategy.cpp \
    stockparameters.cpp \
    seriesgen.cpp \
    randomgenerator.cpp \
    basestrategy.cpp \
    extras/cmath/unity.c \
    extras/cmath/tanh.c \
    extras/cmath/tandg.c \
    extras/cmath/tan.c \
    extras/cmath/sqrt.c \
    extras/cmath/sinh.c \
    extras/cmath/sindg.c \
    extras/cmath/sincos.c \
    extras/cmath/sin.c \
    extras/cmath/setprec.c \
    extras/cmath/round.c \
    extras/cmath/powi.c \
    extras/cmath/pow.c \
    extras/cmath/polevl.c \
    extras/cmath/mtherr.c \
    extras/cmath/log10.c \
    extras/cmath/log2.c \
    extras/cmath/log.c \
    extras/cmath/isnan.c \
    extras/cmath/floor.c \
    extras/cmath/fabs.c \
    extras/cmath/exp10.c \
    extras/cmath/exp2.c \
    extras/cmath/exp.c \
    extras/cmath/drand.c \
    extras/cmath/cosh.c \
    extras/cmath/cmplx.c \
    extras/cmath/clog.c \
    extras/cmath/chbevl.c \
    extras/cmath/cbrt.c \
    extras/cmath/atanh.c \
    extras/cmath/atan.c \
    extras/cmath/asinh.c \
    extras/cmath/asin.c \
    extras/cmath/acosh.c \
    extras/cprob/stdtr.c \
    extras/cprob/pdtr.c \
    extras/cprob/ndtri.c \
    extras/cprob/ndtr.c \
    extras/cprob/nbdtr.c \
    extras/cprob/kolmogorov.c \
    extras/cprob/incbi.c \
    extras/cprob/incbet.c \
    extras/cprob/igami.c \
    extras/cprob/igam.c \
    extras/cprob/gdtr.c \
    extras/cprob/gamma.c \
    extras/cprob/fdtr.c \
    extras/cprob/expx2.c \
    extras/cprob/const.c \
    extras/cprob/chdtr.c \
    extras/cprob/btdtr.c \
    extras/cprob/bdtr.c \
    strategyfactory.cpp \
    extras/qcustomplot/qcustomplot.cpp \
    main.cpp \
    plotswindow.cpp \
    financecalculator.cpp \
    paramwidget.cpp \
    mainwindow.cpp
CONFIG += c++11 console
TARGET = doge_gui
QT+= widgets printsupport
INCLUDEPATH += extras/cprob \
    extras/qcustomplot

OTHER_FILES += \
    extras/cmath/setprbor.asm \
    extras/cmath/polevl.asm

RESOURCES += \
    doge.qrc
