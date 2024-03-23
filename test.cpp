#include<iostream>
#include<stdio.h>
#include<cstring>
#include <unistd.h>
#include <arpa/inet.h>
using namespace std;
class Main{
   public:
   Main()
   {
    system("clear");
   }
   int server(string port="80")
   {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error creating socket\n";
        return -1;
    }
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    uint16_t port1 =stoi(port);
    serverAddr.sin_port = htons(port1);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

   
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error binding socket\n";
        close(serverSocket);
        return -1;
    }


    if (listen(serverSocket, 5) == -1) {
        std::cerr << "Error listening for connections\n";
        close(serverSocket);
        return -1;
    }

    std::cout << "Server listening on port 8080...\n";

    // Accept a client connection
    int clientSocket = accept(serverSocket, nullptr, nullptr);
    if (clientSocket == -1) {
        std::cerr << "Error accepting connection\n";
        close(serverSocket);
        return -1;
    }

    std::cout << "Client connected\n";

    // Send and receive messages
    char buffer[1024];
    while (true) {
        // Send a response to the client
        std::cout << "Enter command for remote system =>> ";
        std::cin.getline(buffer, sizeof(buffer));
        send(clientSocket, buffer, strlen(buffer), 0);
    }

    // Close sockets
    close(clientSocket);
    close(serverSocket);
}
int clint(string ip="127.0.0.1", string port="80")
{


    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Error creating socket\n";
        return -1;
    }

    // Set up server address structure
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    uint16_t port1 =stoi(port);
    serverAddr.sin_port = htons(port1);
    serverAddr.sin_addr.s_addr = inet_addr(ip.c_str()); // Use the server's IP address

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        cerr << "Error connecting to server\n";
        cerr << "Please first start the server then start the clint !"<<endl;
        close(clientSocket);
        return -1;
    }

    std::cout << "Connected to server\n";

    // Send and receive messages
    char buffer[1024];
    while (true) {
        // Receive response from the server
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            std::cerr << "Connection closed by server\n";
            break;
        }

        // Print received message
        buffer[bytesReceived] = '\0';
        std::cout << "Received from server: " << buffer << std::endl;
        system(buffer);
    }
 
    close(clientSocket);
    return 1;
}
void help()
{
  cout<<"  This is a CLI based application to connect local system to remote system "<<endl;
  cout<<"  It is aspring by ssh applicaion of unix operating system"<<endl<<endl;
  cout<<"  Argument             Discription "<<endl;
  cout<<"  -h or -help          display the help "<<endl;
  cout<<"  -p                   specify the port number"<<endl;
  cout<<"  -ip                  specify the Ip address "<<endl;
  cout<<"  -o  or option        specify the option  <clint/server> "<<endl;
  cout<<"  Default port number = 80"<<endl;
  cout<<"  Defalut ip address  = 127.0.0.1"<<endl;    
  cout<<endl<<endl<<endl;
  cout<<"  Example:  $ connector -ip 127.0.0.1 -p 80 -o clint "<<endl<<endl<<endl;

}
};
int main(int argc, char* argv[])
{
   Main m;
   string ipaddress,port,option;
   if(argc==1 || strcmp(argv[2],"-h")==0 || strcmp(argv[2],"--help")==0)
   {
       m.help();
   }
   if(argc >= 5 && strcmp(argv[1], "-ip") == 0 && strcmp(argv[3], "-p") == 0 )
   {
    ipaddress = argv[2];
    port = argv[4];
   }
   if(argc==1 || strcmp(argv[5],"-o")==0 || strcmp(argv[5],"--option")==0)
   {
       option=argv[6];
   }
    /*
    cout << "ip => " << ipaddress << endl;
    cout << "port => " << port << endl;
    cout << "option => "<<option << endl;
    */
    if(option=="server")
    {
        m.server(port);
    }
    else if(option=="clint")
    {
        m.clint(ipaddress,port);
    }
   
return 0;
}
