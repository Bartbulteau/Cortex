//
// Created by Dev on 08/12/2024.
//

#ifndef LIMITORDER_H
#define LIMITORDER_H

#include "LimitPrice.h"

class LimitPrice;

class LimitOrder {
    int _uid, _price, _volume;
    bool _isBid;
    LimitPrice* _parentLimit;

public:
    LimitOrder(int uid, int price, int volume, bool isBid, LimitPrice* parentLimit);
    ~LimitOrder() = default;

    int getUID() const { return _uid; }
    int getPrice() const { return _price; }
    int getVolume() const { return _volume; }
    LimitPrice* getParentLimit() const { return _parentLimit; }
    bool isBid() const { return _isBid; }

    void setVolume(const int volume) { _volume = volume; }
};



#endif //LIMITORDER_H
