#include <stdio.h>
#include <stdlib.h>

// 이진 트리 노드 구조체
struct TreeNode {
    char data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// 스택을 위한 구조체 정의
struct StackNode {
    struct TreeNode* data;
    struct StackNode* next;
};

struct StackNode* createStackNode(struct TreeNode* data) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void push(struct StackNode** stack, struct TreeNode* data) {
    struct StackNode* newNode = createStackNode(data);
    newNode->next = *stack;
    *stack = newNode;
}

struct TreeNode* pop(struct StackNode** stack) {
    if (*stack == NULL) {
        return NULL;
    }
    struct TreeNode* top = (*stack)->data;
    struct StackNode* temp = *stack;
    *stack = (*stack)->next;
    free(temp);
    return top;
}

// 수식 트리를 만드는 함수
struct TreeNode* createExpressionTree(char postfix[]) {
    struct StackNode* stack = NULL;

    for (int i = 0; postfix[i] != '\0'; i++) {
        char token = postfix[i];

        struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        newNode->data = token;
        newNode->left = NULL;
        newNode->right = NULL;

        if (token >= '0' && token <= '9') {
            push(&stack, newNode);
        }
        else {
            struct TreeNode* operand2 = pop(&stack);
            struct TreeNode* operand1 = pop(&stack);

            newNode->right = operand2;
            newNode->left = operand1;

            push(&stack, newNode);
        }
    }

    return pop(&stack);
}

// 이진 트리의 노드 수를 계산하는 함수 (반복적 방법)
int countNodes(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    int nodeCount = 0;
    struct StackNode* stack = NULL;
    push(&stack, root);

    while (stack != NULL) {
        struct TreeNode* current = pop(&stack);
        nodeCount++;

        if (current->right) {
            push(&stack, current->right);
        }

        if (current->left) {
            push(&stack, current->left);
        }
    }

    return nodeCount;
}

// 중간 계산 과정을 출력하는 함수
void printIntermediateResults(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    struct StackNode* stack = NULL;
    push(&stack, root);

    while (stack != NULL) {
        struct TreeNode* current = pop(&stack);

        if (current->right) {
            push(&stack, current->right);
        }

        if (current->left) {
            push(&stack, current->left);
        }

        if (current->data >= '0' && current->data <= '9') {
            printf("%c", current->data);
        }
        else {
            printf(" %c ", current->data);
        }

        if (current->data == '+' || current->data == '-' || current->data == '*' || current->data == '/') {
            printf("= ");
        }
        else {
            printf("\n");
        }
    }
}

// 수식 트리를 계산하고 결과 출력
float evaluateExpressionTree(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    if (root->data >= '0' && root->data <= '9') {
        return (float)(root->data - '0');
    }

    float leftResult = evaluateExpressionTree(root->left);
    float rightResult = evaluateExpressionTree(root->right);

    float result = 0;
    switch (root->data) {
    case '+':
        result = leftResult + rightResult;
        break;
    case '-':
        result = leftResult - rightResult;
        break;
    case '*':
        result = leftResult * rightResult;
        break;
    case '/':
        result = leftResult / rightResult;
        break;
    }

    return result;
}

int main() {
    char postfix[] = "2+3+4*5-6/7+9";

    struct TreeNode* root = createExpressionTree(postfix);
    printf("중간 계산 과정:\n");
    printIntermediateResults(root);

    int nodeCount = countNodes(root);
    printf("이진 트리의 노드 수: %d\n", nodeCount);

    float result = evaluateExpressionTree(root);
    printf("계산 결과: %.2f\n", result);

    return 0;
}
