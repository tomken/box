
#include "link.h"

List::List() {
    printf("链表被创造了\n");
    _head = 0;
    _tail = 0;
}

List::~List() {
    printf("链表被删除了\n");
}

void List::push_front(int value) {
    if (_head) {
        Node* node = new Node(); // 创建新的节点
        node->value = value;     // 给节点赋予数据
        node->next = _head;      // 把该节点的下一个指向头
        _head = node;            // 把链表的头指向该节点
    } else {
        _head = new Node();      // 创建新的节点
        _head->value = value;    // 给节点赋予数据
        _head->next = 0;         // 把该节点的下一个指向空
        _tail = _head;
    }
}

void List::push_back(int value) {
    if (_tail) {
        Node* node = new Node(); // 创建新的节点
        node->value = value;     // 给节点赋予数据
        node->next = 0;          // 把该节点的下一个指向空
        _tail->next = node;      //把尾指向这个节点
        _tail = node;            // 把链表的尾指向该节点
    } else {
        _head = new Node();      // 创建新的节点
        _head->value = value;    // 给节点赋予数据
        _head->next = 0;         // 把该节点的下一个指向空
        _tail = _head;
    }
}

void List::pop_front() {
    if (!_head) {
        return;
    }

    Node* n = _head->next;
    delete _head;
    
    if (n) {
        _head = n;
    } else {
        _head = 0;
        _tail = 0;
    }
}

void List::pop_back() {
    if (!_head) {
        return;
    }

    while (1) {
        Node* p = _head;
        Node* n = p->next;

        if (n == _tail) {
            _tail = p;
            _tail->next = 0;
            delete n;
            return;
        }

        if (!n) {
            delete _head;
            _head = 0;
            _tail = 0;
            return;
        }
    }
}

void List::dump() {
    Node* n = _head;
    while (n) {
        printf("===> %d\n", n->value);
        n = n->next;
    }
}
