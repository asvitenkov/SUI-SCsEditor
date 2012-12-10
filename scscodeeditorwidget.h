#ifndef SCSCODEEDITORWIDGET_H
#define SCSCODEEDITORWIDGET_H

#include <QWidget>

#include "scscodeeditor.h"

class SCsCodeEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SCsCodeEditorWidget(QWidget *parent = 0);
    SCsCodeEditor* getCodeEditor(){ return mEditor; }
signals:
    
public slots:

private:
    SCsCodeEditor *mEditor;
    
};

#endif // SCSCODEEDITORWIDGET_H
