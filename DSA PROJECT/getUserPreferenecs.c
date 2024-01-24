#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int routeId;
    int scheduledTime;
    int estimatedCost;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Function to create a new tree node
TreeNode* createNode(int routeId, int scheduledTime, int estimatedCost) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->routeId = routeId;
    newNode->scheduledTime = scheduledTime;
    newNode->estimatedCost = estimatedCost;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a node into the binary search tree
TreeNode* insert(TreeNode* root, int routeId, int scheduledTime, int estimatedCost) {
    if (root == NULL) {
        return createNode(routeId, scheduledTime, estimatedCost);
    }

    if (scheduledTime < root->scheduledTime) {
        root->left = insert(root->left, routeId, scheduledTime, estimatedCost);
    } else if (scheduledTime > root->scheduledTime) {
        root->right = insert(root->right, routeId, scheduledTime, estimatedCost);
    }

    return root;
}

// Function to find the minimum value node in a binary search tree
TreeNode* findMin(TreeNode* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// Function to delete a node from the binary search tree
TreeNode* deleteNode(TreeNode* root, int scheduledTime) {
    if (root == NULL) {
        return root;
    }

    if (scheduledTime < root->scheduledTime) {
        root->left = deleteNode(root->left, scheduledTime);
    } else if (scheduledTime > root->scheduledTime) {
        root->right = deleteNode(root->right, scheduledTime);
    } else {
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        TreeNode* temp = findMin(root->right);
        root->scheduledTime = temp->scheduledTime;
        root->estimatedCost = temp->estimatedCost;
        root->right = deleteNode(root->right, temp->scheduledTime);
    }

    return root;
}

// Function to search for a node based on scheduled time
TreeNode* search(TreeNode* root, int scheduledTime) {
    if (root == NULL || root->scheduledTime == scheduledTime) {
        return root;
    }

    if (scheduledTime < root->scheduledTime) {
        return search(root->left, scheduledTime);
    } else {
        return search(root->right, scheduledTime);
    }
}

// Function to perform an in-order traversal of the binary search tree
void inorderTraversal(TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("Route %d: Scheduled Time = %d, Estimated Cost = %d\n", root->routeId, root->scheduledTime, root->estimatedCost);
        inorderTraversal(root->right);
    }
}

// Function to free the memory allocated for the binary search tree
void freeTree(TreeNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    TreeNode* root = NULL;
    int numRoutes;

    printf("Enter the number of scheduled routes: ");
    scanf("%d", &numRoutes);

    printf("Enter details for each route (routeId, scheduledTime, estimatedCost):\n");
    for (int i = 0; i < numRoutes; i++) {
        int routeId, scheduledTime, estimatedCost;
        printf("Route %d: ", i + 1);
        scanf("%d %d %d", &routeId, &scheduledTime, &estimatedCost);
        root = insert(root, routeId, scheduledTime, estimatedCost);
    }

    // Print the original scheduled routes
    printf("\nOriginal Scheduled Routes:\n");
    inorderTraversal(root);

    // Perform operations (you can modify this based on your requirements)
    int scheduledTimeToDelete;
    printf("\nEnter the scheduled time to delete a route: ");
    scanf("%d", &scheduledTimeToDelete);
    root = deleteNode(root, scheduledTimeToDelete);

    int scheduledTimeToSearch;
    printf("Enter the scheduled time to search for a route: ");
    scanf("%d", &scheduledTimeToSearch);
    TreeNode* searchResult = search(root, scheduledTimeToSearch);
    
    // Print the updated scheduled routes
    printf("\nUpdated Scheduled Routes:\n");
    inorderTraversal(root);

    // Print the search result
    if (searchResult != NULL) {
        printf("\nRoute found for scheduled time %d: Route %d\n", scheduledTimeToSearch, searchResult->routeId);
    } else {
        printf("\nNo route found for scheduled time %d.\n", scheduledTimeToSearch);
    }

    // Free allocated memory
    freeTree(root);

    return 0;
}
