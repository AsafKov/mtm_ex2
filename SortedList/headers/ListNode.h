#ifndef MTM_EX2_LISTNODE_H
#define MTM_EX2_LISTNODE_H


class ListNode {
    int data;
    ListNode *nextNode;

public:
    explicit ListNode(int value);
    int getData() const;
};

ListNode::ListNode(int value) {
    this->data = value;
    this->nextNode = nullptr;
}

int ListNode::getData() const {
    return this->data;
}
#endif //MTM_EX2_LISTNODE_H
