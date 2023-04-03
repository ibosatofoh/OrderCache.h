# OrderCache.h
This is a C++ header file that defines two classes: Order and OrderCacheInterface. 
Order is a class that holds information about a single order, such as the order ID, security ID, side (buy/sell), quantity, user name, and company. It also has methods to match it with another order, set/get the quantity matched, and check for equality with another order.

The OrderCacheInterface is an abstract class that defines six methods that should be implemented by any derived classes. These methods allow for adding an order to the cache, cancelling an order by its ID, cancelling all orders for a user, cancelling all orders for a security with a minimum quantity, getting the total quantity that can match for a given security ID, and getting all orders in the cache as a vector.

The implementation of OrderCacheInterface should hold all relevant data structures needed to perform the above operations efficiently.
