#include <QGridLayout>
#include <QShortcut>


#include "scscodeeditorwidget.h"
#include "scsparserwrapper.h"

SCsCodeEditorWidget::SCsCodeEditorWidget(QWidget *parent) :
    QWidget(parent),
    mEditor(0)
{
//    mLineErrorArea = new SCsLineErrorArea();

    mEditor = new SCsCodeEditor();
    QFont font("Arial",11);
    font.setStyleHint(QFont::Serif);
    mEditor->setFont(font);
    mEditor->setPalette(QPalette(QPalette::Background, Qt::white));
    mEditor->setTabStopWidth(20);

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(mEditor,0,1,1,1);
//    layout->addWidget(mLineErrorArea,0,0,1,1);
    layout->setMargin(0);
    layout->setSpacing(0);
    setLayout(layout);

    QShortcut *shortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_R),this);
    connect(shortcut,SIGNAL(activated()),this,SLOT(onCheckGrammarShortcut()));
}



void SCsCodeEditorWidget::onCheckGrammarShortcut()
{
    SCsParserWrapper psr(mEditor->document()->toPlainText());
    QVector<int> errorLines;
    if( !psr.parseData() )
    {
        // free memory after
        QList<SCsParserError*> errorList = psr.getErrors();


        QList<SCsParserError*>::Iterator it;
        for( it=errorList.begin(); it!=errorList.end(); ++it)
        {
            errorLines.push_back((*it)->line());
            delete *it;
        }
        errorList.clear();
    }
    mEditor->setErrorsLines(errorLines);
    mEditor->update();
}
