//
// Created by Dev on 08/12/2024.
//

#include "Portfolio.h"
#include <sstream>

Portfolio::Portfolio(const int user_id, const std::vector<std::string> &portfolio, const int cash)
    : _cash(cash), _user_id(user_id)
{
    for (const auto& ticker : portfolio)
        _portfolio.insert(std::pair<std::string, int>(ticker, 0));
}

int Portfolio::get_quantity(const std::string &ticker) {
    if (_portfolio.find(ticker) != _portfolio.end()) {
        return _portfolio.at(ticker);
    }
    std::stringstream ss;
    ss << "Portfolio " << _user_id;
    _logger.error(ss.str(), "Unable to find ticker " + ticker);
    return -1;
}

void Portfolio::buy(const std::string &ticker, const int quantity, const int price) {
    if (_portfolio.find(ticker) != _portfolio.end()) {
        _portfolio.at(ticker) += quantity;
        _cash -= quantity*price;
    }
    else {
        std::stringstream ss;
        ss << "Portfolio " << _user_id;
        _logger.error(ss.str(), "Unable to find ticker " + ticker);
    }
}

void Portfolio::sell(const std::string &ticker, const int quantity, const int price) {
    buy(ticker, -quantity, price);
}


