//
// Created by Dev on 08/12/2024.
//

#ifndef CORTEXENGINE_H
#define CORTEXENGINE_H

#include <string>
#include <vector>

#include "../LOB/LimitOrderBook.h"
#include "../logging/Logger.h"
#include "../User/Portfolio.h"

class CortexEngine {
    std::vector<std::string> _tickers;
    std::map<std::string, LimitOrderBook> _orderbooks;
    std::map<int, Portfolio> _portfolios;
    int userCount;
    int orderCount;
    Logger& _logger = Logger::getInstance();

public:
    explicit CortexEngine(const std::vector<std::string>& tickers);
    ~CortexEngine() = default;

    int addUser(int cash);
    int addOrder(int user_id, const std::string& ticker, int price, int volume, bool isBid);
    void removeOrder(int user_id, const std::string& ticker, int uid);
    int executeOrder(int user_id, const std::string& ticker, int volume, bool isBuy);
    int getBid(const std::string& ticker);
    int getAsk(const std::string& ticker);
};

#endif //CORTEXENGINE_H
