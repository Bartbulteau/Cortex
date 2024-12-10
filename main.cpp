#include <crow.h>
#include <string>
#include <vector>

#include "core/engine/CortexEngine.h"

int main() {

    const std::vector<std::string> tickers = {
        "META",
        "AMZN",
        "AAPL",
        "NFLX",
        "GOOG"
    };

    CortexEngine engine(tickers);
    std::mutex engineMutex;

    crow::SimpleApp app;
    app.loglevel(crow::LogLevel::Warning);

    CROW_ROUTE(app, "/")([](){
        return R"(
            <!DOCTYPE html>
            <html lang="en">
                <head>
                    <meta charset="UTF-8">
                    <title>Cortex API</title>
                </head>
            <body style="
                background-color:black;
                font-family: 'Helvetica', 'Arial', sans-serif;
                margin: 0;
                height: 100vh;
                display: flex;
                flex-direction: column;
                justify-content: center;
                align-items: center;
                color: white;
            ">
                <h1 style="
                    font-size: 100px;
                ">
                    Cortex Trading API ®
                </h1>
            </body>
            </html>)";
    });

    CROW_ROUTE(app, "/submit_limit_order").methods(crow::HTTPMethod::POST)([&engine, &engineMutex] (const crow::request& req) -> crow::response {
        try {
            const auto reqBody = crow::json::load(req.body);
            if (!reqBody) {
                return {400, R"({"status":"error","message":"Invalid JSON format"})"};
            }
            const int user_id = static_cast<int>(reqBody["user_id"].i());
            const bool isBid = reqBody["is_bid"].b();
            const std::string ticker = reqBody["ticker"].s();
            const int price = static_cast<int>(reqBody["price"].i());
            const int volume = static_cast<int>(reqBody["volume"].i());
            int uid;

            {
                std::lock_guard<std::mutex> lock(engineMutex);
                uid = engine.addOrder(user_id, ticker, price, volume, isBid);
            }


            crow::json::wvalue jsonResponse = {
                {"status", "success"},
                {"message", "Order added"},
                {"uid", std::to_string(uid)},
            };
            return {200, jsonResponse};
        }
        catch (const std::exception& e) {
            crow::json::wvalue jsonError = {
                
                {"message", e.what()}
            };
            return  {400, jsonError};
        }
    });

    CROW_ROUTE(app, "/submit_market_order").methods(crow::HTTPMethod::POST)([&engine, &engineMutex] (const crow::request& req) -> crow::response {
        try {
            const auto reqBody = crow::json::load(req.body);
            if (!reqBody) {
                return {400, R"({"status":"error","message":"Invalid JSON format"})"};
            }

            const int user_id = static_cast<int>(reqBody["user_id"].i());
            const bool isBid = reqBody["is_bid"].b();
            const std::string ticker = reqBody["ticker"].s();
            const int volume = static_cast<int>(reqBody["volume"].i());

            {
                std::lock_guard<std::mutex> lock(engineMutex);
                engine.executeOrder(user_id, ticker, volume, isBid);
            }

            crow::json::wvalue jsonResponse = {
                {"status", "success"},
                {"message", "Order executed"}
            };
            return {200, jsonResponse};
        }
        catch (const std::exception& e) {
            crow::json::wvalue jsonError = {
                {"message", e.what()}
            };
            return  {400, jsonError};
        }
    });

    CROW_ROUTE(app, "/submit_cancel_order").methods(crow::HTTPMethod::POST)([&engine, &engineMutex] (const crow::request& req) -> crow::response {
        try {
            const auto reqBody = crow::json::load(req.body);
            if (!reqBody) {
                return {400, R"({"status":"error","message":"Invalid JSON format"})"};
            }
            const int user_id = static_cast<int>(reqBody["user_id"].i());
            const std::string ticker = reqBody["ticker"].s();
            const int uid = static_cast<int>(reqBody["uid"].i());

            {
                std::lock_guard<std::mutex> lock(engineMutex);
                engine.removeOrder(user_id, ticker, uid);
            }

            crow::json::wvalue jsonResponse = {
                {"status", "success"},
                {"message", "Order removed"}
            };
            return {200, jsonResponse};
        }
        catch (const std::exception& e) {
            crow::json::wvalue jsonError = {
                {"message", e.what()}
            };
            return  {400, jsonError};
        }
    });

    CROW_ROUTE(app, "/add_user").methods(crow::HTTPMethod::POST)([&engine, &engineMutex] (const crow::request& req) -> crow::response {
        try {
            const auto reqBody = crow::json::load(req.body);
            if (!reqBody) {
                return {400, R"({"status":"error","message":"Invalid JSON format"})"};
            }
            const int cash = static_cast<int>(reqBody["cash"].i());
            int user_id;

            {
                std::lock_guard<std::mutex> lock(engineMutex);
                user_id = engine.addUser(cash);
            }

            crow::json::wvalue jsonResponse = {
                {"status", "success"},
                {"message", "Order added"},
                {"user_id", std::to_string(user_id)}
            };
            return {200, jsonResponse};
        }
        catch (const std::exception& e) {
            crow::json::wvalue jsonError = {
                {"message", e.what()}
            };
            return  {400, jsonError};
        }
    });

    CROW_ROUTE(app, "/prices").methods(crow::HTTPMethod::GET)([&engine, &engineMutex] (const crow::request& req) -> crow::response {
        try {
            const auto reqBody = crow::json::load(req.body);
            if (!reqBody) {
                return {400, R"({"status":"error","message":"Invalid JSON format"})"};
            }
            const std::string ticker = reqBody["ticker"].s();
            int bid, ask;

            {
                std::lock_guard<std::mutex> lock(engineMutex);
                bid = engine.getBid(ticker);
                ask = engine.getAsk(ticker);
            }

            crow::json::wvalue jsonResponse = {
                {"status", "success"},
                {"message", "Prices sent"},
                {"bid", std::to_string(bid)},
                {"ask", std::to_string(ask)}
            };
            return {200, jsonResponse};
        }
        catch (const std::exception& e) {
            crow::json::wvalue jsonError = {
                {"message", e.what()}
            };
            return  {400, jsonError};
        }
    });

    app.port(80).multithreaded().run_async();

    return 0;
}