//
// Created by Dev on 08/12/2024.
//

#include "CortexEngine.h"

CortexEngine::CortexEngine(const std::vector<std::string>& tickers)
    : _tickers(tickers), userCount(0), orderCount(0)
{
    for (const auto& ticker : tickers) {
        LimitOrderBook lob;
        _orderbooks.insert(std::pair<std::string, LimitOrderBook>(ticker, lob));
    }
}

int CortexEngine::addUser(const int cash) {
    userCount++;
    Portfolio portfolio(userCount, _tickers, cash);
    _portfolios.insert(std::pair<int, Portfolio>(userCount, portfolio));
    return userCount;
}

int CortexEngine::addOrder(const int user_id, const std::string &ticker, const int price, const int volume, const bool isBid) {
    if (_portfolios.find(user_id) == _portfolios.end()) {
        _logger.error("CortexEngine", "Unable to find user " + std::to_string(user_id));
    }
    if (_orderbooks.find(ticker) == _orderbooks.end()) {
        _logger.error("CortexEngine", "Unable to find ticker " + ticker);
    }
    orderCount++;
    _orderbooks.find(ticker)->second.addOrder(orderCount, price, volume, isBid);
    return orderCount;
}

void CortexEngine::removeOrder(const int user_id, const std::string &ticker, const int uid) {
    if (_portfolios.find(user_id) == _portfolios.end()) {
        _logger.error("CortexEngine", "Unable to find user " + std::to_string(user_id));
    }
    if (_orderbooks.find(ticker) == _orderbooks.end()) {
        _logger.error("CortexEngine", "Unable to find ticker " + ticker);
    }
    _orderbooks.find(ticker)->second.removeOrder(uid);
}

int CortexEngine::executeOrder(const int user_id, const std::string &ticker, const int volume, const bool isBuy) {
    if (_portfolios.find(user_id) == _portfolios.end()) {
        _logger.error("CortexEngine", "Unable to find user " + std::to_string(user_id));
    }
    if (_orderbooks.find(ticker) == _orderbooks.end()) {
        _logger.error("CortexEngine", "Unable to find ticker " + ticker);
    }
    orderCount++;
    _orderbooks.find(ticker)->second.executeOrder(orderCount, volume, isBuy);
    return orderCount;
}

int CortexEngine::getBid(const std::string &ticker) {
    if (_orderbooks.find(ticker) == _orderbooks.end()) {
        _logger.error("CortexEngine", "Unable to find ticker " + ticker);
    }
    return _orderbooks.find(ticker)->second.getBid();
}

int CortexEngine::getAsk(const std::string &ticker) {
    if (_orderbooks.find(ticker) == _orderbooks.end()) {
        _logger.error("CortexEngine", "Unable to find ticker " + ticker);
    }
    return _orderbooks.find(ticker)->second.getAsk();
}
