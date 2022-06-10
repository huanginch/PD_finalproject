# PD_finalproject
## This is final project for ProgramDesign class
**Tpoic: Book store database system**

## System Flow Chart
* [Link](https://whimsical.com/programdesignfinalproject-SigUNrBRUwyZ3E698HmoHf)

## How to Execute
```
$make clean
$make
```
## inventory struct:
We have three types of books and a category list.<br>Each category pointer to a linked list, which save inventories with the same type.<br>
![image](https://user-images.githubusercontent.com/57096811/173064830-e6871b46-88cb-4c73-b1be-1e14fe2857d7.png)

## order struct
The order list is a queue, which saves orders in ID sequence.

## How to use
Like the Flow Chart show, you can choose inventory or order to operate.

inventory menu has 6 option to operate:
1. add inv: by  csv file or user input
2. delete inv
3. show inv: by id or price, by descending or ascending
4. search inv: by id or name
5. replenish
6. exit: return to main menu

order menu has 6 option to operate:
1. add order: by csv file
2. cancel order
3. show order: by id or totalPrice, by descending or ascending
4. search: by id
5. complete order: shift from queue
6. exit: return to main menu

## others:
When inventory quantity is lower than 10, our system will show alert when input order data.
