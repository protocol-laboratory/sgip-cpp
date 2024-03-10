#include "sgipcpp/Protocol.h"
#include <cstring>
#include <ostream>
#include <stdexcept>
#include <sys/_endian.h>

size_t lengthBind(const Bind& bind) {
    return 1 + 16 + 16 + 8;
}

void encodeBind(const Bind& bind, std::vector<uint8_t>& buffer) {
    size_t offset = 16;

    buffer[offset++] = bind.login_type;
    std::memcpy(buffer.data() + offset, bind.login_name, 16);
    offset += 16;
    std::memcpy(buffer.data() + offset, bind.login_passwd, 16);
    offset += 16;
    std::memcpy(buffer.data() + offset, bind.reserve, 8);
}

BindResp decodeBindResp(const std::vector<uint8_t>& buffer) {
    BindResp bindResp;

    size_t offset = 0;

    offset += sizeof(uint32_t);
    offset += sizeof(uint32_t);

    bindResp.result = buffer[offset++];
    std::memcpy(bindResp.reserve, buffer.data() + offset, sizeof(bindResp.reserve));

    return bindResp;
}

std::vector<uint8_t> encodePdu(const Pdu& pdu) {
    size_t body_length;
    switch (pdu.header.command_id) {
        case SGIP_BIND:
            body_length = lengthBind(pdu.bind);
            break;
        default:
            throw std::runtime_error("Unsupported command ID for encoding");
    }

    std::vector<uint8_t> buffer(body_length + 16);
    uint32_t total_length = htonl(body_length + 16);
    std::memcpy(buffer.data(), &total_length, 4);

    uint32_t command_id = htonl(pdu.header.command_id);
    std::memcpy(buffer.data() + 4, &command_id, 4);

    uint32_t sequence_number = htonl(pdu.header.sequence_number);
    std::memcpy(buffer.data() + 8, &sequence_number, 8);

    switch (pdu.header.command_id) {
        case SGIP_BIND:
            encodeBind(pdu.bind, buffer);
        break;
        default:
            throw std::runtime_error("Unsupported command ID for encoding");
    }

    return buffer;
}

Pdu decodePdu(const std::vector<uint8_t>& buffer) {
    Pdu pdu;

    uint32_t command_id;
    std::memcpy(&command_id, buffer.data(), 4);
    pdu.header.command_id = ntohl(command_id);

    uint64_t sequence_number;
    std::memcpy(&sequence_number, buffer.data() + 8, 8);
    pdu.header.sequence_number = ntohl(sequence_number);

    switch (pdu.header.command_id) {
        case SGIP_BIND_RESP:
            pdu.bind_resp = decodeBindResp(buffer);
            break;
        default:
            throw std::runtime_error("Unsupported command ID for decoding");
    }

    return pdu;
}
