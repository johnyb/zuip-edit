#include "zuipedit.h"
#include "ui_zuipedit.h"

#include <QtGui/QFileDialog>
#include <QtCore/QDebug>

ZuipEdit::ZuipEdit(QWidget *parent)
  : QMainWindow(parent),
    ui(new Ui::ZuipEdit)
{
  ui->setupUi(this);
  connect(ui->actionImportFromFile,SIGNAL(triggered(bool)),this,SLOT(importFile()));
}

void ZuipEdit::importFile()
{
  QString fileName = QFileDialog().getOpenFileName(this, tr("Open File"), QString(), tr("SVG-Images (*.svg)"));
  importFile(fileName);
}

void ZuipEdit::importFile(const QString& fileName)
{

}

ZuipEdit::~ZuipEdit()
{
  delete ui;
}

#include "zuipedit.moc"
