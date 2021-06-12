#ifndef MTM_EX2_SORTEDLIST_H
#define MTM_EX2_SORTEDLIST_H

template<class T>
class SortedList {
private:
    class ListNode{
    public:
        T value;
        ListNode *nextNode;
        ListNode(T value): nextNode(nullptr), value(value) {};
        ListNode() = default;
    };
    ListNode *head = nullptr;
    int listLength;
public:
    SortedList<T>();
    SortedList<T>(const SortedList &list);
    ~SortedList<T>();
    class Iterator;

    Iterator begin() const;
    Iterator end() const;
    int length() const;
    void insert(T newElement);
};

template<class T>
SortedList<T>::SortedList() : listLength(0){}

template<class T>
SortedList<T>::SortedList(const SortedList &list) : listLength(list.listLength){
    if(listLength == 0){
        return;
    }
    ListNode *dummy = list.head->nextNode;
    head = new ListNode(list.head->value);
    ListNode *current_node = head;
    for(int i=1; i<listLength; i++){
        current_node->nextNode = new ListNode(dummy->value);
        dummy = dummy->nextNode;
        current_node = current_node->nextNode;
    }
}

template<class T>
SortedList<T>::~SortedList<T>() {
    ListNode *to_delete = nullptr;
    while(head != nullptr){
        to_delete = head;
        head = head->nextNode;
        delete to_delete;
    }
}

template<class T>
typename SortedList<T>::Iterator SortedList<T>::begin() const {
    return Iterator(this, 0);
}

template<class T>
typename SortedList<T>::Iterator SortedList<T>::end() const {
    return Iterator(this, listLength);
}

template<class T>
int SortedList<T>::length() const {
    return listLength;
}

template<class T>
void SortedList<T>::insert(T newElement) {
    if(listLength == 0){
        head = new ListNode(newElement);
        listLength++;
        return;
    }
    ListNode *current_node = head;
    ListNode *previous_node = nullptr;

    while(current_node != nullptr && current_node->value < newElement){
        previous_node = current_node;
        current_node = current_node->nextNode;
    }
    ListNode *newNode;
    if(previous_node != nullptr){
        previous_node->nextNode = new ListNode(newElement);
        newNode = previous_node->nextNode;
        newNode->nextNode = current_node;
    } else {
        head = new ListNode(newElement);
        head->nextNode = current_node;
    }
    listLength++;
}


template<class T>
class SortedList<T>::Iterator{
private:
    Iterator() = default;
    friend class SortedList;
    int currentIndex{};
    const SortedList<T> *sortedList;
    Iterator(const SortedList<T> *sortedList, int index);
public:
    Iterator(const Iterator &iterator);
    Iterator& operator=(const Iterator &iterator) = default;
    Iterator& operator++();
    const Iterator operator++(int);
    bool operator==(const Iterator &iterator) const;
    const T& operator*();
};
template<class T>
SortedList<T>::Iterator::Iterator(const SortedList<T> *sortedList, int index)
    : sortedList(sortedList), currentIndex(index){}

template<class T>
SortedList<T>::Iterator::Iterator(const SortedList<T>::Iterator &iterator)
    : sortedList(iterator.sortedList), currentIndex(iterator.currentIndex){}

template <class T>
typename SortedList<T>::Iterator& SortedList<T>::Iterator::operator++() {
    ++currentIndex;
    return *this;
}

template<class T>
const typename SortedList<T>::Iterator SortedList<T>::Iterator::operator++(int) {
    Iterator previous = *this;
    ++*this;
    return previous;
}


template<class T>
bool SortedList<T>::Iterator::operator==(const SortedList<T>::Iterator &iterator) const {
    return currentIndex == iterator.currentIndex;
}

template<class T>
const T &SortedList<T>::Iterator::operator*() {
    if(currentIndex >= sortedList->listLength){
        //TODO: throw exception
    }
    ListNode *current_node = sortedList->head;
    for(int i=0; i<currentIndex; i++){
        current_node = current_node->nextNode;
    }
    return current_node->value;
}

#endif //MTM_EX2_SORTEDLIST_H
