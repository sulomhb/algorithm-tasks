/*
Problem: Slicing Floorplan

A slicing ﬂoorplan is a decomposition of a rectangle with horizontal and vertical sides using horizontal and vertical cuts (see Figure (a)). A slicing ﬂoorplan can be represented by a binary tree, called a slicing tree, whose internal nodes represent the cuts, and whose external nodes represent the basic rectangles into which the ﬂoorplan is decomposed by the cuts (see Figure (b)). The compaction problem is deﬁned as follows.
Assume that each basic rectangle of a slicing ﬂoorplan is assigned a minimum width w and a minimum height h. The compaction problem is to ﬁnd the smallest possible height and width for each rectangle of the slicing ﬂoorplan that is compatible with the minimum dimensions of the basic rectangles. Namely, this problem requires the assignment of values h(v) and w(v) to each node v of the slicing tree, such that

Design a data structure for slicing ﬂoorplans that supports the following operations:
• Create a ﬂoorplan consisting of a single basic rectangle.              2Marks
• Decompose a basic rectangle by means of a horizontal cut.         2Marks
• Decompose a basic rectangle by means of a vertical cut               2Marks
• Assign minimum height and width to a basic rectangle                  1Mark
• Draw the slicing tree associated with the ﬂoorplan                         2Marks
• Compact the ﬂoorplan                                                                            1Mark
• Draw the compacted ﬂoorplan                                                             2Marks
*/
#include <iostream>
// 9th week group 19: Odd-Harald Lillestø Myhren, Andreas Stiansen, Suleyman Selcuk
and Shaheen Thayalan
using namespace std;
enum Type {
  Horizontal,
  Vertical,
  Boundary,
};
class Rectangle {
public:
  int minimum_width;
  int minimum_height;
  Rectangle() {
    this->minimum_width = 0;
    this->minimum_height = 0;
  }
  Rectangle(int minimum_width, int minimum_height) {
    this->minimum_width = minimum_width;
    this->minimum_height = minimum_height;
  }
};
class Node {
public:
  Type type;
  Rectangle boundary;
  int key;
  char id;
  Node *left;
  Node *right;
  Node(Type type, Rectangle boundary, int key, char id) {
    this->type = type;
    this->boundary = boundary;
    this->key = key;
    this->id = id;
    this->left = nullptr;
    this->right = nullptr;
  }
};
class BinaryTree {
public:
  int width;
  int height;
  Node *root;
  BinaryTree(int width, int height) {
    this->width = width;
    this->height = height;
    this->root = nullptr;
  }
  void add(Node *base, Type type, Rectangle boundary, int key, char id) {
    if (root) {
      if (key <= base->key) {
        if (base->left) {
          add(base->left, type, boundary, key, id);
        } else {
          base->left = new Node(type, boundary, key, id);
        }
      } else {
        if (base->right) {
          add(base->right, type, boundary, key, id);
        } else {
          base->right = new Node(type, boundary, key, id);
        }
      }
    } else {
      root = new Node(type, boundary, key, id);
    }
  }
  void addSlice(Type type, int key) {
    add(this->root, type, Rectangle(0, 0), key, ' ');
  }
  void addRectangle(Rectangle rectangle, int key, char id) {
    add(this->root, Boundary, rectangle, key, id);
  }
  void print(Node *base, int indent) {
    if (base) {
      // Print indent
      cout << string(indent, ' ') << char(192) << char(196) << char(196) << " ";
      if (base->type == Boundary)
        cout << base->boundary.minimum_width << "x" << base-
>boundary.minimum_height << " [" << base->id << "]" << endl;
      if (base->type == Horizontal)
        cout << "- [" << base->boundary.minimum_height << "x" << base-
>boundary.minimum_width << "] " << endl;
      if (base->type == Vertical)
        cout << "| [" << base->boundary.minimum_height << "x" << base-
>boundary.minimum_width << "] " << endl;
      print(base->left, indent + 4);
      print(base->right, indent + 4);
    }
  }
  Rectangle* calculate(Node* current) {
    // Check if exists
    if (current == nullptr)
      return nullptr;
    // Calculate
    Rectangle* left = calculate(current->left);
    Rectangle* right = calculate(current->right);
    if (current->type == Horizontal) {
      int width = max(left->minimum_width , right->minimum_width);
      int height = left->minimum_height + right->minimum_height;
      current->boundary = Rectangle(width, height);
    }
    if (current->type == Vertical) {
      int width = left->minimum_width + right->minimum_width;
      int height = max(left->minimum_height, right->minimum_height);
      current->boundary = Rectangle(width, height);
    }
    
    return &current->boundary;
  }
};
int main() {
  int width;
  int height;
  cout << "Width: ";
  cin >> width;
  cout << endl << "Height: ";
  cin >> height;
  cout << endl << "Slicing tree: " << endl;
  BinaryTree binary_tree = BinaryTree(width, height);
  // Start
  binary_tree.addSlice(Horizontal, 50);
  // Left
  binary_tree.addSlice(Vertical, 25);
  binary_tree.addRectangle(Rectangle(2, 7), 15, 'A');
  binary_tree.addSlice(Horizontal, 37);
  binary_tree.addRectangle(Rectangle(7, 2), 30, 'B');
  binary_tree.addSlice(Vertical, 42);
  binary_tree.addRectangle(Rectangle(5, 5), 40, 'C');
  binary_tree.addRectangle(Rectangle(3, 5), 43, 'D');
  // Right
  binary_tree.addSlice(Vertical, 75);
  binary_tree.addRectangle(Rectangle(4, 3), 70, 'E');
  binary_tree.addRectangle(Rectangle(6, 3), 80, 'F');
  // Show
  binary_tree.calculate(binary_tree.root);
  binary_tree.print(binary_tree.root, 0);
  return 0;
}