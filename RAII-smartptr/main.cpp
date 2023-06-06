#include <cstdio>
#include <memory>

struct Node {
    std::unique_ptr<Node> next;
    Node* prev;

    int value;

    Node(int val) : value(val), next(nullptr), prev(nullptr){
    }

    void insert(int val) {
        auto node = std::make_unique<Node>(val);
        node->next = std::move(next);
        node->prev = prev;

        if (next)
            next->prev = node.get();
        if (prev)
            prev->next = std::move(node);
    }

    void erase() {
        if (next)
        {
            next->prev = prev;
        }
            
        if (prev)
            prev->next = std::move(next);
        // if (next)
        //     next->prev = prev;
    }

    ~Node() {
        printf("~Node()\n");  
    }
};

struct List {
    std::unique_ptr<Node> head;

    List() = default;

    List(List const &other) {
        printf("List copied\n");
        head.reset();
        std::unique_ptr<Node> new_head = std::make_unique<Node>(other.front()->value);
        Node* raw = other.front();
        Node* rear = new_head.get();
        while (raw->next) {
            raw = raw->next.get();
            auto new_node = std::make_unique<Node>(raw->value);
            new_node->prev = rear;
            rear->next = std::move(new_node);
            rear = rear->next.get();
        }
        head = std::move(new_head);
    }

    List &operator=(List const &) = delete; 

    List(List &&) = default;
    List &operator=(List &&) = default;

    Node *front() const {
        return head.get();
    }

    int pop_front() {
        int ret = head->value;
        head = std::move(head->next);
        return ret;
    }

    void push_front(int value) {
        auto node = std::make_unique<Node>(value);
		if (head)
		{
			head->prev = node.get();
			node->next = std::move(head);
		}
		head = std::move(node);
    }

    Node *at(size_t index) const {
        auto curr = front();
        for (size_t i = 0; i < index; i++) {
            curr = curr->next.get();
        }
        return curr;
    }
};

void print(const List &lst) {  
    printf("[");
    for (auto curr = lst.front(); curr; curr = curr->next.get()) {
        printf(" %d", curr->value);
    }
    printf(" ]\n");
}

int main() {
    List a;

    a.push_front(7);
    a.push_front(5);
    a.push_front(8);
    a.push_front(2);
    a.push_front(9);
    a.push_front(4);
    a.push_front(1);

    print(a);   // [ 1 4 9 2 8 5 7 ]

    a.at(2)->erase();

    print(a);   // [ 1 4 2 8 5 7 ]

    List b = a;

    a.at(3)->erase();

    print(a);   // [ 1 4 2 5 7 ]
    print(b);   // [ 1 4 2 8 5 7 ]

    b = {};
    a = {};

    return 0;
}
