#ifndef PS3LIB_INTERNET_H
#define PS3LIB_INTERNET_H

#define INTERNET_OK 0
#define INTERNET_ERROR -1

class internet_wrapper {
public:
    int connect_client ( const char* ip, int port );
    int send_data ( const char* data );
    void disconnect_client ( ); 
    bool is_connected ( ) const { return this->connected; };
    const char* get_ip_address ( ) const { return this->ip; };
    int get_port ( ) const { return this->port; };
private:
    const char* ip;
    int port;
    bool connected = false;
};

#endif // !PS3LIB_INTERNET_H