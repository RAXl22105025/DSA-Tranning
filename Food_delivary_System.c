// introduction
// 1.customer order place korbe
// 2.Order Queue through data store hobe
// 3.Delivary history stack ee store hobe
// Costomer place order =>order add in queue
// Kitchen process =>front order process
// Delivery done=>remove queue
// History save=>delivered order stack insert
// display delivary history
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Order
{
    int orderId;
    char customerName[50];
    char foodName[50];
};

struct Order queue[MAX];

int front = -1;
int rear = -1;

struct Order stack[MAX];
int top = -1;

void placeOrder();
void processOrder();
void deliverOrder();
void displayQueue();
void displayHistory();

int isQueueFull();
int isQueueEmpty();

int isStackFull();
int isStackEmpty();



int isQueueFull()
{
    if (rear == MAX - 1)
        return 1;
    else
        return 0;
}

int isQueueEmpty()
{
    if (front == -1 || front > rear)
        return 1;
    else
        return 0;
}

int isStackFull()
{
    if (top == MAX - 1)
        return 1;
    else
        return 0;
}

int isStackEmpty()
{
    if (top == -1)
        return 1;
    else
        return 0;
}

void placeOrder()
{
    if (isQueueFull())
    {
        printf("\nOrder Queue is Full!\n");
        return;
    }

    struct Order newOrder;

    printf("\nEnter Order ID: ");
    scanf("%d", &newOrder.orderId);

    getchar();

    printf("Enter Customer Name: ");
    fgets(newOrder.customerName, sizeof(newOrder.customerName), stdin);
    newOrder.customerName[strcspn(newOrder.customerName, "\n")] = '\0';

    printf("Enter Food Name: ");
    fgets(newOrder.foodName, sizeof(newOrder.foodName), stdin);
    newOrder.foodName[strcspn(newOrder.foodName, "\n")] = '\0';

  
    if (front == -1)
        front = 0;

    rear++;

    queue[rear] = newOrder;

    printf("\nOrder Added Successfully!\n");
}

void processOrder()
{
    if (isQueueEmpty())
    {
        printf("\nNo Orders to Process!\n");
        return;
    }

    printf("\nKitchen Processing Order:\n");

    printf("Order ID      : %d\n", queue[front].orderId);
    printf("Customer Name : %s\n", queue[front].customerName);
    printf("Food Name     : %s\n", queue[front].foodName);
}

void deliverOrder()
{
    if (isQueueEmpty())
    {
        printf("\nNo Orders to Deliver!\n");
        return;
    }

    if (isStackFull())
    {
        printf("\nDelivery History Stack Full!\n");
        return;
    }

  
    top++;
    stack[top] = queue[front];

    printf("\nOrder Delivered Successfully!\n");

    printf("Delivered Order ID : %d\n", queue[front].orderId);

   
    front++;
}

void displayQueue()
{
    if (isQueueEmpty())
    {
        printf("\nNo Pending Orders!\n");
        return;
    }

    printf("\nPENDING ORDERS \n");

    for (int i = front; i <= rear; i++)
    {
        printf("\nOrder ID      : %d\n", queue[i].orderId);
        printf("Customer Name : %s\n", queue[i].customerName);
        printf("Food Name     : %s\n", queue[i].foodName);
    }
}

void displayHistory()
{
    if (isStackEmpty())
    {
        printf("\nNo Delivery History Found!\n");
        return;
    }

    printf("\nDELIVERY HISTORY....\n");

    for (int i = top; i >= 0; i--)
    {
        printf("\nOrder ID      : %d\n", stack[i].orderId);
        printf("Customer Name : %s\n", stack[i].customerName);
        printf("Food Name     : %s\n", stack[i].foodName);
    }
}
int main()
{
    int choice;

    while (1)
    {
       
        printf("\n FOOD DELIVERY MANAGEMENT SYSTEM");
        
        printf("\n1. Place Order");
        printf("\n2. Process Kitchen Order");
        printf("\n3. Deliver Order");
        printf("\n4. Display Pending Orders");
        printf("\n5. Display Delivery History");
        printf("\n6. Exit");

        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            placeOrder();
            break;

        case 2:
            processOrder();
            break;

        case 3:
            deliverOrder();
            break;

        case 4:
            displayQueue();
            break;

        case 5:
            displayHistory();
            break;

        case 6:
            printf("\nSystem Closed...\n");
            exit(0);

        default:
            printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}