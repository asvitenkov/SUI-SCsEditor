/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010 OSTIS

OSTIS is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OSTIS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OSTIS.  If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------------------------------
*/

#include "scswindow.h"
#include "scshighlightingrulespool.h"
#include "scscodeeditor.h"
#include "scssyntaxhighlighter.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QUndoStack>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QTextStream>

SCsWindow::SCsWindow(const QString& _windowTitle, QWidget *parent):
    QWidget(parent),
    mEditor(0),
    mEditorWidget(0),
    mHighlighter(0),
    mIsSaved(false)
{
    mEditorWidget = new SCsCodeEditorWidget();
    mEditor = mEditorWidget->getCodeEditor();
    QFont font("Arial", 11);
    font.setStyleHint(QFont::Serif);
    mEditor->setFont(font);
    mEditor->setPalette(QPalette(QPalette::Background, Qt::white));
    mEditor->setTabStopWidth(20);

    mHighlighter = new SCsSyntaxHighlighter(mEditor->document(), SCsHighlightingRulesPool::getInstance()->rules());
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(mEditorWidget);
    setLayout(layout);

    connect(mEditor, SIGNAL(textChanged()), this, SLOT(textChanged()));
}

SCsWindow::~SCsWindow()
{
    delete mHighlighter;
    delete mEditor;
}

bool SCsWindow::loadFromFile(const QString &fileName)
{
    // read data from file
    QFile fileIn(fileName);

    if (!fileIn.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(0, tr("Error"),
                             tr("Can't open file %1:\n%2.")
                             .arg(fileName)
                             .arg(fileIn.errorString()));
        return false;
    }

    QTextStream in(&fileIn);
    mEditor->document()->setPlainText(in.readAll());
    mEditor->setDocumentPath(fileName);
    fileIn.close();

    mFileName = fileName;
    setWindowTitle(mFileName + "[*]");
    mIsSaved = true;

    return true;
}

bool SCsWindow::saveToFile(const QString &fileName)
{
    QFile fileOut(fileName);
    if (!fileOut.open(QFile::WriteOnly | QFile::Text))
    {
         QMessageBox::warning(0, tr("error"),
                              tr("Can't save file %1:\n%2.")
                              .arg(fileName)
                              .arg(fileOut.errorString()));
         return false;
    }
    QTextStream out(&fileOut);
    out << mEditor->document()->toPlainText();
    fileOut.close();

    mFileName = fileName;
    setWindowTitle(mFileName + "[*]");
    mIsSaved = true;


    return true;
}

void SCsWindow::_update()
{

}

void SCsWindow::textChanged()
{
    mIsSaved = false;
}

