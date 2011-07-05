/*=========================================================================

  Library:   CTK

  Copyright (c) Kitware Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.commontk.org/LICENSE

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=========================================================================*/

#ifndef __ctkPopupWidget_h
#define __ctkPopupWidget_h

// Qt includes
#include <QFrame>

// CTK includes
#include "ctkWidgetsExport.h"

class ctkPopupWidgetPrivate;

/// Description:
class CTK_WIDGETS_EXPORT ctkPopupWidget : public QFrame
{
  Q_OBJECT
  /// Final transparency of the widget (after opacity fading)
  /// QStyle::SH_ToolTipLabel_Opacity by default.
  Q_PROPERTY( int opacity READ opacity WRITE setOpacity)
  /// Control wether the popup automatically opens when the mouse
  /// is over the baseWidget and automatically closes when it leaves
  /// the widget.
  Q_PROPERTY( bool autoHide READ autoHide WRITE setAutoHide)

public:
  typedef QFrame Superclass;
  explicit ctkPopupWidget(QWidget* parent = 0);
  virtual ~ctkPopupWidget();

  /// Widget the popup is attached to. It opens right under \a baseWidget
  /// and if the ctkPopupWidget sizepolicy contains the growFlag/shrinkFlag,
  /// it tries to resize itself to fit the same width of \a baseWidget.
  QWidget* baseWidget()const;
  void setBaseWidget(QWidget* baseWidget);
  
  int opacity()const;
  void setOpacity(int alpha);
  
  bool autoHide()const;
  void setAutoHide(bool);

public slots:
  /// Hide the popup if open or opening. It takes around 300ms 
  /// for the fading effect to hide the popup.
  void hidePopup();
  /// Open the popup if closed or closing. It takes around 300ms 
  /// for the fading effect to open the popup.
  void showPopup();
  /// Show/hide the popup. It can be conveniently linked to a QPushButton
  /// signal.
  inline void showPopup(bool show);

protected slots:
  void updatePopup();
  void animatePopup();

protected:
  QScopedPointer<ctkPopupWidgetPrivate> d_ptr;

  virtual void paintEvent(QPaintEvent*);
  virtual void leaveEvent(QEvent* event);
  virtual void enterEvent(QEvent* event);
  virtual bool eventFilter(QObject* obj, QEvent* event);

private:
  Q_DECLARE_PRIVATE(ctkPopupWidget);
  Q_DISABLE_COPY(ctkPopupWidget);
};

void ctkPopupWidget::showPopup(bool show)
{
  if (show)
    {
    this->showPopup();
    }
  else
    {
    this->hidePopup();
    }
}

#endif
