#include "scscodeeditorwidget.h"
#include "scscodeeditor.h"
#include "scscodeeditorfindwidget.h"
#include "scsparserwrapper.h"

#include <QGridLayout>
#include <QShortcut>



SCsCodeEditorWidget::SCsCodeEditorWidget(QWidget *parent) :
    QWidget(parent)
    ,mEditor(0)
	,mEditorFindWidget(0)
{

    mEditor = new SCsCodeEditor();
    QFont font("Arial",11);
    font.setStyleHint(QFont::Serif);
    mEditor->setFont(font);
    mEditor->setPalette(QPalette(QPalette::Background, Qt::white));
    mEditor->setTabStopWidth(20);

    mEditorFindWidget = mEditor->getFindWidget();

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(mEditor,0,0,1,1);
    layout->addWidget(mEditorFindWidget,1,0,1,1);
    layout->setMargin(0);
    layout->setSpacing(0);

    mEditorFindWidget->hide();

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
        QList<SCsParserError*> errorList = psr.getErrors();

        QList<SCsParserError*>::Iterator it;
        for( it=errorList.begin(); it!=errorList.end(); ++it)
        {
            errorLines.push_back((*it)->line());
        }

		qDeleteAll(errorList.begin(),errorList.end());
        errorList.clear();
    }
    mEditor->setErrorsLines(errorLines);
    mEditor->update();
}



SCsCodeEditorWidget::~SCsCodeEditorWidget()
{
	if(mEditorFindWidget)
		delete mEditorFindWidget;
}