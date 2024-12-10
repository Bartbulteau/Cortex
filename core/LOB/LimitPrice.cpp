//
// Created by Dev on 08/12/2024.
//

#include "LimitPrice.h"

void LimitPrice::addOrder(LimitOrder *order) {
    _volume += order->getVolume();
    _orders.push_back(order);
}

void LimitPrice::removeOrder(LimitOrder *order) {
    _volume -= order->getVolume();
    _orders.remove(order);
}

void LimitPrice::putBackOrder(LimitOrder *order) {
    _volume += order->getVolume();
    _orders.push_front(order);
}

LimitOrder *LimitPrice::popOrder() {
    LimitOrder *order = _orders.front();
    _orders.pop_front();

    _volume -= order->getVolume();

    return order;
}


