#Cấu hình để build

cmake_minimum_required(VERSION 3.20)

project(Agent_25120032 VERSION 1.0 LANGUAGES CXX) 

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Cài đặt nlohmann_json từ github
include(FetchContent)
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)

# Kiểm tra xem CURL và SQLite3 có trong máy người dùng không
if(WIN32)
    list(PREPEND CMAKE_PREFIX_PATH "C:/msys64/ucrt64")
endif()
find_package(CURL REQUIRED)
find_package(SQLite3 REQUIRED)

# Gom toàn bộ file .cpp vào thư viện agent_core, làm bước này bởi vì add_library và target_incluede_directories không tự bung *.cpp(include từng cái rất dài và bất tiện)
file(GLOB AGENT_CORE_SOURCES CONFIGURE_DEPENDS
    "src/agent/*.cpp"
    "src/client/*.cpp"
    "src/harness/*.cpp"
    "src/tools/*.cpp"
)

# Tạo agent_core như bộ não quản lý và chạy toàn bộ thư viện, hàm .h .cpp
add_library(agent_core STATIC ${AGENT_CORE_SOURCES})
target_include_directories(agent_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(agent_core PUBLIC CURL::libcurl SQLite::SQLite3 nlohmann_json::nlohmann_json $<$<BOOL:${MINGW}>:stdc++exp>)

# Chạy chương trình
add_executable(Agent_run src/main.cpp)
target_link_libraries(Agent_run PRIVATE agent_core)

# Bật CTest cho unit test
enable_testing()