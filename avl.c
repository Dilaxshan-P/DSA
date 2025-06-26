#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    struct Node *left;
    int data;
    struct Node *right;
    int height;
} Node;
//kerrthi paththiya karran
Node *createNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    newNode->height = 1;

    return newNode;
}

int getHeight(Node *node)
{

    return node == NULL ? 0 : node->height;
}

int getBalanceFactor(Node *node)
{
    if (node == NULL)
    {
        return 0;
    }

    return getHeight(node->left) - getHeight(node->right);
}

Node *findMax(Node *root)
{
    if (root == NULL || root->right == NULL)
    {
        return root;
    }

    return findMax(root->right);
}

Node *findMin(Node *root)
{
    if (root == NULL|| root->right == NULL )
    {
        return root;
    }

    return findMin(root->left);
}

Node *leftRotate(Node *node)
{

    if (node == NULL)
    {
        return node;
    }

    Node *x = node->right;
    Node *y = x->left;

    x->left = node;
    node->right = y;

    node->height = 1 + (getHeight(node->left) > getHeight(node->right) ? getHeight(node->left) : getHeight(node->right));
    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));
    return x;
}

Node *rightRotate(Node *node)
{

    if (node == NULL)
    {
        return node;
    }

    Node *x = node->left;
    Node *y = x->right;

    x->right = node;
    node->left = y;

    node->height = 1 + (getHeight(node->left) > getHeight(node->right) ? getHeight(node->left) : getHeight(node->right));
    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));
    return x;
}

Node *insert(Node *root, int data)
{

    if (root == NULL)
    {
        return createNode(data);
    }

    if (root->data < data)
    {
        root->right = insert(root->right, data);
    }
    else if (root->data > data)
    {
        root->left = insert(root->left, data);
    }

    root->height = 1 + (getHeight(root->left) > getHeight(root->right) ? getHeight(root->left) : getHeight(root->right));

    int balanceFactor = getBalanceFactor(root);

    if (balanceFactor < -1 && data > root->right->data)
    {
        root = leftRotate(root);
    }
    else if(balanceFactor > 1 && data < root->left->data)
    {
        root = rightRotate(root);
    }
    else if(balanceFactor < -1 && data < root->right->data)
    {
        root->right = rightRotate(root->right);
        root = leftRotate(root);
    }
    else if(balanceFactor > 1 && data > root->left->data)
    {
        root->left = leftRotate(root->left);
        root = rightRotate(root);
    }

    return root;
}

Node *delete(Node *root, int data)
{
    if (root == NULL)
    {
        return root;
    }

    if (root->data > data)
    {
        root->left = delete (root->left, data);
    }
    else if (root->data < data)
    {
        root->right = delete (root->right, data);
    }
    else
    {

        if (root->left == NULL)
        {
            Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            Node *temp = root->left;
            free(root);
            return temp;
        }
        else
        {
            Node *temp = findMin(root->right);

            root->data = temp->data;


            root->right = delete (root->right, temp->data);
        }

        root->height = 1 + (getHeight(root->left) > getHeight(root->right) ? getHeight(root->left) : getHeight(root->right));

      
    int balanceFactor = getBalanceFactor(root);

    if (balanceFactor < -1 && data > root->right->data)
    {
        root = leftRotate(root);
    }
    else if(balanceFactor > 1 && data < root->left->data)
    {
        root = rightRotate(root);
    }
    else if(balanceFactor < -1 && data < root->right->data)
    {
        root->right = rightRotate(root->right);
        root = leftRotate(root);
    }
   else if(balanceFactor > 1 && data > root->left->data)
    {
        root->left = leftRotate(root->left);
        root = rightRotate(root);
    }

    return root;
    }
}

void inorder(struct Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main()
{
    struct Node *root = NULL;

    root = insert(root, 8);
    root = insert(root, 10);
    root = insert(root, 12);
    root = insert(root, 20);
    root = insert(root, 22);
    root = insert(root, 23);
        root = insert(root, 24);
    root = insert(root, 27);



    printf("In-order traversal before deletion:\n");
    inorder(root);

    root = insert(root, 26);

    printf("\nIn-order traversal after deleting 20:\n");
    inorder(root);

    return 0;
}