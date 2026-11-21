cmake_minimum_required(VERSION 3.20)

project(Agent_25120032 VERSION 1.0 LANGUAGES CXX) 

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)

add_executable(Agent_25120032 src/main.cpp)
target_link_libraries(Agent_25120032 PRIVATE nlohmann_json::nlohmann_json)