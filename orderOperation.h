#ifndef orderOperation
#define orderOperation
#include "basic.h"
#include "myDS.h"
#include "fileIO.h"

/***********************************************
* initOrder: create order queue and initialize *
************************************************/
struct orderQueue *initOrder(void);

/*******************************************
* isEmpty: check if current queue is empty *
*          Empty: return FALSE             *
*          Non empty: return TRUE          *
********************************************/
BOOL isEmpty(void);

/********************
* addOrder: Enqueue *
*********************/
BOOL addOrder(char CustomerName[], int inventoryIds[], int inventoryQuantity[], int totalPrice);

/****************************************************************
* sortOrder: sort order by id or total price in ASC or DESC way *
*****************************************************************/
void sortOrder(int order, int order_by);

/*******************************************************
* searchOrder: search order by id and print order info *
********************************************************/
void searchOrder(int orderId);

/*************************************************************************
* completeOrder: delete queue of head for complete the most ealier order *
**************************************************************************/
BOOL completeOrder();

/***************************************************
* cancelOrder: delete queue by id for cancel order * 
****************************************************/
BOOL cancelOrder(int orderId);

/************************************************************************************************************
* checkReplenish: compare quantity between order and inventory, check whether to send a replenishment alert * 
*************************************************************************************************************/
void checkReplenish(int inventoryId);
#endif 
