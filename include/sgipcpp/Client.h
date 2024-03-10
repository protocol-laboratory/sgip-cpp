#ifndef CLIENT_H
#define CLIENT_H

#include "BoundAtomic.h"
#include "Protocol.h"
#include "asio.hpp"
#include <string>

class Client {
public:
    Client(const std::string& host, uint16_t port);
    ~Client();

    void connect();
    BindResp bind(const Bind& bind_request);
    void close();

private:
    std::string host_;
    uint16_t port_;
    asio::io_context io_context_;
    asio::ip::tcp::socket socket_;
    BoundAtomic* sequence_number_;

    void send(const std::vector<uint8_t>& data);
    std::vector<uint8_t> receive(size_t length);
};

#endif //CLIENT_H
