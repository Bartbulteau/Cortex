//
// Created by Dev on 08/12/2024.
//

#include "LimitOrderBook.h"
#include <string>
#include <sstream>

void LimitOrderBook::addOrder(const int uid, const int price, const int volume, const bool isBid) {
    LimitPrice* limit_price;
    std::map<int, LimitPrice*>* prices = isBid ? &_bid_prices : &_ask_prices;

    if (prices->find(price) == prices->end()) {
        limit_price = new LimitPrice(price);
        prices->insert(std::pair<int, LimitPrice*>(price, limit_price));
    } else {
        limit_price = prices->at(price);
    }

    auto *limit_order = new LimitOrder(uid, price, volume, isBid, limit_price);
    limit_price->addOrder(limit_order);
    _orders.insert(std::pair<int, LimitOrder*>(uid, limit_order));

    std::stringstream ss;
    ss << "Added limit order : isBid " << isBid << ", UID: " << uid << ", Price: " << price << ", Volume: " << volume;
    _logger.debug(
        "LimitOrderBook::addOrder",
        ss.str()
        );
}

void LimitOrderBook::removeOrder(const int uid) {
    if (_orders.find(uid) != _orders.end()) {
        LimitOrder* limit_order = _orders.at(uid);
        LimitPrice* limit_price = limit_order->getParentLimit();
        std::map<int, LimitPrice*>* prices = limit_order->isBid() ? &_bid_prices : &_ask_prices;

        limit_price->removeOrder(limit_order);
        _orders.erase(uid);

        delete limit_order;

        if (limit_price->getVolume() == 0) {
            prices->erase(limit_price->getPrice());
            delete limit_price;
        }

        std::stringstream ss;
        ss << "Deleted order with UID: " << uid;
        _logger.debug(
            "LimitOrderBook::removeOrder",
            ss.str()
            );

    } else {
        _logger.error(
            "LimitOrderBook::removeOrder",
            "Order with UID " + std::to_string(uid) + " not found and could not be deleted."
            );
    }
}

void LimitOrderBook::executeOrder(const int uid, const int volume, const bool isBuy) {
    int volumeLeft = volume;
    std::map<int, LimitPrice*>* prices = isBuy ? &_ask_prices : &_bid_prices;

    while (volumeLeft > 0 && !prices->empty()) {

        LimitPrice* limit_price = isBuy ? prices->begin()->second : prices->rbegin()->second;

        while (volumeLeft > 0 && limit_price->getVolume() > 0) {

            LimitOrder* limit_order = limit_price->popOrder();

            std::stringstream ss;
            ss << "Executing limit order with UID: " << limit_order->getUID() << " Price: " << limit_order->getPrice();
            _logger.debug(
                "LimitOrderBook::executeOrder",
                ss.str()
                );

            if (limit_order->getVolume() > volumeLeft) {
                limit_order->setVolume(limit_order->getVolume() - volumeLeft);
                volumeLeft = 0;
                limit_price->putBackOrder(limit_order);
            } else {
                volumeLeft -= limit_order->getVolume();
                _orders.erase(limit_order->getUID());
                delete limit_order;
            }

        }

        if (limit_price->getVolume() == 0) {
            prices->erase(limit_price->getPrice());
            delete limit_price;
        }
    }

    if (volumeLeft > 0) {
        std::stringstream ss;
        ss << "Market order with UID: " << uid << " has been partially executed and has " << volumeLeft << " volume left.";
        _logger.debug(
            "LimitOrderBook::executeOrder",
            ss.str()
            );
    } else {
        std::stringstream ss;
        ss << "Market order with UID: " << uid << " has been fully executed";
        _logger.debug(
            "LimitOrderBook::executeOrder",
            ss.str()
            );
    }
}

int LimitOrderBook::getBid() const {
    return _bid_prices.rbegin()->first;
}

int LimitOrderBook::getAsk() const {
    return _ask_prices.begin()->first;
}

int LimitOrderBook::getMid() const {
    return (getBid() + getAsk()) / 2;
}

