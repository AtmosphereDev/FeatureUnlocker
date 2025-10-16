#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Config {
private:
    json config;
    bool loaded = false;
public:
    void load(const std::string &configDir);
    bool isLoaded();
    std::vector<int> getEnabled();
    std::vector<int> getDisabled();
    void saveDefaults(const std::string &configDir);
};
