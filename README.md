# CLI Chat Messenger
This is CLI Chat Messenger based on POSIX API from Linux OS. Do note that unlike other similar named projects, this project works like a normal messenger e.g just as Facebook messenger would work. Except that it uses Command Line Interface (CLI) instead of a Graphical User Interface(GUI).

### Major Programming Concepts Used
-	Sockets
-	Multi-Threading
-	Object Oriented Programming
-	Queue Data Structure

### Compilation
If using the g++ compiler you can do:<br>
```
g++ server.cpp -lpthread -o server
g++ client.cpp -lpthread -o client
```

### Usage
- Start the server on 1 PC/Terminal.<br>
```
./server
```

- Find IP of the server's PC using <b>ipconfig/ifconfig</b>. Let's call it <i>"serverIP"</i>.<br>

- Use IP of the server to start client in another PC/Terminal.
```
./client serverIP
```
Using the above method, you can start as many clients as you want on different PCs OR even on same PC but different Terminals.

# How does it work?
<p align="center">
<img src="/readme_images/Users.png" alt="alt text" width="50%" height="auto" style="text-align:center"></img>
</p>

***

<p align="center">
<img src="/readme_images/Server.png" alt="alt text" width="60%" height="auto"></img>
</p>

***

<p align="center">
<img src="/readme_images/Server2a.png" alt="alt text" width="85%" height="auto"></img>
</p>

***
