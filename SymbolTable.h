#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include "main.h"


struct Node {
private:
  string method, indentifier_name, type;
  Node *next;

public:
  Node() { next = NULL; }
  Node(string method, string indentifier_name, string type) {
    this->method = method;
    this->indentifier_name = indentifier_name;
    this->type = type;
    next = NULL;
  }
  friend class SymbolTable;
};

class SymbolTable {
private:
  Node *head, *tail;
  Node *next;

public:
  SymbolTable() {
    head = NULL;
    tail = NULL;
  }
  void run(string filename);
  Node *insert(Node *head, Node *T, string dataLine);
  Node *assign(Node *head, Node *T, string dataLine);
  void print(Node *head);
  bool checkRedeclared(Node *head, Node *T);
  void block(Node *head, Node* T, string dataLine);
};
#endif