#include <stdio.h>
#include <stdlib.h>

// Ʈ�� ��� ����ü ����
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// ���� ��� ����ü ����
struct StackNode {
    struct TreeNode* data;
    struct StackNode* next;
};

// ���� ����ü ����
struct Stack {
    struct StackNode* top;
};

// ���� �ʱ�ȭ �Լ�
struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = NULL;
    return stack;
}

// ������ ����ִ��� Ȯ���ϴ� �Լ�
int isEmpty(struct Stack* stack) {
    return (stack->top == NULL);
}

// ���ÿ� ��带 Ǫ���ϴ� �Լ�
void push(struct Stack* stack, struct TreeNode* node) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    newNode->data = node;
    newNode->next = stack->top;
    stack->top = newNode;
}

// ���ÿ��� ��带 ���ϴ� �Լ�
struct TreeNode* pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        return NULL;
    }
    struct StackNode* temp = stack->top;
    stack->top = stack->top->next;
    struct TreeNode* node = temp->data;
    free(temp);
    return node;
}

// Ʈ�� ��� ���� �Լ�
struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// �迭 ǥ������ ���� ���� ��ȸ �Լ�
void preorderTraversalArray(struct TreeNode* root, int* arr, int* index) {
    if (root == NULL) {
        return;
    }
    arr[(*index)++] = root->data;
    preorderTraversalArray(root->left, arr, index);
    preorderTraversalArray(root->right, arr, index);
}

// �迭 ǥ������ ���� ���� ��ȸ �Լ�
void inorderTraversalArray(struct TreeNode* root, int* arr, int* index) {
    if (root == NULL) {
        return;
    }
    inorderTraversalArray(root->left, arr, index);
    arr[(*index)++] = root->data;
    inorderTraversalArray(root->right, arr, index);
}

// �迭 ǥ������ ���� ���� ��ȸ �Լ�
void postorderTraversalArray(struct TreeNode* root, int* arr, int* index) {
    if (root == NULL) {
        return;
    }
    postorderTraversalArray(root->left, arr, index);
    postorderTraversalArray(root->right, arr, index);
    arr[(*index)++] = root->data;
}

// ���� ��ȸ �Լ� (��ũ ǥ����)
void preorderTraversalLink(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    struct Stack* stack = createStack();
    push(stack, root);

    while (!isEmpty(stack)) {
        struct TreeNode* node = pop(stack);
        printf("%d ", node->data);

        // ������ ����Ʈ���� ���� Ǫ���Ͽ� ���� ����Ʈ���� ���� �湮�ϵ��� �մϴ�.
        if (node->right != NULL) {
            push(stack, node->right);
        }
        if (node->left != NULL) {
            push(stack, node->left);
        }
    }
}

// ���� ��ȸ �Լ� (��ũ ǥ����)
void inorderTraversalLink(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    struct Stack* stack = createStack();
    struct TreeNode* current = root;

    while (!isEmpty(stack) || current != NULL) {
        if (current != NULL) {
            push(stack, current);
            current = current->left;
        }
        else {
            current = pop(stack);
            printf("%d ", current->data);
            current = current->right;
        }
    }
}

// ���� ��ȸ �Լ� (��ũ ǥ����)
void postorderTraversalLink(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    struct Stack* stack1 = createStack();
    struct Stack* stack2 = createStack();
    push(stack1, root);

    while (!isEmpty(stack1)) {
        struct TreeNode* node = pop(stack1);
        push(stack2, node);

        if (node->left != NULL) {
            push(stack1, node->left);
        }
        if (node->right != NULL) {
            push(stack1, node->right);
        }
    }

    while (!isEmpty(stack2)) {
        struct TreeNode* node = pop(stack2);
        printf("%d ", node->data);
    }
}

int main() {
    // Ʈ�� ��� ����
    struct TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(7);
    root->left->left = createNode(3);
    root->left->right = createNode(6);
    root->right->left = createNode(8);
    root->right->right = createNode(9);
    root->left->left->left = createNode(4);
    root->left->left->right = createNode(5);
    root->right->right->left = createNode(10);
    root->right->right->right = createNode(11);

    // �迭 ǥ������ ���� �迭 �ʱ�ȭ
    int arr[11];
    int index = 0;

    printf("��ũ ǥ���� ��ȸ ���:\n");
    printf("���� ��ȸ: ");
    preorderTraversalLink(root);
    printf("\n");

    printf("���� ��ȸ: ");
    inorderTraversalLink(root);
    printf("\n");

    printf("���� ��ȸ: ");
    postorderTraversalLink(root);
    printf("\n");

    printf("\n�迭 ǥ���� ��ȸ ���:\n");

    printf("���� ��ȸ: ");
    preorderTraversalArray(root, arr, &index);
    for (int i = 0; i < 11; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    index = 0; // �迭 �ε��� �ʱ�ȭ

    printf("���� ��ȸ: ");
    inorderTraversalArray(root, arr, &index);
    for (int i = 0; i < 11; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    index = 0; // �迭 �ε��� �ʱ�ȭ

    printf("���� ��ȸ: ");
    postorderTraversalArray(root, arr, &index);
    for (int i = 0; i < 11; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
