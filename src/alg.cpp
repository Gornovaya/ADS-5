// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <cassert>

template <typename T>
class TPQueue {
  struct ITEM {
    T data;
    ITEM* next;
  };

 private:
  ITEM* first;
  ITEM* finish;
  ITEM* create(T data) {
    ITEM* t = new ITEM;
    t->data = data;
    t->next = nullptr;
    return t;
  }

 public:
  TPQueue() : first(nullptr), finish(nullptr) {}
  ~TPQueue() {
    while (first) pop();
  }

  void push(const T &data) {
    if (finish && first) {
      ITEM* val = first;
      if (val->data.prior < data.prior) {
        val = create(data);
        val->next = first;
        first = val;
      } else {
        while (val->next) {
          if (val->next->data.prior < data.prior) {
            ITEM* t = create(data);
            t->next = val->next;
            val->next = t;
            break;
          } else {
            val = val->next;
          }
        }
      }
      if (!val->next) {
        finish->next = create(data);
        finish = finish->next;
      }
    } else {
      first = create(data);
      finish = first;
    }
  }
  T pop() {
    ITEM* val = first->next;
    T data = first->data;
    delete first;
    first = val;
    return data;
  }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H
