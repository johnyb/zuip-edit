#ifndef ZUIPEDIT_H
#define ZUIPEDIT_H

#include <QtGui/QMainWindow>

class ZuipScene;

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
  ZuipScene *m_scene;
};

#endif // ZUIPEDIT_H
