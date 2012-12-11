#include <QtGui/QApplication>
#include <QTextCodec>

#include "scswindow.h"
#include "scscodeeditorfindwidget.h"


#include "scsparser/scsparserwrapper.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));


    QApplication a(argc, argv);
    SCsWindow edit("SCs Editor");
    edit.show();
    return a.exec();
}
