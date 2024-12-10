//
// Created by Dev on 08/12/2024.
//

#ifndef LIMITPRICE_H
#define LIMITPRICE_H

#include <list>
#include "LimitOrder.h"

class LimitOrder;

class LimitPrice {
    int _price, _volume;
    std::list<LimitOrder*> _orders;

public:
    explicit LimitPrice(const int price): _price(price), _volume(0) {}
    ~LimitPrice() = default;

    void addOrder(LimitOrder* order);
    void removeOrder(LimitOrder* order);
    void putBackOrder(LimitOrder* order);
    LimitOrder* popOrder();

    int getPrice() const { return _price; }
    int getVolume() const { return _volume; }
};



#endif //LIMITPRICE_H
