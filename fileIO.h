#ifndef fileIO
#define fileIO
#include "basic.h"
#include "inventoryOperation.h"
#include "orderOperation.h"

void main_menu();
void printInv(struct inventory * inv,int category);
void printOrder(struct order *ptr);
 
#endif
