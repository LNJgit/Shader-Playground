#include "RemoteAPI.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>

//Constructor
RemoteAPI::RemoteAPI(const std::string& baseUrl) : baseUrl(baseUrl){}

bool RemoteAPI::ping() {
    try {
        cpr::Response response = cpr::Get(cpr::Url{baseUrl + "/ping"});
        if (response.status_code == 200) {
            return true;
        } else {
            std::cerr << "Ping failed with status code: " << response.status_code << std::endl;
            return false;
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception during ping: " << e.what() << std::endl;
        return false;
    }
}

std::vector<std::string> RemoteAPI::fetchModelList() {
    std::vector<std::string> modelList;
    try {
        cpr::Response response = cpr::Get(cpr::Url{baseUrl + "/models/"});

        if (response.status_code == 200) {
            auto jsonResponse = nlohmann::json::parse(response.text);

            if (!jsonResponse.contains("models") || !jsonResponse["models"].is_array()) {
                std::cerr << "Expected 'models' array in JSON, got: " << jsonResponse << "\n";
                return modelList;
            }

            for (const auto& model : jsonResponse["models"]) {
                if (model.is_string()) {
                    modelList.push_back(model.get<std::string>());
                } else {
                    std::cerr << "Skipped non-string model entry: " << model << "\n";
                }
            }
        } else {
            std::cerr << "Failed to fetch model list, status: " << response.status_code << "\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception during fetchModelList: " << e.what() << "\n";
    }

    return modelList;
}

