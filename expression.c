#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Stack structure for operators and operands
typedef struct {
    int top;
    int items[MAX];
} Stack;

void push(Stack *s, int value) {
    if (s->top == MAX - 1) {
        printf("Stack overflow\n");
        return;
    }
    s->items[++(s->top)] = value;
}

int pop(Stack *s) {
    if (s->top == -1) {
        printf("Stack underflow\n");
        return -1;
    }
    return s->items[(s->top)--];
}

int peek(Stack *s) {
    if (s->top == -1) {
        return -1;
    }
    return s->items[s->top];
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

int applyOperation(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

int evaluateInfix(char* expression) {
    Stack values, ops;
    values.top = ops.top = -1;
    int i;

    for (i = 0; i < strlen(expression); i++) {
        if (expression[i] == ' ') continue;

        if (isdigit(expression[i])) {
            int val = 0;
            while (i < strlen(expression) && isdigit(expression[i])) {
                val = (val * 10) + (expression[i] - '0');
                i++;
            }
            i--;
            push(&values, val);
        } else if (expression[i] == '(') {
            push(&ops, expression[i]);
        } else if (expression[i] == ')') {
            while (ops.top != -1 && peek(&ops) != '(') {
                int val2 = pop(&values);
                int val1 = pop(&values);
                char op = pop(&ops);
                push(&values, applyOperation(val1, val2, op));
            }
            pop(&ops); // Remove '('
        } else {
            while (ops.top != -1 && precedence(peek(&ops)) >= precedence(expression[i])) {
                int val2 = pop(&values);
                int val1 = pop(&values);
                char op = pop(&ops);
                push(&values, applyOperation(val1, val2, op));
            }
            push(&ops, expression[i]);
        }
    }

    while (ops.top != -1) {
        int val2 = pop(&values);
        int val1 = pop(&values);
        char op = pop(&ops);
        push(&values, applyOperation(val1, val2, op));
    }

    return pop(&values);
}

int evaluatePostfix(char* expression) {
    Stack values;
    values.top = -1;
    int i;

    for (i = 0; i < strlen(expression); i++) {
        if (expression[i] == ' ') continue;

        if (isdigit(expression[i])) {
            int val = 0;
            while (i < strlen(expression) && isdigit(expression[i])) {
                val = (val * 10) + (expression[i] - '0');
                i++;
            }
            i--;
            push(&values, val);
        } else {
            int val2 = pop(&values);
            int val1 = pop(&values);
            push(&values, applyOperation(val1, val2, expression[i]));
        }
    }

    return pop(&values);
}

int main() {
    char expression[MAX];
    int choice;

    printf("Choose Evaluation Method:\n");
    printf("1. Infix Evaluation\n");
    printf("2. Postfix Evaluation\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    getchar(); // Consume newline

    printf("Enter expression: ");
    fgets(expression, MAX, stdin);
    expression[strcspn(expression, "\n")] = 0; // Remove newline character

    if (choice == 1) {
        printf("Result: %d\n", evaluateInfix(expression));
    } else if (choice == 2) {
        printf("Result: %d\n", evaluatePostfix(expression));
    } else {
        printf("Invalid choice!\n");
    }

    return 0;
}