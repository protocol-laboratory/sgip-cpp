#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <cstdint>
#include <vector>

constexpr uint32_t SGIP_BIND = 0x00000001;
constexpr uint32_t SGIP_BIND_RESP = 0x80000001;
constexpr uint32_t SGIP_UNBIND = 0x00000002;
constexpr uint32_t SGIP_UNBIND_RESP = 0x80000002;
constexpr uint32_t SGIP_SUBMIT = 0x00000003;
constexpr uint32_t SGIP_SUBMIT_RESP = 0x80000003;
constexpr uint32_t SGIP_DELIVER = 0x00000004;
constexpr uint32_t SGIP_DELIVER_RESP = 0x80000004;
constexpr uint32_t SGIP_REPORT = 0x00000005;
constexpr uint32_t SGIP_REPORT_RESP = 0x80000005;
constexpr uint32_t SGIP_ADDSP = 0x00000006;
constexpr uint32_t SGIP_ADDSP_RESP = 0x80000006;
constexpr uint32_t SGIP_MODIFYSP = 0x00000007;
constexpr uint32_t SGIP_MODIFYSP_RESP = 0x80000007;
constexpr uint32_t SGIP_DELETESP = 0x00000008;
constexpr uint32_t SGIP_DELETESP_RESP = 0x80000008;
constexpr uint32_t SGIP_QUERYROUTE = 0x00000009;
constexpr uint32_t SGIP_QUERYROUTE_RESP = 0x80000009;
constexpr uint32_t SGIP_ADDTELESEG = 0x0000000A;
constexpr uint32_t SGIP_ADDTELESEG_RESP = 0x8000000A;
constexpr uint32_t SGIP_MODIFYTELESEG = 0x0000000B;
constexpr uint32_t SGIP_MODIFYTELESEG_RESP = 0x8000000B;
constexpr uint32_t SGIP_DELETETELESEG = 0x0000000C;
constexpr uint32_t SGIP_DELETETELESEG_RESP = 0x8000000C;
constexpr uint32_t SGIP_ADDSMG = 0x0000000D;
constexpr uint32_t SGIP_ADDSMG_RESP = 0x8000000D;
constexpr uint32_t SGIP_MODIFYSMG = 0x0000000E;
constexpr uint32_t SGIP_MODIFYSMG_RESP = 0x8000000E;
constexpr uint32_t SGIP_DELETESMG = 0x0000000F;
constexpr uint32_t SGIP_DELETESMG_RESP = 0x8000000F;
constexpr uint32_t SGIP_CHECKUSER = 0x00000010;
constexpr uint32_t SGIP_CHECKUSER_RESP = 0x80000010;
constexpr uint32_t SGIP_USERRPT = 0x00000011;
constexpr uint32_t SGIP_USERRPT_RESP = 0x80000011;
constexpr uint32_t SGIP_TRACE = 0x00001000;
constexpr uint32_t SGIP_TRACE_RESP = 0x80001000;

struct Header {
    uint32_t total_length;
    uint32_t command_id;
    uint64_t sequence_number;
};

struct Bind {
    char login_type;
    char login_name[16];
    char login_passwd[16];
    char reserve[8];
};

struct BindResp {
    char result;
    char reserve[8];
};

struct Pdu {
    Header header;
    union {
        Bind bind;
        BindResp bind_resp;
    };
};

size_t lengthBind();
std::vector<uint8_t> encodePdu(const Pdu& pdu);
Pdu decodePdu(const std::vector<uint8_t>& buffer);

#endif //PROTOCOL_H
