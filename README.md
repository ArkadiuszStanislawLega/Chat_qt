# Chat app in Qt
App chat with anonymous user. Is not required e-mail address or phone number. 
Messages are removed from server after 30 days.
If user doesn't use his account, after 30 all data will be deleted and user lost his account. 
User can set up his account absence, then his account will be deleted after absence date and 30 days.
User see all properties and stats in messages. He can set up his chat view to see when message was sent, 
passed to server and readed with all times. It is possible to set up how many numbers of letters is in 
current message.

## TO DO:
### offline
+ fully working offline app with sqlite database
>+ login in using database
>+ get user settings
>+ get contacts
>+ get conversation

### online
+ make client app        
>+ adding user
>+ login in
>+ remove accout
>+ show all contacts
>+ make conversation
>+ connection to server via TCP
+ make server app
>+ same as client app but everything via server using sqlite database

+ add cryptography
+ add files to chat
+ add creating groups

---
