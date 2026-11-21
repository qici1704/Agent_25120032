#include <curl/curl.h>
#include <sqlite3.h>
#include <fstream>
#include <print>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct EnvCheck {
    EnvCheck() = default;
    EnvCheck(const EnvCheck&) = delete("Khong duoc sao chep (C++26 check)");
};
int main() {
    EnvCheck check;
    (void)check;
    std::ifstream file("config.json");
    if (!file.is_open()) {
        std::println(stderr, "Khong mo duoc config.json");
        return 1;
    }
    json cfg = json::parse(file);
    std::println("Model: {}", cfg["llm"]["model"].get<std::string>());
    std::println("Base URL: {}", cfg["llm"]["base_url"].get<std::string>());
    std::println("libcurl: {}", curl_version());
    std::println("SQLite3: {}", sqlite3_libversion());
    return 0;
}