#include "sgipcpp/Client.h"
#include <iostream>

int main() {
    try {
        Client client("127.0.0.1", 8801);

        client.connect();
        std::cout << "Connected to the server." << std::endl;

        Bind bindRequest;
        bindRequest.login_type = 1;
        std::string login_name = "1234567890123456";
        std::string login_password = "1234567890123456";
        std::string reserve = "12345678";
        std::copy(login_name.begin(), login_name.end(), bindRequest.login_name);
        std::copy(login_password.begin(), login_password.end(), bindRequest.login_passwd);
        std::copy(reserve.begin(), reserve.end(), bindRequest.reserve);

        BindResp response = client.bind(bindRequest);
        if (response.result == 0) {
            std::cout << "Login successful." << std::endl;
        } else {
            std::cout << "Login failed with result code: " << static_cast<int>(response.result) << std::endl;
        }

        client.close();
        std::cout << "Connection closed." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
