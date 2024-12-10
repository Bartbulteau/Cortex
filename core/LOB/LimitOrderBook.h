//
// Created by Dev on 08/12/2024.
//

#ifndef LIMITORDERBOOK_H
#define LIMITORDERBOOK_H

#include <map>

#include "LimitOrder.h"
#include "LimitPrice.h"
#include "../logging/Logger.h"

class LimitOrderBook {
    std::unordered_map<int, LimitOrder*> _orders;
    std::map<int, LimitPrice*> _bid_prices;
    std::map<int, LimitPrice*> _ask_prices;
    Logger& _logger = Logger::getInstance();

public:
    LimitOrderBook() = default;
    ~LimitOrderBook() = default;

    void addOrder(int uid, int price, int volume, bool isBid);
    void removeOrder(int uid);
    void executeOrder(int uid, int volume, bool isBuy);

    int getBid() const;
    int getAsk() const;
    int getMid() const;
};



#endif //LIMITORDERBOOK_H
