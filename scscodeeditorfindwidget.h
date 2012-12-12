#ifndef SCSCODEEDITORFINDWIDGET_H
#define SCSCODEEDITORFINDWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QTextDocument>
#include <QToolButton>

class SCsCodeEditor;

class SCsCodeEditorFindWidget : public QWidget
{
    Q_OBJECT
public:
    SCsCodeEditorFindWidget(SCsCodeEditor *editor=0);
    void setFocus();

    QTextDocument::FindFlags getFlags();

    void find();

public slots:
    void findNext();
    void findPrevious();

protected:
    void keyPressEvent(QKeyEvent *e);

private:
    QToolButton* setupToolButton(const QString& text, const QString& icon);

    SCsCodeEditor* mEditor;
    QLineEdit *mSearchEdit;
    QCheckBox *mIsCaseSensitive;
    QCheckBox *mIsFindWholeWord;

    QToolButton *mFindNextButton;
    QToolButton *mFindPreviousButton;
    QToolButton *mCloseButton;
};

#endif // SCSCODEEDITORFINDWIDGET_H
