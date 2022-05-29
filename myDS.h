#include "basic.h"

#ifndef myDS_H
#define myDS_H

enum bookType {EDU , FIN, NOVEL};

struct inventory {
    int inventoryId;
    char inventoryName [MAX_BOOK_NAME];
    double price;
    int quantity;
    struct inventory *next;
};

struct categoty {
    enum bookType type;
    struct Inventory *Inventory_head;
};

/****************************************
 * Order: use queue to implement *
 ****************************************/
struct Order {
    char CustomerName [MAX_CUSTOMER_NAME];
    int orderId;
    int inventoryIds [20];
    int inventoryQuantity [20];
    int totalPrice;
    time_t orderDate;
    struct Order *prev;
    struct Order *next;
};

#endif