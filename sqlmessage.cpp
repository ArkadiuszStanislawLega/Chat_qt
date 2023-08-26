#include "sqlmessage.h"

/* TODO: Implement this.
 * Insert message query.
 * insert into Messages (contact_id, author_id, message, sended_time) VALUES(1,1,"druga wiadomosc",  "2023-10-12T12:10:00");
 * /

 /* TODO: Implement this.
  * Selected messages for contact query.
select
                sender.id as first_id,
                sender.username as first_username,
                reciver.id as second_id,
                reciver.username as second_username,
                Messages.author_id,
                Messages.message,
                Messages.sended_time
                from Messages
INNER JOIN Contacts ON Contacts.id = Messages.contact_id
INNER JOIN Users as sender ON sender.id = Contacts.first_user
INNER JOIN Users as reciver ON reciver.id = Contacts.second_user
where Messages.author_id = 1
ORDER BY Messages.sended_time DESC	;
 */

SqlMessage::SqlMessage(QObject *parent)
    : QObject{parent}
{

}
