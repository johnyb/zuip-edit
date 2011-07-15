#include "zuipedit.h"
#include "ui_zuipedit.h"

#include <QtGui/QFileDialog>
#include <QtGui/QGraphicsScene>
#include <QtSvg/QGraphicsSvgItem>
#include <QtSvg/QSvgRenderer>
#include <QtCore/QDebug>
#include "presentationmodel.h"

ZuipEdit::ZuipEdit(QWidget *parent)
  : QMainWindow(parent),
    ui(new Ui::ZuipEdit),
    m_presentation(0)
{
  ui->setupUi(this);
  m_scene = new QGraphicsScene();
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
  if (m_presentation) {
    delete m_presentation;
  }
  m_presentation = new PresentationModel(fileName);
}

#include "zuipedit.moc"
