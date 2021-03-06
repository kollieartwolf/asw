#ifndef MESSAGE_H
#define MESSAGE_H

#include <QDateTime>
#include <QJsonObject>
#include <QString>

/*!
 * @enum Author
 * @brief Enumeration of possible authors of messages.
 * @sa Message
 */
enum Author { undefA, ASW, User };

/*!
 * @enum ContentType
 * @brief Enumeration of possible content types.
 * @sa Message
 */
enum ContentType {
  undefC,
  Text,
  Markdown,
  Picture,
  File,
  Warning,
  Error,
  Widget
};

/*!
 * @enum Theme
 * @brief Enumeration of possible message themes for ADisplay.
 * @sa Message
 */
enum Theme { undefT, Std, White, Dark, Red, Green, Blue, Yellow };

/*!
 * @struct Message
 * @brief Contains the message and its properties.
 * @sa Author, ContentType, Theme
 */
struct Message {
  /*! Content. */
  QString content = QString();
  /*! Data and time of creation/change. */
  QDateTime datetime;
  /*! Message author. */
  Author author = Author::undefA;
  /*! Type of message content. */
  ContentType content_type = ContentType::undefC;
  /*! Message theme. */
  Theme theme = Theme::Std;

  /*! Compares two messages. They are identical if the authors, content types,
   * content and posting times are the same. */
  friend bool operator==(Message m1, Message m2) {
    return m1.author == m2.author and m1.content_type == m2.content_type and
           m1.content == m2.content and m1.datetime == m2.datetime;
  }

  /*!
   * @fn to_json
   * @brief Turns @a message into a JSON object.
   * @param[in] message message data
   * @returns converted properties of @a message
   */
  friend QJsonObject to_json(const Message &message) {
    return {{"content", message.content},
            {"datetime", message.datetime.toString(Qt::ISODateWithMs)},
            {"author", int(message.author)},
            {"contentType", int(message.content_type)},
            {"theme", int(message.theme)}};
  }
};

/*!
 * @fn to_message
 * @brief Turns @a json_object into a message.
 * @param[in] json_object message in JSON
 * @returns message
 * @sa Message
 */
Message to_message(const QJsonObject &json_object) {
  return {json_object["content"].toString(),
          QDateTime::fromString(json_object["datetime"].toString(),
                                Qt::ISODateWithMs),
          Author(json_object["author"].toInt()),
          ContentType(json_object["contentType"].toInt()),
          Theme(json_object["theme"].toInt())};
}

#endif // MESSAGE_H
