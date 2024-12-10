//
// Created by Dev on 08/12/2024.
//

#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <map>
#include <string>
#include <vector>

#include "../logging/Logger.h"

class Portfolio {
    std::map<std::string, int> _portfolio;
    int _cash;
    int _user_id;
    Logger& _logger = Logger::getInstance();

public:
    explicit Portfolio(int user_id, const std::vector<std::string> &portfolio, int cash);
    Portfolio(const Portfolio &portfolio) = default;
    ~Portfolio() = default;

    int get_user_id() const { return _user_id; }
    int get_cash() const { return _cash; }
    int get_quantity(const std::string &ticker);
    void buy(const std::string &ticker, int quantity, int price);
    void sell(const std::string &ticker, int quantity, int price);
};



#endif //PORTFOLIO_H
