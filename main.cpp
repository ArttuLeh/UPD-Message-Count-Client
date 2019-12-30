/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Arttu Lehtovaara
 *
 * Created on May 17, 2019, 11:57 AM
 */

#include <iostream>

#include <string.h> // memset, strlen
#include <stdio.h> // sprintf

// headers for socket (UDP) communication
#include <unistd.h> // standard unix calls
#include <sys/types.h> // standard types for system calls
// for socket connections
#include <sys/socket.h> // basic socket calls
#include <netinet/in.h> // sockaddr_in
#include <arpa/inet.h> // inet_ntoa

#include <signal.h> // sigaction, SIGINT

using namespace std;

/*
* 
 */
int main(int argc, char** argv) 
{
    // variables
    int s; // socket
    bool end; // for main loop ending
    
    char bf[100], rbf[120]; // max 100 bytes c-string for receive buffer
    socklen_t l = sizeof(sockaddr_in); // the length of the sockaddr structure
    int n; // count of the received characters
    
   // create a socket object
    s = socket(AF_INET, SOCK_DGRAM, 0); // ipv4-socket, UDP
    
    // define listening port for socket ()
    sockaddr_in server, client; // structure for socket address
    server.sin_port = htons("your own port number"); // own unic port number
    server.sin_family = AF_INET; // ipv4 address
    server.sin_addr.s_addr = inet_addr("localhost"); // connection from anywhere
    bind(s, (sockaddr*)&server, sizeof(server));
    
    // main loop for listening message
    cout << "Message counting client for testing the service\n";
    
    while (!end)
    {
        cout << "Give a message: ";
        cin.getline(rbf, sizeof(rbf));
        //if (bf[0] != 0)
        //{
            // send the message to the server
            sendto(s, rbf, strlen(rbf), 0, (sockaddr*)&server, l);
            
            // call is blocking until we get the answer
            n = recvfrom(s, bf, sizeof(bf)-1, 0, (sockaddr*)&server, &l);
            
            // if we got an answer
            if (n >= 0)
            {
                bf[n] = 0;
                cout << "Number of characters in the message is: " << bf << endl;
            }
            if (rbf[0] == 0)
            {
                end = true;
            }
        //}
        //else
            //end = true; // end the main loop and whole program
    }
    
    cout << "Client program is stopped...\n";
    
    close(s); // close the socket here in the end of the program
    
    return 0;
}

