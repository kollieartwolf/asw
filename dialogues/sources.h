#ifndef SOURCESDIALOG_H
#define SOURCESDIALOG_H

#include "dialogues/modal-handler.h"
#include "dialogues/sources/create-source.h"
#include "widgets/a_button.h"
#include "widgets/a_sourcelist.h"
#include <QDialog>
#include <QFileDialog>
#include <QMenu>
#include <QString>
#include <QTranslator>
#include <QTreeWidgetItem>

/*!
 * @class SourcesDialog
 * @brief Manages NLP module's sources.
 */
class SourcesDialog : public QWidget {
public:
  // Functions described in 'sources.cpp':
  explicit SourcesDialog(Basis *_basis, QWidget *parent = nullptr,
                         ModalHandler *m_handler = nullptr);
  void add();
  void remove();

private:
  Q_DISABLE_COPY(SourcesDialog)

  // Objects:
  Basis *basis = nullptr;
  ModalHandler *_m_handler = nullptr;
  QMap<QTreeWidgetItem *, Source> source_widgets;
  CreateSourceDialog *create_source_dialog = nullptr;
  ASourceList *source_list = nullptr;
  QGridLayout *grid_layout = nullptr;
  AButton *add_source = nullptr;
  QAction *create_source = nullptr;
  QAction *remove_source = nullptr;
  AButton *save_and_close = nullptr;
  QAction *cancel = nullptr;
  bool edited = false;

  // Constants:
  inline static const QString object_name = "sources";

  // Functions described in 'sources.cpp':
  void connector();
  void append(const QList<Source> &sources);
  void appendSingle(const Source &source);
  void sncl();
  void openCS();
  void closeCS();
  void load();
};

#endif // SOURCESDIALOG_H
