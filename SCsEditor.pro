

QT       += core gui

TARGET        = SCsEditor

OBJECTS_DIR = obj
MOC_DIR = moc

INCLUDEPATH += scsparser \
    scsparser/include \
    highlightingrules

HEADERS += \
    scssyntaxhighlighter.h \
    highlightingrules/scsstdhighlightingrule.h \
    highlightingrules/scsmultilinecommenthighlightingrule.h \
    scshighlightingrulespool.h \
    scscodeeditor.h \
    highlightingrules/scsabstracthighlightingrule.h \
    scscodeanalyzer.h \
    scscodecompleter.h \
    scswindow.h \
    scsparser/scsparserwrapper.h \
    scsparser/SCsParser.hpp \
    scsparser/SCsLexer.hpp \
    scscodeeditorwidget.h \
    scscodeeditorfindwidget.h \
    highlightingrules/scsmultilinecontenthighlightingrule.h
    
SOURCES += \
    scssyntaxhighlighter.cpp \
    highlightingrules/scsstdhighlightingrule.cpp \
    highlightingrules/scsmultilinecommenthighlightingrule.cpp \
    scshighlightingrulespool.cpp \
    scscodeeditor.cpp \
    highlightingrules/scsabstracthighlightingrule.cpp \
    scscodeanalyzer.cpp \
    scscodecompleter.cpp \
    main.cpp \
    scswindow.cpp \
    scsparser/scsparserwrapper.cpp \
    scsparser/SCsParser.cpp \
    scsparser/SCsLexer.cpp \
    scscodeeditorwidget.cpp \
    scscodeeditorfindwidget.cpp \
    highlightingrules/scsmultilinecontenthighlightingrule.cpp

RESOURCES += \
    media/scseditor.qrc

