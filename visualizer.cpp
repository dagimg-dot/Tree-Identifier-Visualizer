#include <iostream>
using namespace std;

struct node {
  int data;
  struct node *right, *left;
};
node *newNode(int data) {
  node *Node = new node;
  Node->data = data;
  Node->left = Node->right = NULL;
  return Node;
}
bool dataTypeChecker(int n) {
  bool cond = cin.fail();
  cin.clear();
  cin.ignore(10000, '\n');
  return cond;
}
struct node *create() {
  int x;
  struct node *newNode;
  newNode = (struct node *)malloc(sizeof(struct node));
  cout << "Enter the data (0 = no input)\n";
  cin >> x;
  while (dataTypeChecker(x) != 0) {
    cout << "Invalid input, please enter data again : ";
    cin >> x;
  }
  if (x == 0)
    return 0;
  newNode->data = x;
  cout << " Enter the data of left child of " << x << endl;
  newNode->left = create();
  cout << " Enter the data of right child of " << x << endl;
  newNode->right = create();
  return newNode;
}
int height_count = 0;

int height(node *node) {
  if (node == NULL)
    return 0;
  else {
    height_count++;
    height(node->left);
  }
  return height_count;
}

// void display(node *root) {
//   cout << root->data;
//   if (root->left != NULL) {
//     display(root->left);
//   }
//   if (root->right != NULL) {
//     display(root->right);
//   }
// }
void display(int level, node *root) {
  int i;
  if (root != NULL) {
    display(level + 1, root->right);
    cout << endl;
    for (i = 0; i < level ; i++)
      cout << "        ";
    cout << root->data;
    display(level + 1, root->left);
  }
}
int main() {
  struct node *root;
  root = create();
  // cout << height(root);
  int h = height(root);
  for (int i = 1; i < h; i++) {
    cout << " ";
  }
  display(h, root);
}