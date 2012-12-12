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

    mFindPreviousButton = setupToolButton(tr("Previous"), ":/media/icons/find-previous.png");
    connect(mFindPreviousButton, SIGNAL(clicked()), this, SLOT(findPrevious()));
    mFindNextButton = setupToolButton(tr("Next"), ":/media/icons/find-next.png");
    connect(mFindNextButton, SIGNAL(clicked()), this, SLOT(findNext()));

    mIsCaseSensitive = new QCheckBox(tr("Case sensitive"),this);
    mIsFindWholeWord = new QCheckBox(tr("Whole word"),this);

    mCloseButton = setupToolButton("", ":/media/icons/find-close.png");
    connect(mCloseButton, SIGNAL(clicked()), this, SLOT(hide()));
    mCloseButton->setFixedHeight(28);
    mCloseButton->setFixedWidth(28);

    QHBoxLayout *layout = new QHBoxLayout();

    layout->addWidget(mCloseButton);
    layout->addWidget(mSearchEdit);
    layout->addWidget(mFindPreviousButton);
    layout->addWidget(mFindNextButton);
    layout->addWidget(mIsCaseSensitive);
    layout->addWidget(mIsFindWholeWord);

    layout->setContentsMargins(QMargins(0,5,20,0));

    setLayout(layout);
}

void SCsCodeEditorFindWidget::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Return)
    {
        findNext();
    }
    else if (e->key() == Qt::Key_Escape)
    {
        hide();
    }
}

QTextDocument::FindFlags SCsCodeEditorFindWidget::getFlags(){
    QTextDocument::FindFlags searchFlags;

    if (mIsCaseSensitive->isChecked())
    {
        searchFlags |= QTextDocument::FindCaseSensitively;
    }
    if (mIsFindWholeWord->isChecked())
    {
        searchFlags |= QTextDocument::FindWholeWords;
    }

    return searchFlags;
}

void SCsCodeEditorFindWidget::findNext()
{
    mEditor->find(mSearchEdit->text(), getFlags());
}

void SCsCodeEditorFindWidget::findPrevious()
{
    mEditor->find(mSearchEdit->text(), getFlags()|QTextDocument::FindBackward);
}

void SCsCodeEditorFindWidget::setFocus()
{
    QWidget::setFocus();
    mSearchEdit->setFocus();
    mSearchEdit->selectAll();
}

QToolButton* SCsCodeEditorFindWidget::setupToolButton(const QString &text, const QString &icon)
{
    QToolButton *toolButton = new QToolButton(this);

    toolButton->setText(text);
    toolButton->setAutoRaise(true);
    toolButton->setIcon(QIcon(icon));
    toolButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    return toolButton;
}
