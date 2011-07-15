#ifndef ZUIPEDIT_H
#define ZUIPEDIT_H

#include <QMainWindow>

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
};

#endif // ZUIPEDIT_H
