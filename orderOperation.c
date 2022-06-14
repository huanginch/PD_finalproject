#include "orderOperation.h"

extern struct category cat_list[MAX_CATEGORY];//the list of category

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
        //Check if we need replenishment
        //checkReplenish(inventoryIds[i]);

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
        if(order == 1)
        {
            for(ptr = order_queue.tail ; ptr != NULL ; ptr = ptr->prev)
            {
                printOrder(ptr);
            }
        }
        else if(order == 0)
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
            price_order[i] = ptr;
			i++;
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
            for(i = num_order-1 ; i >= 0 ; i--)
            {
                printOrder(price_order[i]);          
            }
        }
    }
}

void searchOrder(int orderId){
    if(isEmpty()){
        printf(RED_BOLD"ERROR : There is no order.\n"RESET);
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
        printf(RED_BOLD"ERROR : Order not exist.\n"RESET);
    }
}

BOOL completeOrder(){
    if(isEmpty()){
        printf(RED_BOLD"ERROR : There is no order.\n"RESET);
        return false;
    }
    else{
        num_order--;
        struct order *toComplete = order_queue.head;
          
        //Reduce book's inventory
        int i = 0;
        int type = 0;
        //check inventory type
        int inventory_complete_id = 0 , inventory_complete_num = 0;
        int isEnough = true;
        while(toComplete->inventory[i][0]){
            inventory_complete_id = toComplete->inventory[i][0];
            inventory_complete_num = toComplete->inventory[i][1];
            if(inventory_complete_id - 300 >= 0){
                type = 2;   
            }
            else if(inventory_complete_id - 200 >= 0){
                type = 1;
            }
            else if(inventory_complete_id - 100 >= 0){
                type = 0;
            }
            i++;
            struct inventory *cur = cat_list[type].inv_head;

            //Check all the inventory is enough to complete current order
            while(cur != NULL){
                if(cur->inventoryId == inventory_complete_id){
                    if(cur->quantity < inventory_complete_num){
                        printf(RED_BOLD"ALERT : Fail to complete order, Inventory[%d] quantity is not enough\n"RESET, inventory_complete_id);
                        isEnough = false;
                    }
                }
                cur = cur->next;
            }

            //Reduce Inventory
            if(isEnough){
                while(cur != NULL){
                    if(cur->inventoryId == inventory_complete_id){
                            cur->quantity -= inventory_complete_num;
                    }
                cur = cur->next;
                }
            }
        }

        //Shift current order from queue
        if(isEnough){
            toComplete = order_queue.head;
            order_queue.head = toComplete->next;
            if(order_queue.head != NULL){
                (order_queue.head)->prev = NULL;
            }
            else{
                order_queue.tail = NULL;
            }
            free(toComplete);
            printf(GRN_BOLD"MSG : Order[%04d] successfuly complete!\n"RESET, toComplete->orderId);
        }
        return true;
    }
}

BOOL cancelOrder(int orderId){
    if(isEmpty()){
        printf(RED_BOLD"ERROR : There is no order.\n"RESET);
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
				
				/*if the node to be delete is the tail node*/
				if(order_queue.tail == toCancel)
					order_queue.tail = toCancel->prev;

                /* Change next only if node to be deleted is NOT the last node */
                if (toCancel->next != NULL)
                    (toCancel->next)->prev = toCancel->prev;
            
                /* Change prev only if node to be deleted is NOT the first node */
                if (toCancel->prev != NULL)
                    (toCancel->prev)->next = toCancel->next;
				
				num_order--;
                printf(GRN_BOLD"MSG : Order[%04d] successfuly canceled!\n"RESET, toCancel->orderId); //for debug
                free(toCancel);
                return true;
            }
            else{
                cur = cur->next;
            }
        }
        printf(RED_BOLD"ERROR : Order not exist.\n"RESET);
        return false;
    }
}

void checkReplenish(int inventoryId){
    struct inventory *inv = searchInvByID(inventoryId);
    if(inv->quantity < 10){
        printf(RED_BOLD"ALERT : ID[%d] inventory quantity is lower than 10, please replenish.\n"RESET, inventoryId);
    }
}
