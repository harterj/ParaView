/*=========================================================================

   Program:   ParaQ
   Module:    pqObjectInspectorWidget.h

   Copyright (c) 2005,2006 Sandia Corporation, Kitware Inc.
   All rights reserved.

   ParaQ is a free software; you can redistribute it and/or modify it
   under the terms of the ParaQ license version 1.1. 

   See License_v1.1.txt for the full ParaQ license.
   A copy of this license can be obtained by contacting
   Kitware Inc.
   28 Corporate Drive
   Clifton Park, NY 12065
   USA

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/

/// \file pqObjectInspectorWidget.h
/// \brief
///   The pqObjectInspectorWidget class is used to display the properties
///   of an object in an editable form.
///
/// \date 11/25/2005

#ifndef _pqObjectInspectorWidget_h
#define _pqObjectInspectorWidget_h

#include "pqWidgetsExport.h"
#include <QWidget>
#include <QMap>
#include "pqSMProxy.h"

class pqObjectPanel;
class QTabWidget;
class QPushButton;
class vtkSMProxy;
class pqObjectPanel;
class pqAutoGeneratedObjectPanel;


/// \class pqObjectInspectorWidget
/// \brief
///   The pqObjectInspectorWidget class is used to display the properties
///   of an object in an editable form.
class PQWIDGETS_EXPORT pqObjectInspectorWidget : public QWidget
{
  Q_OBJECT
public:
  pqObjectInspectorWidget(QWidget *parent=0);
  virtual ~pqObjectInspectorWidget();

  /// hint for sizing this widget
  virtual QSize sizeHint() const;

public slots:
  void setProxy(vtkSMProxy *proxy);

  /// accept the changes made to the properties
  /// changes will be propogated down to the server manager
  void accept();

  /// reset the changes made
  /// editor will query properties from the server manager
  void reset();

  /// This slot is a temporary slot to force  ObjectInspectorPanel
  /// to become modified i.e. enable Accept/Reset buttons.
  void forceModified();

signals:
  /// emitted before accept.
  void preaccept();
  /// emitted on accept() after preaccept() but before postaccept()/
  void accepted();
  ///emitted after accept;
  void postaccept();

  /// emitted before reject.
  void prereject();
  /// emitted after reject.
  void postreject();

protected slots:

  void removeProxy(vtkSMProxy* proxy);

  
private:
  // When in forceModified(), reset, should not disable accept button,
  // hence, we keep this flag. This behaviour may need rethinking, but currently,
  // since forceModified is only called on source creation with pending,
  // display proxy, it makes sense. This flag gets cleared on accept().
  bool ForceModified;
  QTabWidget* TabWidget;
  QPushButton* AcceptButton;
  QPushButton* ResetButton;
  
  pqAutoGeneratedObjectPanel* CurrentAutoPanel;
  pqObjectPanel* CurrentCustomPanel;
  
  QMap<pqSMProxy, pqObjectPanel*> QueuedCustomPanels;
  QMap<pqSMProxy, pqAutoGeneratedObjectPanel*> QueuedAutoPanels;
};

#endif
