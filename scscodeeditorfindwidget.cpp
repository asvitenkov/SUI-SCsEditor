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

    mSearchEdit = new QLineEdit(this);
    mSearchEdit->setMinimumWidth(80);
    QFont font("Arial", 11);
    font.setStyleHint(QFont::Serif);
    this->setFont(font);
    mIsCaseSensitive = new QCheckBox(tr("Case sensitive"),this);
    mIsFindWholeWord = new QCheckBox(tr("Whole word"),this);
    mIsFindBackward = new QCheckBox(tr("Find Backward"),this);


    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(mSearchEdit);
    layout->addWidget(mIsCaseSensitive);
    layout->addWidget(mIsFindWholeWord);
    layout->addWidget(mIsFindBackward);

    layout->setContentsMargins(QMargins(0,5,20,0));

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


void SCsCodeEditorFindWidget::setFocus()
{
    QWidget::setFocus();
    mSearchEdit->setFocus();
    mSearchEdit->selectAll();
}
