#include "inventoryOperation.h"
#include "sort.h"

struct category cat_list[MAX_CATEGORY];//the list of category
int type1_len;//type1 inventory list length
int type2_len;//type2 inventory list length
int type3_len;//type3 inventory list length

void initInv(void){
	int i;
	for(i = 0; i < MAX_CATEGORY; i++){
		//made the cat_list
		cat_list[i].type = i;
		cat_list[i].inv_head = NULL;
	}

	type1_len = 0;
	type2_len = 0;
	type3_len = 0;
}

bool addInv(char name[], double price, int quantity, enum bookType type){
	//id for each inventory
	static int IDs[] = {100, 200, 300};

	//new inventory
	struct inventory *new_inv = malloc(sizeof(struct inventory));
	new_inv->inventoryId = IDs[type];
	strcpy(new_inv->inventoryName, name);
	new_inv->price = price;
	new_inv->quantity = quantity;
	new_inv->next = NULL;

	if(cat_list[type].inv_head == NULL){//if the list is null
		cat_list[type].inv_head = new_inv;
	}
	else{
		struct inventory *current = cat_list[type].inv_head;
		
		while(current->next != NULL){//find the end of the list
			current = current->next;
		}

		current->next = new_inv;
	}

	IDs[type]++;//increase id

	//increase list length
	if(type == EDU){
		type1_len++;
	}
	else if(type == FIN){
		type2_len++;
	}
	else if(type == NOVEL){
		type3_len++;
	}
	else{
		return false;
	}

	return true;
}

struct category *traversaInv(){

	return cat_list;
	// int i;
	// for(i = 0; i < MAX_CATEGORY; i++){
	// 	printf("type %d:\n", i);//print type
	// 	struct inventory *current = cat_list[i].inv_head;
	// 	printf("id\tname\tprice\tquantity\n");//print title
	// 	while(current != NULL){
	// 		//printf each item
	// 		printf("%d\t%s\t%.2f\t%d\n", current->inventoryId, current->inventoryName, current->price, current->quantity);
	// 		current = current->next;
	// 	}
		
	// }
}

bool sortInv(int order, int order_by){
	int i = 0;
	if(order == 0){
		//ascending
		if(order_by == 0){
			//sort by id
			for(i = 0; i < MAX_CATEGORY; i++){
				cat_list[i].inv_head = _sort(cat_list[i].inv_head,cmpAscById);
			}
		}
		else if(order_by == 1){
			//sort by price
			for(i = 0; i < MAX_CATEGORY; i++){
				cat_list[i].inv_head = _sort(cat_list[i].inv_head,cmpAscByPrice);
			}
		}
		else{
			//fprintf(stderr, "Wrong order_by parameter, please input 0 or 1\n");
			return false;
		}
	}
	else if(order == 1){
		//descending
		if(order_by == 0){
			//sort by id
			for(i = 0; i < MAX_CATEGORY; i++){
				cat_list[i].inv_head = _sort(cat_list[i].inv_head,cmpDesById);
			}
		}
		else if(order == 1){
			//sort by price
			for(i = 0; i < MAX_CATEGORY; i++){
				cat_list[i].inv_head = _sort(cat_list[i].inv_head,cmpDesByPrice);
			}
		}
		else{
			//fprintf(stderr, "Wrong order_by parameter, please input 0 or 1\n");
			return false;
		}
		
		
	}
	else{
		//fprintf(stderr, "Wrong order parameter, please input 0 or 1\n");
		return false;
	}

	return true;

}

/***********柏恩part************/
bool deleteInv(int id){//delete produce
	struct inventory *cur, *prev;
	for(int i = 0; i < MAX_CATEGORY; i++){
		for (cur = cat_list[i].inv_head , prev = NULL;
			cur != NULL && cur->inventoryId==id;
			prev = cur, cur = cur->next)
			;
		if (cur == NULL)
		{
			
			return false;
		}
		if (prev == NULL)
		{
			struct inventory *next_inv = cat_list[i].inv_head;
			cat_list[i].inv_head = next_inv->next;
		}
		else
		{
			
			prev->next = cur->next; 
		}
		 free(cur);
	     return true;
	}
	return false;
}

bool searchInvByID(int id){//search id and print the specific item
	struct inventory *p;
	int count = 0;
	p = malloc(sizeof(struct inventory));
	for(int i = 0; i < MAX_CATEGORY; i++){
		for (p = cat_list[i].inv_head; p != NULL; p = p->next)
	{ //找id位置

		if (p->inventoryId==id)
		{   printf("id\tname\tprice\tquantity\n");
			//print item
			printf("%d\t%s\t%f\t%d\n", p->inventoryId, p->inventoryName, p->price, p->quantity);
			count++;
            return true;
		}
	} }//
	if (count == 0)
	{    return false;
		// printf("Don't has this inventory\n");
	}
  return false;
}

bool searchInvByName(char name[]){//search name and print the specific item
	struct inventory *p;
	int count = 0;
	p = malloc(sizeof(struct inventory));
	for(int i = 0; i < MAX_CATEGORY; i++){
		for (p = cat_list[i].inv_head; p != NULL; p = p->next)
	{ //找name位置

		if (strcmp(p->inventoryName,name)==0)
		{   
			 printf("id\tname\tprice\tquantity\n");
			//print item
			printf("%d\t%s\t%f\t%d\n", p->inventoryId, p->inventoryName, p->price, p->quantity);
			count++;
           return true;
		}
	} }
	if (count == 0)
	{
		return false;
	}
   return false;
}

/************end************/

void replenish(int replenish_id,int replenish_num){
	int i = 0;
	int type = 0;
	//check inventory type
	if(replenish_id - 300 > 0){
		type = 2;
	}
	else if(replenish_id - 200 > 0){
		type = 1;
	}
	else if(replenish_id - 100 > 0){
		type = 0;
	}

	struct inventory *cur = cat_list[type].inv_head;
	while(cur != NULL){
		if(cur->inventoryId == replenish_id){
			cur->quantity += replenish_num;
			break;
		}

		cur = cur->next;
	}
}

int cmpAscById(const void *a, const void *b){

	int a_ID = ((struct inventory *)a)->inventoryId;
	int b_ID = ((struct inventory *)b)->inventoryId;

	// printf("%d\n", a_ID - b_ID);
	return a_ID - b_ID;

}

int cmpDesById(const void *a, const void *b){

	int a_ID = ((struct inventory *)a)->inventoryId;
	int b_ID = ((struct inventory *)b)->inventoryId;

	// printf("%d\n", b_ID - a_ID);
	return b_ID - a_ID;

}

int cmpAscByPrice(const void *a, const void *b){

	double a_price = ((struct inventory *)a)->price;
	double b_price = ((struct inventory *)b)->price;

	// printf("%f\n", a_price);
	// printf("%f\n", b_price);

	if(a_price > b_price){
		return 1;
	}
	else if(a_price == b_price){
		return 0;
	}
	else{
		return -1;
	}
}

int cmpDesByPrice(const void *a, const void *b){

	double a_price = ((struct inventory *)a)->price;
	double b_price = ((struct inventory *)b)->price;

	// printf("%f\n", a_price);
	// printf("%f\n", b_price);

	if(a_price > b_price){
		return -1;
	}
	else if(a_price == b_price){
		return 0;
	}
	else{
		return 1;
	}
}
