#include <QtGui/QApplication>
#include "zuipedit.h"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);
  ZuipEdit foo;
  foo.show();
  return app.exec();
}
