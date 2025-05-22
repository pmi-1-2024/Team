#pragma once
#include "Order.h"
#include "Book.h"
#include <vector>
#include <string>
using namespace std;

class OrderManager {
private:
    vector<Order>* orders;
    vector<Book>* books;
    string filename = "orders.txt";

public:
    OrderManager(vector<Order>* orderList, vector<Book>* bookList);
    void loadOrders();
    void saveOrders();
    void createOrder(const string& userId);
    void viewOrdersByUser(const string& userId);
    void viewAllOrders();
    void returnOrder();
};
