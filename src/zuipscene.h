/*
    Copyright (c) 2011 Julian Bäume <baeume@imis.uni-luebeck.de>

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

#ifndef ZUIPSCENE_H
#define ZUIPSCENE_H

#include <QtGui/QGraphicsScene>

class PresentationModel;

/**
 * A scene to render a presentation with zoomable user interface (ZUI)
 *
 * This scene also provides editing features for the presentation.
 */
class ZuipScene : public QGraphicsScene
{
  Q_OBJECT
public:
  ZuipScene(PresentationModel* presentation = 0);
  virtual ~ZuipScene();

  /**
    * Set a presentation model for this scene. It will get all information from the
    * model and visualise it.
    *
    * @param presentation - the model containing a ZUI Presentation
    */
  void setPresentation(PresentationModel* presentation);

  QString title() const;

private:
  PresentationModel *m_model;
  void reload();
};

#endif // ZUIPSCENE_H
