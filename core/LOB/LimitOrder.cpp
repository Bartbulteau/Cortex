//
// Created by Dev on 08/12/2024.
//

#include "LimitOrder.h"

LimitOrder::LimitOrder(const int uid, const int price, const int volume, const bool isBid, LimitPrice *parentLimit)
: _uid(uid), _price(price), _volume(volume), _isBid(isBid), _parentLimit(parentLimit)
{
}
