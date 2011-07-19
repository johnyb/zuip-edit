/*
    Copyright (c) 2011 Julian Bäume <julian@svg4all.de>

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.
*/


#include "presentationmodel.h"

#include <QtGui/QGraphicsItem>
#include <QtCore/QFile>
#include <QtCore/QDebug>
#include <QtSvg/QGraphicsSvgItem>
#include <QSvgRenderer>

PresentationModel::PresentationModel(const QString& fileName, QObject* parent)
  : QObject(parent),
    m_renderer(0)
{
  load(fileName);
}

PresentationModel::~PresentationModel()
{
  delete m_renderer;
}

void PresentationModel::load(const QString& fileName)
{
  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly))
    return;
  if (!m_svgDoc.setContent(&file)) {
    qWarning() << "Couldn’t load" << file.fileName();
    file.close();
    return;
  }
  file.close();

  delete m_renderer;
  m_renderer = 0;
  m_renderer = new QSvgRenderer(fileName);
}

QList< QGraphicsItem* > PresentationModel::assets() const
{
  QList<QGraphicsItem*> result;
  QDomElement root = rootSvgElement();
  if (root.isNull())
    return result;

  QDomNodeList list = root.elementsByTagName(QLatin1String("g"));
  for (int i=0; i<list.size(); i++){
    if (list.at(i).isElement() && list.at(i).toElement().attribute(QLatin1String("class")).contains(QLatin1String("content"))){
      result << createGraphicsItem(list.at(i).toElement());
    }
  }
  return result;
}

QRectF PresentationModel::viewBox() const
{
  QDomElement root = rootSvgElement();
  if (root.isNull())
    return QRectF();

  QRectF viewBox;
  QString vBoxString = root.attribute(QLatin1String("viewBox"), QLatin1String("0 0 0 0"));
  QStringList vBoxValues = vBoxString.split(' ');
  viewBox.setLeft(vBoxValues[0].toDouble());
  viewBox.setTop(vBoxValues[1].toDouble());
  viewBox.setWidth(vBoxValues[2].toDouble());
  viewBox.setHeight(vBoxValues[3].toDouble());
  return viewBox;
}

QString PresentationModel::title() const
{
//   somehow namespaces seem to be broken or i’m using them wrong
//   QDomNodeList list = rootSvgElement().elementsByTagNameNS(rootSvgElement().attribute(QLatin1String("xmlns:dc")),QLatin1String("title"));
  QDomNodeList list = rootSvgElement().elementsByTagName(QLatin1String("dc:title"));
  if (list.size() != 1)
    return QString();

  if (list.at(0).isElement())
    return list.at(0).toElement().text();

  return QString();
}

QDomElement PresentationModel::rootSvgElement() const
{
  if (m_svgDoc.isNull())
    return QDomElement();

  QDomNodeList list = m_svgDoc.elementsByTagName(QLatin1String("svg"));
  if (list.size() > 0)
    return list.at(0).toElement();

  return QDomElement();
}

QGraphicsItem* PresentationModel::createGraphicsItem(const QDomElement& element) const
{
  QGraphicsSvgItem* item = new QGraphicsSvgItem();
  item->setSharedRenderer(m_renderer);
  QString id = element.attribute(QLatin1String("id"));
  if (!id.isEmpty())
    item->setElementId(id);

  item->setFlags( QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable );

  QRegExp re(QLatin1String("^translate\\((.+),(.+)\\) scale\\((.+)\\)$"));
  re.indexIn(element.attribute(QLatin1String("transform")));
  // re.capturedTexts should be of the for: (complete string, x, y, scale)
  qreal x = re.cap(1).toDouble();
  qreal y = re.cap(2).toDouble();
  qreal scale = re.cap(3).toDouble();
  //move item center to parsed coordinates
  QPointF pos = QPointF(x,y) - item->boundingRect().center();
  item->setPos(pos);
  item->setScale(scale);

  return item;
}

#include "presentationmodel.moc"