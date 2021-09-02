#include "SymbolTable.h"

bool SymbolTable::checkRedeclared(Node *head, Node *T) {
  Node *p = head;
  while (p->next != NULL) {
    if (T->method == p->method && T->indentifier_name == p->indentifier_name)
      return false;
    p = p->next;
  }
  return true;
}
Node *SymbolTable::insert(Node *head, Node *T, string dataLine) {
  Node *p = head;

  if (head == NULL) {
    head = T;
    cout << "success" << endl;
    head->next = NULL;
    return head;
  }
  while (p->next != NULL) {
    if (T->method == p->method && T->indentifier_name == p->indentifier_name &&
        p->method == "INSERT") {
      throw(Redeclared(dataLine));
    }

    p = p->next;
  }
  if (p->next == NULL) {
    if (T->method == p->method && T->indentifier_name == p->indentifier_name &&
        p->method == "INSERT") {
      throw(Redeclared(dataLine));
    }
  }
  cout << "success" << endl;

  p->next = T;
  return head;
}
bool isNumber(const string &s) {
  for (char const &ch : s) {
    if (std::isdigit(ch) == 0)
      return false;
  }
  return true;
}

Node *SymbolTable::assign(Node *head, Node *T, string dataLine) {
  Node *p = head;
  if (head == NULL)
    throw Undeclared(dataLine);
  bool check = false;
  bool isExit = false;
  while (p->next != NULL) {
    if (p->indentifier_name == T->indentifier_name) {
      if (p->type == "number" && isNumber(T->type) ||
          p->type == "string" && !isNumber(T->type))
        check = true;
      isExit = true;
    }
    p = p->next;
  }
  if (!isExit)
    throw Undeclared(dataLine);

  if (check) {
    cout << "success" << endl;
    p->next = T;
  } else
    throw(TypeMismatch(dataLine));
  return head;
}

void SymbolTable::print(Node *head) {
  Node *p = head;
  while (p != NULL) {
    cout << p->method << " " << p->indentifier_name << " " << p->type << endl;
    p = p->next;
  }
}

void SymbolTable::block(Node *block_level, Node *T, string dataLine) {
  insert(block_level, T, dataLine);
}

void SymbolTable::run(string filename) {

  fstream newfile;
  newfile.open(filename, ios::in);
  if (newfile.is_open()) {
    string dataLine, method, indentifier_name, type;
    int level = 0;

    while (getline(newfile, dataLine)) {
      int start = 0;
      int end = dataLine.find(" ");
      method = dataLine.substr(start, end - start);
      start = end + 1;
      end = dataLine.find(" ", start);
      indentifier_name = dataLine.substr(start, end - start);
      start = end + 1;
      end = dataLine.find(" ", start);
      type = dataLine.substr(start, end - start);
      start = end + 1;
      end = dataLine.find(" ", start);

      Node *T = new Node(method, indentifier_name, type);

      if (method == "BEGIN") {
        level++;
      } else if (method == "END") {
        level--;
      } else if (level != 0) {
        Node *block_level = NULL;
        block(block_level, T, dataLine);
      }
      if (level < 0)
        throw UnknownBlock();

      if (level == 0) {
        if (method == "INSERT")
          head = insert(head, T, dataLine);
        else if (method == "ASSIGN")
          head = assign(head, T, dataLine);
        bool check = checkRedeclared(head, T);
        if (!check)
          break;
      }
    }
    if (level != 0) {
      throw UnclosedBlock(level);
    }
    newfile.close();
  }
};
