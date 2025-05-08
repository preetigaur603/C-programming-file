#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    int data;
    struct list *next;
} list;

int main() {
    list *p = NULL, *l = NULL; 
    int ch, x;
    int c = 0; 

    while (1) {
        // Allocate memory for a new node
        p = (list *)malloc(sizeof(list));
        if (p == NULL) {
            printf("Memory is not allocated!\n");
            return 1; // Exit if memory allocation fails
        }

        printf("Enter the data: ");
        scanf("%d", &x);
        p->data = x;

        // Insert at the beginning (left-hand side)
        p->next = l;
        l = p;

        c++; // increment node counter

        printf("Do you want to continue? (1 for Yes / 0 for No): ");
        scanf("%d", &ch);
        if (ch == 0)
            break;
    }

    printf("\nThe total number of nodes: %d\n", c);

    // Print the linked list
    p = l;
    printf("The linked list is: ");
    while (p != NULL) {
        printf("%d", p->data);
        p = p->next;
    }
    printf("NULL\n");

    return 0;
}
