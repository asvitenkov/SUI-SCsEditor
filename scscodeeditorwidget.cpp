#include "scscodeeditorwidget.h"

#include <QGridLayout>


SCsCodeEditorWidget::SCsCodeEditorWidget(QWidget *parent) :
    QWidget(parent),
    mEditor(0)
{
    mEditor = new SCsCodeEditor();
    QFont font("Arial",11);
    font.setStyleHint(QFont::Serif);
    mEditor->setFont(font);
    mEditor->setPalette(QPalette(QPalette::Background, Qt::white));
    mEditor->setTabStopWidth(20);

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(mEditor,0,1,1,1);
    layout->setMargin(0);
    layout->setSpacing(0);
    setLayout(layout);
}
