# Multi-Users-Chat-Messenger
This is C++ based Chat Messenger which uses Client Server Architecture and Socket programming features of POSIX API from Linux OS. Compared to normal Messenger projects, this project allows for multiple users to connect to server and communicate with multiple users privately.

The implementation method for this project heavily relies on <br/>
(1) **Sockets** - Connect one device to another device on network <br/>
(2) **Multi-Threading** - For handling multiple users in parallel <br/>

# Features
## Core Features:
-	Point-to-Point Communication with another user over same network.
-	Secured Connection: User information not broadcasted.
-	Each user is Assigned a Unique ID and one user can access the other user only if he has his Unique ID .
-	Exclusive data handling of each message **=>** Program is made such as to avoid Data Mixing. 
    -	**Example:** In case multiple users send message to the same Receiver.

## Server Features:
As Server is the one who provides features and services to the Client. Besides providing client the ability to send and receive messages, here are some other special services:
-	Add another user to your list
-	Remove another user from your list.
-	List all the users you have added in your list. 
-	Set Active Connection – which is the connection you want to send messages to.
-	Display My Unique ID any time you want. In case you want to send it to some one for “adding you” in his list.
-	Change your Name .
-	Help - List the usage of all the commands available.
-	Exit – You can exit the program normally.

# Working Principle
**NOTE: In this Project , messages having “./” at start is used for Server Commands**

1. There are 2 Programs:
   - Server Program 
   - Client Program
2. Start the Server program in background:
   -	./server
3.	Start the Client program in any PC on same wifi network, you have to pass the IP
    -	./client 192.168.1.7
    -	Client(user-1) will be asked to enter USERNAME
    -	Client(user-2) will be assigned a Unique ID by server.
4.	User-2: 
    -	Starts the client program the same way as step-3.
    -	User-2 gets a Uniqued ID by server.
    -	He sends his ID to his friend(user-1) manually by any means, suppose he sends the ID in a “SMS message”.
5.	User-1:  
    -	Types “./add User-2-Unique-ID”
        -	This will add User 2 in your list
        -	This will also add you automatically in User 2’s List
    -	Types “./list”, it will show list of users available +  simple numerical IDs assigned to them
        -	Like, 1 – Talha, 2 – Rafeeq, 3 – Hashim…….etc
    -	Types “./active 3” 
        -	This will set user 3 named “Hashim” as an active.
        -	Now, anything you write besides “Server Commands( ./ at start)” will send messages to the active connection which is “Hashim” in this case. 

## EXTRA COMMANDS:
1.	“./myID”  shows you your Unique-ID.
2.	“./remove ID-From-List” will remove a connection from your list.
3.	“./name New-Name” will change your current name to “New-Name”
4.	“./help” shows you list of available Server Commands and how to use them. 
5.	“./exit” will stop your Client Program Completely.
