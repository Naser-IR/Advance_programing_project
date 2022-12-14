//
// Created by Naser Ihab on 20/12/2021.
//

#ifndef UNTITLED4_SERVER_H
#define UNTITLED4_SERVER_H

#include <iostream>
#include <sys/socket.h>  // The header file socket.h includes a number of definitions of structures needed for sockets.
#include <netinet/in.h>  // The header file in.h contains constants and structures needed for internet domain addresses.

#include <pthread.h>
#include <thread>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<signal.h>
#include <sstream>

#include "CLI.h"

#include "CLI.h"

using namespace std;

// edit your ClientHandler interface here:
class ClientHandler{
public:
    virtual void handle(int clientID)=0;
};


// you can add helper classes here and implement on the cpp file
class SocketIO : public DefaultIO {
    int clientID;
public:
    SocketIO(int clientID):clientID(clientID){};
    virtual string read();
    virtual void write(string text);
    virtual void write(float f);
    virtual void read(float* f);
    virtual ~SocketIO(){}
};

// edit your AnomalyDetectionHandler class here
class AnomalyDetectionHandler: public ClientHandler{
public:
    virtual void handle(int clientID){
        SocketIO sio(clientID);
        CLI cli(&sio);
        cli.start();
    }
};


// implement on Server.cpp
class Server {
    int server_fd;
    thread* t; // the thread to run the start() method in
    sockaddr_in s_add;
    sockaddr_in c_add;
    volatile bool stopped;
    // you may add data members

public:
    Server(int port) throw (const char*);
    virtual ~Server();
    void start(ClientHandler& ch)throw(const char*);
    void stop();
};
#endif //UNTITLED4_SERVER_H
