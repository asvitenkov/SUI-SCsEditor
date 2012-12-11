

QT       += core gui

TARGET        = SCsEditor

OBJECTS_DIR = obj
MOC_DIR = moc

INCLUDEPATH += scsparser \
    scsparser/include

HEADERS += \
    scssyntaxhighlighter.h \
    scsstdhighlightingrule.h \
    scsmultilinecommenthighlightingrule.h \
    scshighlightingrulespool.h \
    scscodeeditor.h \
    scsabstracthighlightingrule.h \
    scscodeanalyzer.h \
    scscodecompleter.h \
    scswindow.h \
    scsparser/scsparserwrapper.h \
    scsparser/SCsParser.hpp \
    scsparser/SCsLexer.hpp \
    scscodeeditorwidget.h \
    scscodeeditorfindwidget.h
    
SOURCES += \
    scssyntaxhighlighter.cpp \
    scsstdhighlightingrule.cpp \
    scsmultilinecommenthighlightingrule.cpp \
    scshighlightingrulespool.cpp \
    scscodeeditor.cpp \
    scsabstracthighlightingrule.cpp \
    scscodeanalyzer.cpp \
    scscodecompleter.cpp \
    main.cpp \
    scswindow.cpp \
    scsparser/scsparserwrapper.cpp \
    scsparser/SCsParser.cpp \
    scsparser/SCsLexer.cpp \
    scscodeeditorwidget.cpp \
    scscodeeditorfindwidget.cpp

RESOURCES += \
    media/scseditor.qrc

