#include <iostream>

class tree_elem {
 public:
  int m_data;
  tree_elem* m_left;
  tree_elem* m_right;
  tree_elem(int val) {
    m_left = nullptr;
    m_right = nullptr;
    m_data = val;
  }
};

class binary_tree {
 private:
  tree_elem* m_root;
  int m_size;
  void print_tree(tree_elem*);
  void delete_tree(tree_elem*);

 public:
  binary_tree(int key);
  ~binary_tree();

  void print();
  bool find(int);
  void insert(int);
  void erase(int);
  int size();
};

binary_tree::binary_tree(int key) {
  m_root = new tree_elem(key);
  m_size = 1;
}

binary_tree::~binary_tree() {
  delete_tree(m_root);
}

void binary_tree::delete_tree(tree_elem* curr) {
  if (curr) {
    delete_tree(curr->m_left);
    delete_tree(curr->m_right);
    delete curr;
  }
}

void binary_tree::print() {
  print_tree(m_root);
  std::cout << std::endl;
}

void binary_tree::print_tree(tree_elem* curr) {
  if (curr) {
    print_tree(curr->m_left);
    std::cout << curr->m_data << " ";
    print_tree(curr->m_right);
  }
}

bool binary_tree::find(int key) {
  tree_elem* curr = m_root;
  while (curr && curr->m_data != key) {
    if (curr->m_data > key)
      curr = curr->m_left;
    else
      curr = curr->m_right;
  }
  return curr != nullptr;
}

void binary_tree::insert(int key) {
  tree_elem* curr = m_root;
  while (curr && curr->m_data != key) {
    if (curr->m_data > key && curr->m_left == nullptr) {
      curr->m_left = new tree_elem(key);
      ++m_size;
      return;
    }
    if (curr->m_data < key && curr->m_right == nullptr) {
      curr->m_right = new tree_elem(key);
      ++m_size;
      return;
    }
    if (curr->m_data > key)
      curr = curr->m_left;
    else
      curr = curr->m_right;
  }
}

void binary_tree::erase(int key) {
  tree_elem* curr = m_root;
  tree_elem* parent = nullptr;
  while (curr && curr->m_data != key) {
    parent = curr;
    if (curr->m_data > key) {
      curr = curr->m_left;
    } else {
      curr = curr->m_right;
    }
  }
  if (!curr)
    return;
  if (curr->m_left == nullptr) {
    if (parent && parent->m_left == curr)
      parent->m_left = curr->m_right;
    if (parent && parent->m_right == curr)
      parent->m_right = curr->m_right;
    --m_size;
    delete curr;
    return;
  }
  if (curr->m_right == nullptr) {
    if (parent && parent->m_left == curr)
      parent->m_left = curr->m_left;
    if (parent && parent->m_right == curr)
      parent->m_right = curr->m_left;
    --m_size;
    delete curr;
    return;
  }
  tree_elem* replace = curr->m_right;
  while (replace->m_left)
    replace = replace->m_left;
  int replace_value = replace->m_data;
  erase(replace_value);
  curr->m_data = replace_value;
}

int binary_tree::size() {
  return m_size;
}
