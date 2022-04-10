TARGET = Calculator

QT += qml quick
SOURCES += main.cpp

RESOURCES += calculator.qrc

OTHER_FILES = calculator.qml \
    content/Display.qml \
    content/NumberPad.qml \
    content/CalculatorButton.qml \
    content/calculator.js \
    content/images/paper-edge-left.png \
    content/images/paper-edge-right.png \
    content/images/paper-grip.png

DESTDIR = build
DESTDIR = build
OBJECTS_DIR = build/.obj
MOC_DIR = build/.moc
RCC_DIR = build/.rcc
UI_DIR = build/.ui

