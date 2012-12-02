

QT       += core gui

TARGET        = SCsEditor

OBJECTS_DIR = obj
MOC_DIR = moc


HEADERS += \
    scssyntaxhighlighter.h \
    scsstdhighlightingrule.h \
    scsmultilinecommenthighlightingrule.h \
    scshighlightingrulespool.h \
    scscodeeditor.h \
    scsabstracthighlightingrule.h \
    scscodeanalyzer.h \
    scscodecompleter.h \
    scswindow.h
    
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
    scswindow.cpp

