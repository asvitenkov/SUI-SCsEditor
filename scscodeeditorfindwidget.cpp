#include "scscodeeditorfindwidget.h"
#include "scscodeeditor.h"

#include <QLineEdit>
#include <QCheckBox>
#include <QHBoxLayout>

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

    setLayout(layout);
}
