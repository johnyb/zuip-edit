#ifndef ZUIPEDIT_H
#define ZUIPEDIT_H

#include <QtGui/QMainWindow>

class PresentationModel;
class QGraphicsScene;

namespace Ui {
  class ZuipEdit;
}

class ZuipEdit : public QMainWindow
{
  Q_OBJECT

public:
  explicit ZuipEdit(QWidget *parent = 0);
  ~ZuipEdit();

public slots:
  void importFile();

protected:
  void importFile(const QString& fileName);

private:
  Ui::ZuipEdit *ui;
  QGraphicsScene *m_scene;
  PresentationModel *m_presentation;
};

#endif // ZUIPEDIT_H
