TARGET = SystemDialogs

QT += qml quick widgets

SOURCES += main.cpp

OTHER_FILES += \
    systemdialogs.qml \
    FileDialogs.qml 

RESOURCES += systemdialogs.qrc

DESTDIR = build
DESTDIR = build
OBJECTS_DIR = build/.obj
MOC_DIR = build/.moc
RCC_DIR = build/.rcc
UI_DIR = build/.ui


