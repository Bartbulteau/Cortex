cmake_minimum_required(VERSION 3.30)
project(Cortex)

set(CMAKE_CXX_STANDARD 11)

include_directories(/opt/homebrew/Cellar/crow/1.2.0/include /opt/homebrew/Cellar/asio/1.30.2/include)
link_directories(/opt/homebrew/Cellar/crow/1.2.0/lib)

add_executable(Cortex main.cpp
        core/logging/Logger.cpp
        core/logging/Logger.h
        core/logging/Message.cpp
        core/logging/Message.h
        core/LOB/LimitPrice.cpp
        core/LOB/LimitPrice.h
        core/LOB/LimitOrder.cpp
        core/LOB/LimitOrder.h
        core/LOB/LimitOrderBook.cpp
        core/LOB/LimitOrderBook.h
        core/engine/CortexEngine.cpp
        core/engine/CortexEngine.h
        core/User/Portfolio.cpp
        core/User/Portfolio.h
)

target_include_directories(Cortex PUBLIC /opt/homebrew/Cellar/crow/1.2.0/include)