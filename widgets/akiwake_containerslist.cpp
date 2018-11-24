#include "akiwake_containerslist.h"

AkiwakeContainersList::AkiwakeContainersList(QWidget *parent)
    : QTreeWidget(parent) {
  // Creates a special tree widget for displaying containers.
  this->setHeaderLabel("Containers");
  int ID =
      QFontDatabase::addApplicationFont(":/arts/fonts/iosevka-regular.ttf");
  QFont Font = QFontDatabase::applicationFontFamilies(ID).at(0);
  this->setFont(Font);
}
