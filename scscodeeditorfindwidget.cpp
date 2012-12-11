#include <QLineEdit>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QTextDocument>

#include <QDebug>

#include "scscodeeditorfindwidget.h"
#include "scscodeeditor.h"


SCsCodeEditorFindWidget::SCsCodeEditorFindWidget(SCsCodeEditor *editor) :
    QWidget(editor)
{
    mEditor = editor;

    mSearchEdit = new QLineEdit();
    mIsCaseSensitive = new QCheckBox("Case sensitive");
    mIsFindBackward = new QCheckBox("Find Backward");
    mIsFindWholeWord = new QCheckBox("Whole word");

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(mSearchEdit);
    layout->addWidget(mIsCaseSensitive);
    layout->addWidget(mIsFindWholeWord);
    layout->addWidget(mIsFindBackward);

    layout->setMargin(0);
    layout->setSpacing(0);

    setLayout(layout);
}

void SCsCodeEditorFindWidget::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Return)
    {
        find();

    }
    else if (e->key() == Qt::Key_Escape)
    {
        hide();
    }
}

void SCsCodeEditorFindWidget::find()
{
    QTextDocument::FindFlags searchFlags;
    if (mIsCaseSensitive->isChecked())
    {
        searchFlags |= QTextDocument::FindCaseSensitively;
    }
    if (mIsFindBackward->isChecked())
    {
        searchFlags |= QTextDocument::FindBackward;
    }
    if (mIsFindWholeWord->isChecked())
    {
        searchFlags |= QTextDocument::FindWholeWords;
    }

    mEditor->find(mSearchEdit->text(), searchFlags);
}
