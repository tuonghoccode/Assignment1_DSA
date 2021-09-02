#include "SymbolTable.h"

Node *SymbolTable::insert(Node *head, Node *T) {
  Node *p = head;

  if (head == NULL) {
    head = T;
    head->next = NULL;
    return head;
  }
  while( p->next != NULL) p=p->next;
    p->next = T;
  return head;
}
void SymbolTable::print(Node *head) {
  Node *p = head;
  while (p != NULL) {
    cout << p->method << " " << p->indentifier_name << " " << p->type << endl;
    p = p->next;
  }
}

void SymbolTable::run(string filename) {

  fstream newfile;
  newfile.open(filename, ios::in);
  if (newfile.is_open()) {
    string dataLine, method, indentifier_name, type;
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
      head = insert(head, T);
    }
    print(head);
    newfile.close();
  }
  cout << "success";
};
