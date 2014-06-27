TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lbz2 \
        -lz
SOURCES += \
    bcat.c

