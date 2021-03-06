#ifndef SQLITE_H
#define SQLITE_H

#include "model/nlp/cache.h"
#include "model/source.h"
#include <QFile>
#include <QJsonObject>
#include <QMap>
#include <QObject>
#include <QPair>
#include <QRandomGenerator>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlResult>
#include <QString>
#include <QStringList>
#include <QTime>
#include <QUuid>
#include <QVariant>

/*!
 * @enum Check
 * @brief Enumeration of possible types of checking the state of database.
 */
enum Check { NoCheck, Exists, Openable, Correct, RecursivelyСorrect };

/*!
 * @enum ToDo
 * @brief Enumeration of possible types of operations with database.
 */
enum ToDo {
  NoneToDo,
  CreateMainTableIfNotExists,
  CreateSourceTable,
  WithDraw,
  LoadOptions,
  WriteOptions,
  SelectSources,
  InsertExpression,
  SelectExpressionByAddress,
  SelectAEL,         /*!< Address, expression and links. */
  SelectELByAddress, /*!< Expression and links. */
  SelectAPByAddress, /*!< Additional properties. */
  IfMainTableExists,
  IfMainTableCorrect,
  IfSourceTableExists,
  IfSourceTableCorrect,
  RemoveMainTableIfExists,
  RemoveSourceTableIfExists
};

/*!
 * @class SQLite
 * @brief Contains methods of working with databases.
 */
class SQLite : public QObject {
  Q_OBJECT
public:
  // Functions:
  /*!
   * @fn SQLite::SQLite
   * @brief The constructor.
   * @details Initializes SQLite database.
   * @param[in,out] parent QObject parent
   */
  SQLite(QObject *parent = nullptr) : QObject(parent) {
    QSqlDatabase::addDatabase("QSQLITE");
  }

  /*!
   * @fn SQLite::purify
   * @brief Purifies @a str.
   * @param[in] str string to be purified
   * @returns purified string
   */
  QString purify(const QString &str) {
    return remove_symbols(str.trimmed().toLower());
  }

  /*!
   * @fn SQLite::remove_symbols
   * @brief Removes punctuation.
   * @param[in] str string that should not contain punctuation
   * @returns string without punctuation
   */
  QString remove_symbols(QString str) {
    for (auto symbol : punctuation_symbols)
      str.remove(symbol);
    return str;
  }

  // Functions described in `sqlite.cpp`:
#ifdef SQLITE_AUTO_TESTS
  virtual
#endif
      bool
      create_source(const Source &source, QString *uuid);
  bool create_base_structure(QSqlQuery *query);
  QList<Source> sources(const QString &path);
  Source load_source(Source source);
  bool write_source(const Source &source);
  bool insert_expression(const Source &source, int address,
                         const QString &expression, const QString &links);
  Expression get_expression_by_address(const Source &source, int address);
  Cache scan_source(const Source &source, const QString &input);

signals:
  /*!
   * @brief Reports an error in the database.
   */
  QString sqlite_error(QString error_text);

  /*!
   * @brief [constructing]
   */
  QString sqlite_warning(QString warning_text);

private:
  // Constants:
  static const int maximum_number_of_attempts =
      4; /*!< Number of attempts for table creation. */
  static const int init_additionals_rows =
      3; /*!< Column from which additional expression properties begin. */
  inline static const QString punctuation_symbols = ".,:;!?-'\"";

  // Functions described in `sqlite.cpp`:
  QSqlDatabase prepare(const QString &path, Check option = Openable,
                       bool *result = nullptr, bool quiet = false);
  bool check(QSqlDatabase *db, Check option = NoCheck);
  bool validate(QSqlDatabase *db, bool recursive = false, bool quiet = false);
  bool validate(QSqlDatabase *db, const QString &source_table,
                bool quiet = false);
  bool exec(QSqlQuery *query, ToDo option, QStringList values = {});
  Options get_additional_properties(QSqlDatabase *db, const Source &source, int address);
  QSet<int> unpack_links(const QString &links);
};

#endif // SQLITE_H
