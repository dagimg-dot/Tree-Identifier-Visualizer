#include <iostream>
using namespace std;

int INT_MAX = 250;

struct node {
  int data;
  struct node *right, *left;
};
node *newNode(int data) {
  node *Node = new node;
  Node->data = data;
  Node->left = Node->right = NULL;
  return (Node);
}
// function declaration
void onlyBST(node *root);
void onlyAVL(node *root);
void onlyHeap(node *root);
void all(node *root);
bool dataTypeChecker(int n);

bool isBalanced(node *root, int &maxh1, int &minh1) {
  if (root == NULL) {
    maxh1 = minh1 = 0;
    return true;
  }
  int lmxh1, lmnh1;
  int rmxh1, rmnh1;
  if (isBalanced(root->left, lmxh1, lmnh1) == false)
    return false;
  if (isBalanced(root->right, rmxh1, rmnh1) == false)
    return false;
  maxh1 = max(lmxh1, rmxh1) + 1;
  minh1 = min(lmnh1, rmnh1) + 1;
  if (maxh1 <= 2 * minh1)
    return true;
  return false;
}

struct node *create() {
  int x; // different local variable would be created for each function call
  struct node *newNode;
  newNode = (struct node *)malloc(sizeof(struct node));
  cout << "Enter the data or enter 'n/N' for no node" << endl;
  cin >> x;
    while (dataTypeChecker(x) != 0) {
      cout << "Invalid input, please enter data again : ";
      cin >> x;
    }
  if (x == 0)
    return 0;
  newNode->data = x;
  cout << " Enter the data of left child of " << x << endl;
  newNode->left = create(); // create function always return pointer to node(address)
  cout << " Enter the data of right child of " << x << endl;
  newNode->right = create(); // this recursion
  return newNode;
}

int height(node *node) { // get the height means the number of nodes along the
                         // longest path from the root
  // node down to the farthest leaf node of the tree.
  if (node == NULL)
    return 0;
  return 1 + max(height(node->left), height(node->right));
}

bool checkBST(node *root) {
  if (root == NULL)
    return 0;

  int d = root->data;
  bool r1 = true, r2 = true;
  if (root->left != NULL) {
    if (d < root->left->data)
      r1 = 0;
    else
      r1 = checkBST(root->left);
  }

  if (root->right != NULL) {
    if (d > root->right->data)
      r2 = 0;
    else
      r2 = checkBST(root->right);
  }
  return r1 && r2;
}

bool checkAVL(node *root) {
  int lh;
  int rh;
  if (root == NULL)
    return 1;
  lh = height(root->left);  // left height
  rh = height(root->right); // right height
  if (abs(lh - rh) <= 1 && checkAVL(root->left) && checkAVL(root->right))
    return 1;
  return 0;
}

unsigned int countNodes(struct node *root) {
  if (root == NULL)
    return (0);
  return (1 + countNodes(root->left) + countNodes(root->right));
}

bool isComplete(struct node *root, unsigned int index1,
                    unsigned int number_nodes) {
  if (root == NULL)
    return (true);
  if (index1 >= number_nodes)
    return (false);
  // Recur for left and right subtrees
  return (isComplete(root->left, 2 * index1 + 1, number_nodes) &&
          isComplete(root->right, 2 * index1 + 2, number_nodes));
}

bool isHeap(struct node *root) {
  if (root->left == NULL && root->right == NULL)
    return (true);
  if (root->right == NULL) {
    return (root->data >= root->left->data);
  } else {
    if (root->data >= root->left->data && root->data >= root->right->data)
      return ((isHeap(root->left)) && (isHeap(root->right)));
    else
      return (false);
  }
}

bool checkHeap(struct node *root) {
  unsigned int node_count = countNodes(root);
  unsigned int index1 = 0;
  if (isComplete(root, index1, node_count) && isHeap(root))
    return true;
  return false;
}

void menu() {
  char test;
  do {
    system("cls");
    int choice;
    cout << "\t\t=============================================================="
            "=============\n";
    cout << "\t\t\t\t          BINARY TREE CHECKER \n";
    cout << "\t\t=============================================================="
            "=============\n\n";
    cout << "\t\t--------------------------------------------------------------"
            "-------------\n";
    cout << "\t\t\t1. Check if a given Binary Tree is BST tree \n";
    cout << "\t\t\t2. Check if a given Binary Tree is AVL tree \n";
    cout << "\t\t\t3. Check if a given Binary Tree is HEAP tree\n";
    cout << "\t\t\t4. Check what type of binary tree is it \n";
    cout << "\t\t--------------------------------------------------------------"
            "------------\n";
    cout << " \t ==> Please enter the data of the binary tree based on the "
            "instruction\n";
    cout << "\t\t--------------------------------------------------------------"
            "------------\n";
    struct node *root;
    root = create();
    cout << "\t\t--------------------------------------------------------------"
            "------------\n";
    cout << "Choose what you want to do : ";
    cin >> choice;
    while (dataTypeChecker(choice) != 0 || choice < 1 || choice > 5) {
      cout << "Invalid choice, Choose what you want to do : ";
      cin >> choice;
    }
    if (choice)
      switch (choice) {
      case 1:
        onlyBST(root);
        break;
      case 2:
        onlyAVL(root);
        break;
      case 3:
        onlyHeap(root);
        break;
      case 4:
        all(root);
        break;
      }
    cout << "Do you want to continue again(Y/N)" << endl;
    cin >> test;
  } while (test == 'Y' || test == 'y');
}

int main() {
  menu();
  return 0;
}

void onlyBST(node *root) {
  if (checkBST(root))
    cout << "Given binary tree is a BST \n";
  else
    cout << "Given binary tree is not a BST\n";
}

void onlyAVL(node *root) {
  if (checkAVL(root))
    cout << "Given binary tree is a AVL and BST \n ALL AVL TREE IS BST\n";
  else
    cout << "Given binary tree is not a AVL\n";
}

void onlyHeap(node *root) {
  if (checkHeap(root))
    cout << "Given binary tree is a HEAP \n";
  else
    cout << "Given binary tree is not a HEAP\n";
}

void all(node *root) {
  if (checkBST(root)) {
    cout << "Given binary tree is a BST, ";
    if (checkAVL(root)) {
      cout << "AVL, ";
    }
    cout << "\n----------------------------------\n";
  } else if (checkHeap(root)) {
    cout << "Given binary tree is a HEAP \n";
    cout << "----------------------------------\n";
  } else {
    cout << "The given binary tree is not BST,AVL and HEAP\n";
  }
}

bool dataTypeChecker(int n) {
  bool cond = cin.fail();
  cin.clear();
  cin.ignore();
  return cond;
}