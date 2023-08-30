#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QDateTime>

class Message : public QObject
{
  Q_OBJECT
  Q_PROPERTY(int senderId READ getSenderId WRITE setSenderId NOTIFY
                 senderIdChanged FINAL)
  Q_PROPERTY(int receiverId READ getReceiverId WRITE setReceiverId NOTIFY
                 receiverIdChanged FINAL)
  Q_PROPERTY(QString senderUsername READ getSenderUsername WRITE
                 setSenderUsername NOTIFY senderUsernameChanged FINAL)
  Q_PROPERTY(QString receiverUsername READ getReceiverUsername WRITE
                 setReceiverUsername NOTIFY receiverUsernameChanged FINAL)
  Q_PROPERTY(int authorId READ getAuthorId WRITE setAuthorId NOTIFY
                 authorIdChanged FINAL)
  Q_PROPERTY(QString message READ getMessage WRITE setMessage NOTIFY
                 messageChanged FINAL)
  Q_PROPERTY(QDateTime setTimestamp READ getSentTimestamp WRITE setSentTimestamp
                 NOTIFY sentTimestampChanged FINAL)
private:
  int _senderId;
  int _receiverId;
  int _authorId;
  QString _senderUsername;
  QString _receiverUsername;
  QString _message;
  QDateTime _sentTimestamp;

public:
  explicit Message(QObject *parent = nullptr);

  int getSenderId() const;
  void setSenderId(const int &);

  int getReceiverId() const;
  void setReceiverId(const int &);

  int getAuthorId() const;
  void setAuthorId(const int &);

  QString getMessage() const;
  void setMessage(const QString &);

  QString getReceiverUsername() const;
  void setReceiverUsername(const QString &);

  QString getSenderUsername() const;
  void setSenderUsername(const QString &);

  QDateTime getSentTimestamp() const;
  void setSentTimestamp(const QDateTime &);

signals:
  void senderIdChanged();
  void receiverIdChanged();
  void authorIdChanged();
  void receiverUsernameChanged();
  void senderUsernameChanged();
  void sentTimestampChanged();
  void messageChanged();
};

#endif // MESSAGE_H
