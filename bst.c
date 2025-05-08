#include <stdio.h> 
#include <stdlib.h>

//------------------- Structure definition--------------------
typedef struct bst {
    struct bst* left;
    int info;
    struct bst* right;
} tree_type;

//---------------- Function declarations-------------------------
void insert(tree_type** rt, int num);
void inorder(tree_type* rt);
void preorder(tree_type* rt);
void postorder(tree_type* rt);
void countNodes(tree_type* rt, int* p);
void countLeafNodes(tree_type* rt, int* leafCount);
void countLeftOnly(tree_type* rt, int* leftOnly);
void countRightOnly(tree_type* rt, int* rightOnly);
void countBothChildren(tree_type* rt, int* both);
tree_type* deleteNode(tree_type* root, int key);
tree_type* findMin(tree_type* node);
int findHeight(tree_type* root);
int findDepth(tree_type* root, int key, int depth);

//--------- Main function-----------
int main() {
    tree_type* root = NULL;
    int num, ch;

    do {
        printf("\n1. Insert\n2. Inorder Traversal\n3. Preorder Traversal\n4. Postorder Traversal");
        printf("\n5. Count Total Nodes\n6. Count Leaf Nodes");
        printf("\n7. Count Left/Right/Both Child Nodes\n8. Delete Node");
        printf("\n9. Display Traversals\n10. Exit");
        printf("\n11. Find Height of BST\n12. Find Depth of a Node");
        printf("\nEnter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
        case 1:
            printf("Enter the number to insert: ");
            scanf("%d", &num);
            insert(&root, num);
            break;
        case 2:
            printf("Inorder Traversal: ");
            inorder(root);
            printf("\n");
            break;
        case 3:
            printf("Preorder Traversal: ");
            preorder(root);
            printf("\n");
            break;
        case 4:
            printf("Postorder Traversal: ");
            postorder(root);
            printf("\n");
            break;
        case 5: {
            int count = 0;
            countNodes(root, &count);
            printf("Total number of nodes in BST: %d\n", count);
            break;
        }
        case 6: {
            int leafCount = 0;
            countLeafNodes(root, &leafCount);
            printf("Total number of leaf nodes in BST: %d\n", leafCount);
            break;
        }
        case 7: {
            int leftOnly = 0, rightOnly = 0, both = 0;
            countLeftOnly(root, &leftOnly);
            countRightOnly(root, &rightOnly);
            countBothChildren(root, &both);
            printf("Nodes with only left child: %d\n", leftOnly);
            printf("Nodes with only right child: %d\n", rightOnly);
            printf("Nodes with both children: %d\n", both);
            break;
        }
        case 8: {
            printf("Enter the value to delete: ");
            scanf("%d", &num);
            root = deleteNode(root, num);
            printf("Node deleted.\n");
            break;
        }
        case 9: {
            int tchoice;
            printf("\nChoose Traversal to Display:\n1. Inorder\n2. Preorder\n3. Postorder\nEnter your choice: ");
            scanf("%d", &tchoice);
            switch (tchoice) {
                case 1:
                    printf("Inorder Traversal: ");
                    inorder(root);
                    break;
                case 2:
                    printf("Preorder Traversal: ");
                    preorder(root);
                    break;
                case 3:
                    printf("Postorder Traversal: ");
                    postorder(root);
                    break;
                default:
                    printf("Invalid traversal choice!\n");
            }
            printf("\n");
            break;
        }
        case 10:
            printf("Exiting program.\n");
            break;
        case 11: {
            int height = findHeight(root);
            printf("Height of BST: %d\n", height);
            break;
        }
        case 12: {
            printf("Enter the value to find its depth: ");
            scanf("%d", &num);
            int depth = findDepth(root, num, 0);
            if (depth == -1)
                printf("Node not found in BST.\n");
            else
                printf("Depth of node %d: %d\n", num, depth);
            break;
        }
        default:
            printf("Invalid choice! Please enter a valid choice.\n");
        }
    } while (ch != 10);

    return 0;
}

//------------------- Function to insert a node------------------------------
void insert(tree_type** rt, int num) {
    if (*rt == NULL) {
        tree_type* p = (tree_type*)malloc(sizeof(tree_type));
        p->info = num;
        p->left = NULL;
        p->right = NULL;
        *rt = p;
    }
    else if (num < (*rt)->info) {
        insert(&((*rt)->left), num);
    }
    else if (num > (*rt)->info) {
        insert(&((*rt)->right), num);
    }
    else {
        printf("Duplicate data not allowed.\n");
    }
}

//------------------- Inorder traversal-----------------
void inorder(tree_type* rt) {
    if (rt == NULL)
        return;
    inorder(rt->left);
    printf("%d ", rt->info);
    inorder(rt->right);
}

//---------------- Preorder traversal--------------------
void preorder(tree_type* rt) {
    if (rt == NULL)
        return;
    printf("%d ", rt->info);
    preorder(rt->left);
    preorder(rt->right);
}

//------------------------ Postorder traversal--------------
void postorder(tree_type* rt) {
    if (rt == NULL)
        return;
    postorder(rt->left);
    postorder(rt->right);
    printf("%d ", rt->info);
}

//-------------------- Count total number of nodes-------------------
void countNodes(tree_type* rt, int* p) {
    if (rt == NULL)
        return;
    (*p)++;
    countNodes(rt->left, p);
    countNodes(rt->right, p);
}

//--------------------- Count total number of leaf nodes-----------------------
void countLeafNodes(tree_type* rt, int* leafCount) {
    if (rt == NULL)
        return;
    if (rt->left == NULL && rt->right == NULL) {
        (*leafCount)++;
        return;
    }
    countLeafNodes(rt->left, leafCount);
    countLeafNodes(rt->right, leafCount);
}

//----------------------- Count only left-child nodes-------------------------
void countLeftOnly(tree_type* rt, int* leftOnly) {
    if (rt == NULL)
        return;
    if (rt->left != NULL && rt->right == NULL)
        (*leftOnly)++;
    countLeftOnly(rt->left, leftOnly);
    countLeftOnly(rt->right, leftOnly);
}

//------------------ Count only right-child nodes----------------------
void countRightOnly(tree_type* rt, int* rightOnly) {
    if (rt == NULL)
        return;
    if (rt->left == NULL && rt->right != NULL)
        (*rightOnly)++;
    countRightOnly(rt->left, rightOnly);
    countRightOnly(rt->right, rightOnly);
}

//-------------------- Count nodes with both children---------------
void countBothChildren(tree_type* rt, int* both) {
    if (rt == NULL)
        return;
    if (rt->left != NULL && rt->right != NULL)
        (*both)++;
    countBothChildren(rt->left, both);
    countBothChildren(rt->right, both);
}

//----------------- Helper to find minimum node------------------------
tree_type* findMin(tree_type* node) {
    while (node && node->left != NULL)
        node = node->left;
    return node;
}

//-------------------- Delete a node and update BST--------------------
tree_type* deleteNode(tree_type* root, int key) {
    if (root == NULL)
        return root;
    if (key < root->info)
        root->left = deleteNode(root->left, key);
    else if (key > root->info)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            tree_type* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            tree_type* temp = root->left;
            free(root);
            return temp;
        }
        tree_type* temp = findMin(root->right);
        root->info = temp->info;
        root->right = deleteNode(root->right, temp->info);
    }
    return root;
}

//-------------------- Find height of the BST ----------------------
int findHeight(tree_type* root) {
    if (root == NULL)
        return -1; // height of empty tree is -1
    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

//-------------------- Find depth of a node ------------------------
int findDepth(tree_type* root, int key, int depth) {
    if (root == NULL)
        return -1; // not found
    if (root->info == key)
        return depth;
    else if (key < root->info)
        return findDepth(root->left, key, depth + 1);
    else
        return findDepth(root->right, key, depth + 1);
}
