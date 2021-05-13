// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <cassert>
template <typename T>
class TPQueue {
 private:
  struct ITEM {
    T data;
    ITEM* prev;
    ITEM* next;
  };
  ITEM* tail;
  ITEM* head;
  TPQueue::ITEM* create(const T& data, ITEM* prev) {
    ITEM* item = new ITEM;
    item->next = nullptr;
    item->data = data;
    item->prev = prev;
    return item;
  }

 public:
  TPQueue() : head(nullptr), tail(nullptr) {}
  ~TPQueue() {
    while (head) pop();
  }
  void push(const T& data) {
    if (tail && head) {
      ITEM* var = tail;
      while (var && data.prior > (var->data).prior) {
        var = var->prev;
      }
      if (var) {
        ITEM* temp = var->next;
        var->next = create(data, var);
        var = var->next;
        var->next = temp;
        if (temp)
          temp->prev = var;
        else
          tail = var;
      } else {
        var = create(data, nullptr);
        var->next = head;
        head->prev = var;
        head = var;
      }
    } else {
      head = create(data, nullptr);
      tail = head;
    }
  }
  T pop() {
    assert(head);
    ITEM* temp = head->next;
    T data = head->data;
    if (temp) temp->prev = nullptr;
    delete head;
    head = temp;
    return data;
  }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
