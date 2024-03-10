#include "sgipcpp/Client.h"
#include <iostream>

Client::Client(const std::string& host, uint16_t port)
    : host_(host), port_(port), socket_(io_context_) {
    sequence_number_ = new BoundAtomic(1, 0x7FFFFFFF);
}

Client::~Client() {
    close();
    delete sequence_number_;
}

void Client::connect() {
    asio::ip::tcp::resolver resolver(io_context_);
    asio::connect(socket_, resolver.resolve(host_, std::to_string(port_)));
}

BindResp Client::bind(const Bind& bind_request) {
    Pdu pdu;
    pdu.header.total_length = sizeof(Bind) + sizeof(Header);
    pdu.header.command_id = SGIP_BIND;
    pdu.header.sequence_number = sequence_number_->next_val();
    pdu.bind = bind_request;

    send(encodePdu(pdu));

    auto length_data = receive(4);
    uint32_t total_length = ntohl(*reinterpret_cast<uint32_t*>(length_data.data()));

    auto resp_data = receive(total_length - 4);
    Pdu resp_pdu = decodePdu(resp_data);
    return resp_pdu.bind_resp;
}

void Client::close() {
    socket_.close();
}

void Client::send(const std::vector<uint8_t>& data) {
    asio::write(socket_, asio::buffer(data));
}

std::vector<uint8_t> Client::receive(size_t length) {
    std::vector<uint8_t> buffer(length);
    asio::read(socket_, asio::buffer(buffer));
    return buffer;
}
