#include "Config.h"

#include <filesystem>
#include <fstream>


namespace fs = std::filesystem;

void Config::load(const std::string &configDir) {
    if (!fs::exists(configDir)) {
        fs::create_directory(configDir);
        saveDefaults(configDir);
    }
    std::ifstream configFile(configDir + "/config.json");
    this->config = json::parse(configFile);
    this->loaded = true;
}

bool Config::isLoaded() {
    return this->loaded;
}

std::vector<int> Config::getEnabled() {
    return this->config.at("enabled").get<std::vector<int>>();
}

std::vector<int> Config::getDisabled() {
    return this->config.at("disabled").get<std::vector<int>>();
}

void Config::saveDefaults(const std::string &configDir) {
    std::ofstream file(configDir + "/config.json");
    config["enabled"] = {};
    config["disabled"] = {};
    file << config.dump(4);
    file.close();
}