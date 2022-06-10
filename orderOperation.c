#include "orderOperation.h"

//initial order queue
struct orderQueue order_queue = {NULL,NULL};  
static int num_order = 0;

BOOL isEmpty(void)
{  
    return !(order_queue.head) ? true : false;
}

//add a new order into queue.
BOOL addOrder(char CustomerName[], int inventoryIds[], int inventoryQuantity[], int invNum)
{
    static int orderID = 0;
    num_order++;

    //declare order_new
    struct order *order_new = malloc(sizeof(struct order));
    if(!order_new){
        return false;
    }

    //initalize order_new's inventory
    for(int i = 0 ; i < 20 ; i++){
        for(int j = 0 ; j < 2 ; j++)
            order_new->inventory[i][j] = 0;
    }
    strcpy(order_new->CustomerName , CustomerName);
    order_new->orderId = orderID++;
    float totalPrice = 0;

    for(int i = 0 ; i < invNum ; i++)
    {
        order_new->inventory[i][0] = inventoryIds[i];
        order_new->inventory[i][1] = inventoryQuantity[i];

        //Searcch for price
        struct inventory *p;
        p = searchInvByID(inventoryIds[i]);

        totalPrice += p->price * inventoryQuantity[i];
    }

    order_new->totalPrice = totalPrice;
    time(&order_new->orderDate);
    //order_new->orderDate = orderDate;
    order_new->prev = NULL;
    order_new->next = NULL;
    
    //queue is empty. enqueue order_new.
    if (isEmpty()) 
    {
        order_queue.head = order_new;
        order_queue.tail = order_new;
        return true;
    }
    
    //queue is not empty. enqueue order_new. 
    order_queue.tail->next = order_new;
    order_new->prev = order_queue.tail;
    order_queue.tail = order_new;
    
    return true;
}

//use insertion sort to sort the price to increasing
void insertion_sort(int total_price[],struct order *order[], int n) {
  for (int i = 0; i < n; i++) {
    int j = i;
    while (j > 0 && total_price[j - 1] > total_price[j]) 
    {
        int temp = total_price[j];
        total_price[j] = total_price[j - 1];
        total_price[j - 1] = temp;

        struct order *temp_order = order[j];
        order[j] = order[j - 1];
        order[j - 1] = temp_order;

        j--;
    }
  }
}

//traversal the queue with the request like : order(0:increasing, 1:decreasing), order_by(0:id, 1:total price )
void sortOrder(int order, int order_by)
{
    if(isEmpty())
    {
        printf("There is no order.\n");
        return;
    }

    struct order *ptr;
    if(order_by == 0)
    {
        if(order == 0)
        {
            for(ptr = order_queue.tail ; ptr != NULL ; ptr = ptr->prev)
            {
                printOrder(ptr);
            }
        }
        else if(order == 1)
        {
            for(ptr = order_queue.head ; ptr != NULL ; ptr = ptr->next)
            {
                printOrder(ptr);
            }
        }
    }
    else if(order_by == 1)
    {
        //use two array to store the price and the pointer of the order 
        struct order **price_order = malloc( num_order * sizeof(struct order *));
        int *total_price = malloc(num_order * sizeof( int ));
        int i = 0;
        for(ptr = order_queue.tail ; ptr != NULL ; ptr = ptr->prev)
        {
            total_price[i] = ptr->totalPrice;
            price_order[i++] = ptr;
        }

        //use insertion sort to sort the price array
        insertion_sort(total_price,price_order,num_order);
         
        if(order == 0)
        {   
            for(i = 0;i<num_order;i++)
            {
                printOrder(price_order[i]);                
            }
        }
        else if(order == 1)
        {
            for(i = num_order-1 ; i >= 0 ; i++)
            {
                printOrder(price_order[i]);          
            }
        }
    }
}

void searchOrder(int orderId){
    if(isEmpty()){
        printf("There is no order.\n");
        return;
    }
    else{
        struct order *cur = order_queue.head;
        while (cur != NULL){
            if(cur->orderId == orderId){
                printOrder(cur);
                return;
            }
            else{
                cur = cur->next;
            }
        }
        printf("Order not exist\n");
    }
}

BOOL completeOrder(){
    if(isEmpty()){
        printf("There is no order.\n");
        return false;
    }
    else{
        num_order--;
        struct order *toComplete = order_queue.head;
        order_queue.head = order_queue.head->next;
        printf("Order:%d complete!\n", toComplete->orderId); //for debug
        free(toComplete);
        return true;
    }
}

BOOL cancelOrder(int orderId){
    if(isEmpty()){
        printf("There is no order.\n");
        return false;
    }
    else{
        struct order *cur = order_queue.head;
        while (cur != NULL){
            if(cur->orderId == orderId){
                struct order *toCancel = cur;

                /* If node to be deleted is head node */
                if (order_queue.head == toCancel)
                    order_queue.head = toCancel->next;
            
                /* Change next only if node to be deleted is NOT the last node */
                if (toCancel->next != NULL)
                    toCancel->next->prev = toCancel->prev;
            
                /* Change prev only if node to be deleted is NOT the first node */
                if (toCancel->prev != NULL)
                    toCancel->prev->next = toCancel->next;

                printf("Order:%d canceled!\n", toCancel->orderId); //for debug
                free(toCancel);
                return true;
            }
            else{
                cur = cur->next;
            }
        }
        printf("Order not exist\n");
        return false;
    }
}
