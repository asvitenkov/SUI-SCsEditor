#ifndef SCSCODEEDITORWIDGET_H
#define SCSCODEEDITORWIDGET_H

#include <QWidget>

class SCsCodeEditor;
class SCsCodeEditorFindWidget;

class SCsCodeEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SCsCodeEditorWidget(QWidget *parent = 0);
	~SCsCodeEditorWidget();
    SCsCodeEditor* getCodeEditor(){ return mEditor; }
signals:
    
public slots:

private slots:

private:
    SCsCodeEditor *mEditor;
    SCsCodeEditorFindWidget *mEditorFindWidget;
};

#endif // SCSCODEEDITORWIDGET_H
