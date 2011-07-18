#include "zuipedit.h"
#include "ui_zuipedit.h"
#include "zuipscene.h"
#include "presentationmodel.h"

#include <QtGui/QFileDialog>
#include <QtSvg/QGraphicsSvgItem>
#include <QtSvg/QSvgRenderer>
#include <QtCore/QDebug>

ZuipEdit::ZuipEdit(QWidget *parent)
  : QMainWindow(parent),
    ui(new Ui::ZuipEdit)
{
  ui->setupUi(this);
  m_scene = new ZuipScene();
  ui->graphicsView->setScene(m_scene);
  connect(ui->actionImportFromFile,SIGNAL(triggered(bool)),this,SLOT(importFile()));
}

ZuipEdit::~ZuipEdit()
{
  delete ui;
  delete m_scene;
}

void ZuipEdit::importFile()
{
  QString fileName = QFileDialog().getOpenFileName(this, tr("Open File"), QString(), tr("SVG-Images (*.svg)"));
  importFile(fileName);
}

void ZuipEdit::importFile(const QString& fileName)
{
  m_scene->setPresentation(new PresentationModel(fileName));
  ui->titleEdit->setText(m_scene->title());
}

#include "zuipedit.moc"
