# CLI Chat Messenger
This is CLI Chat Messenger based on POSIX API from Linux OS. Do note that unlike other similar named projects, this project works like a normal messenger e.g just as Facebook messenger would work. Except that it uses Command Line Interface (CLI) instead of a Graphical User Interface(GUI).

# Major Programming Concepts used:
-	Sockets
-	Multi-Threading
-	Object Oriented Programming
-	Queue Data Structure

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
## Server should be started ONCE
The very first step should be starting the server. As server is the one that connects one user to another. How to start server?
- Open 1 terminal
- Type "./server" in the terminal and minimize it
- Find the IP address of this PC using "ifconfig" (if in Linux) or any other suitable command.
  - It will look something like "192.168.1.7"
  - As this IP will be used by Clients to connect to this server

## Open 1 terminal for User-1 and another terminal for User-2
As clear from the heading, we need to open 1 terminal so User-1 can start Chatting with someone and similarly another terminal so User-2 can chat with some one. You can also open more than 2 terminals ( forexample 10 terminals to simulate 10 users) if you want to test for many users.<br/>

Now we are gonna see things from different Viewpoints.
- What should User-1 do? And how does he see things from his Viewpoint.
- Similarly how does User-2 see things?
- Suppose User-1 is named "Talha"
- Suppose User-2 is named "Hamza"

## How will both Users start the messenger in order to Talk?

#### User-1(Talha) Viewpoint
1.	Talha starts the Client program in any PC on same wifi network of the "Server", he has to pass the IP of the PC where we started the Server in above step
    -	./client 192.168.1.7   
2.	Talha(User-1) will be asked to enter his USERNAME
3.  After Talha(User-1) enters his USERNAME
    -	The server will send a Unique ID to the Talha(User-1).
#### User-2(Hamza) Viewpoint
Hamza(User-2) who is on another terminal also performs the same steps (1,2,3) as Talha(User-1)

    1.  Step 1
    2.  Step 2
    3.  Step 3
        - Hamza(User-2) also gets a Unique ID from server

## How do both users connect to each other?
-   Both users have started messenger but they can not send messages to each other because the server doesn't just allow any one to send messages to any one available on the server.

-   Thats exactly what the UNIQUE-ID assigned to each user is for.
    -   The Users need to know UNIQUE-ID of friends in order to add them to his/her friend list and start chatting.

-   Any one of the User(Suppose Talha(User-1)) needs to send his Unique-ID to his other friend Hamza(User-2) manually by any means.
    -   Forexample he sends the ID in a “SMS message”.

#### Talha (User-1):
-   Types “./add Hamza's-Unique-ID”
    -	This will add Hamza(User-2) in Friend list of Talha
    -	This will also add Talha automatically in Hamza's(User-2) Friend List
        
## How do both users talk to each other?
#### Talha(User-1) Viewpoint
-   Types “./list”
-   It will show list of users(your added friends) available **+**  simple numerical IDs assigned to them
-   As User-2 is named "Hamza" so the list will be displayed like:
    -   1 – Hamza
-   Later when you add more friends , the list will display more names like:
    -   1-Hamza , 2–Rafeeq, 3–Hashim
-   **Using the Numbers assigned to the Names, you can Select the Friend you want to talk to and start sending messages**
    -   Forexample, Talha can type “./active 1” in order to send messages to Hamza(USER-2) 
        -	This will set  “Hamza” as an "Active Connection".
        -	Now, anything Talha write will send messages to the active connection which is “Hamza” in this case. 

At this point you already know how to add friend, select friend and send messages to that friend, so basically you can add any other friend and start sending messages.
        
#### Hamza(User-2) Viewpoint
-   As Talha(User-1) has already added Hamza(User-2) to his friend list so Talha is also added automatically in Hamza's Friend List.
-   Hamza will be able to receive messages from Talha as he already set his active connection to "Hamza" and started sending messages in above steps.
-   Hamza can do the same as from above steps and start sending messages to Talha(User-1).

# More about Server Commands
**NOTE: In this Project , messages having “./” at start is used to send COMMANDS to Server**<br/>
We already saw few command like:
-   ./add Hamza's-UNIQUE-ID
-   ./list
-   ./active UaSER-ID-from-list
## EXTRA COMMANDS:
1.	“./myID”  shows you your Unique-ID.
2.	“./remove ID-From-List” will remove a connection from your list (Basically Unfriend him)
3.	“./name New-Name” will change your current name to “New-Name”
4.	“./help” shows you list of available Server Commands and how to use them. 
5.	“./exit” will stop your Client Program Completely (Basically exit the messenger)
