#include <stdio.h>
#include <stdlib.h>

// Structure for a Red-Black Tree Node
typedef struct TreeNode {
    int key;      // Train or route identifier
    int load;     // Current load or occupancy
    char color;   // 'R' for red, 'B' for black
    struct TreeNode* left;
    struct TreeNode* right;
    struct TreeNode* parent;
} TreeNode;

// Structure for a Red-Black Tree
typedef struct {
    TreeNode* root;
} RedBlackTree;

// Function to create a new Red-Black Tree Node
TreeNode* createNode(int key, int load) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->key = key;
    newNode->load = load;
    newNode->color = 'R';  // New nodes are always red initially
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

// Function to insert a node into the Red-Black Tree
void insertNode(RedBlackTree* tree, int key, int load) {
    // Implementing a simplified insertion; balancing not included in this example
    TreeNode* newNode = createNode(key, load);

    // Insertion similar to a regular binary search tree
    TreeNode* parent = NULL;
    TreeNode* current = tree->root;
    while (current != NULL) {
        parent = current;
        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    newNode->parent = parent;
    if (parent == NULL) {
        tree->root = newNode;  // Tree was empty, so the new node becomes the root
    } else if (key < parent->key) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    // Additional operations for maintaining Red-Black Tree properties are not included in this example
}

// Function to print the in-order traversal of the Red-Black Tree
void inOrderTraversal(TreeNode* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("Train/Route ID: %d, Load: %d, Color: %c\n", root->key, root->load, root->color);
        inOrderTraversal(root->right);
    }
}

// Function to free memory allocated for the Red-Black Tree
void freeTree(TreeNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    RedBlackTree tree;
    tree.root = NULL;

    int numTrainsRoutes;
    printf("Enter the number of trains/routes: ");
    scanf("%d", &numTrainsRoutes);

    // Input train or route information
    for (int i = 0; i < numTrainsRoutes; i++) {
        int trainRouteID, load;
        printf("Enter Train/Route ID and Load for Train/Route %d: ", i + 1);
        scanf("%d %d", &trainRouteID, &load);

        // Inserting the train or route into the Red-Black Tree
        insertNode(&tree, trainRouteID, load);
    }

    // Display the Red-Black Tree
    printf("\nTrain/Route Information (In-Order Traversal):\n");
    inOrderTraversal(tree.root);

    // Free allocated memory
    freeTree(tree.root);

    return 0;
}
