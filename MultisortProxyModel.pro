QT += core gui sql

TARGET = MultisortProxyModel
TEMPLATE = app

SOURCES += \
    main.cpp \
    MultisortTableView.cpp

HEADERS += \
    AlphanumComparer.h \
    MultisortTableView.h \
    AlphanumSortProxyModel.h
