#ifndef SCSCODEEDITORFINDWIDGET_H
#define SCSCODEEDITORFINDWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>

class SCsCodeEditor;

class SCsCodeEditorFindWidget : public QWidget
{
    Q_OBJECT
public:
    SCsCodeEditorFindWidget(SCsCodeEditor *editor=0);
    void setFocus();
protected:
    void keyPressEvent(QKeyEvent *e);

private:
    void find();

    SCsCodeEditor* mEditor;
    QLineEdit *mSearchEdit;
    QCheckBox *mIsCaseSensitive;
    QCheckBox *mIsFindWholeWord;
    QCheckBox *mIsFindBackward;
};

#endif // SCSCODEEDITORFINDWIDGET_H
