#pragma once
#include <vector>
#include <string>

class RemoteAPI {
public:
    // Constructor
    explicit RemoteAPI(const std::string& baseUrl="http://127.0.0.1:8000");

    bool ping();
    std::vector<std::string> fetchModelList();

private:
    std::string baseUrl;
};