#pragma once

#include <string>
#include <vector>

class Order
{

public:

    // do not alter signature of this constructor
    Order(const std::string& ordId, const std::string& secId, const std::string& side, const unsigned int qty, const std::string& user,
        const std::string& company)
        : m_orderId(ordId), m_securityId(secId), m_side(side), m_qty(qty), m_user(user), m_company(company), m_qty_matched(0) { }

    // do not alter these accessor methods
    std::string orderId() const { return m_orderId; }
    std::string securityId() const { return m_securityId; }
    std::string side() const { return m_side; }
    std::string user() const { return m_user; }
    std::string company() const { return m_company; }
    unsigned int qty() const { return m_qty; }
    unsigned int qty_matched() const { return m_qty_matched; }

    //set value of quantity
    void qty_matched(unsigned int quantity) {
        m_qty_matched = quantity;
    }

    //match order and return the quantity used
    unsigned int match(const Order& order) {
        if (m_qty_matched == m_qty) return 0; //filled

        unsigned int qty_supply = m_qty - m_qty_matched;
        unsigned int qty_demand = order.qty() - order.qty_matched();
        unsigned int qty_used = 0;

        if (qty_supply < qty_demand) {
            m_qty_matched += qty_supply;
            qty_used = qty_supply;
        }
        else {
            m_qty_matched += qty_demand;
            qty_used = qty_demand;
        }

        return qty_used;
    }

    bool operator ==(const Order& order) const
    {
        if (m_orderId == order.m_orderId)
            return true;
        else
            return false;
    }


private:

    // use the below to hold the order data
    // do not remove the these member variables
    std::string m_orderId;     // unique order id
    std::string m_securityId;  // security identifier
    std::string m_side;        // side of the order, eg Buy or Sell
    unsigned int m_qty;        // qty for this order
    std::string m_user;        // user name who owns this order
    std::string m_company;     // company for user
    unsigned int m_qty_matched; // qty matched

};

namespace std
{
    template<>
    struct hash<Order>
    {
        size_t operator()(const Order& order) const
        {
            return hash<std::string>()(order.orderId());
        }
    };
}

// Provide an implementation for the OrderCacheInterface interface class.
// Your implementation class should hold all relevant data structures you think
// are needed.
class OrderCacheInterface
{

public:

    // implememnt the 6 methods below, do not alter signatures

    // add order to the cache
    virtual void addOrder(Order order) = 0;

    // remove order with this unique order id from the cache
    virtual void cancelOrder(const std::string& orderId) = 0;

    // remove all orders in the cache for this user
    virtual void cancelOrdersForUser(const std::string& user) = 0;

    // remove all orders in the cache for this security with qty >= minQty
    virtual void cancelOrdersForSecIdWithMinimumQty(const std::string& securityId, unsigned int minQty) = 0;

    // return the total qty that can match for the security id
    virtual unsigned int getMatchingSizeForSecurity(const std::string& securityId) = 0;

    // return all orders in cache in a vector
    virtual std::vector<Order> getAllOrders() const = 0;

};
