#ifndef MTM_EX2_SORTEDLIST_H
#define MTM_EX2_SORTEDLIST_H
#include <cstdlib>
#include <cassert>
#include <stdexcept>
using std::string;

namespace mtm {
    const static string ERROR_OUT_OF_RANGE = "Out of range exception occurred.";
    template<class T>
    class SortedList {
    private:
        class ListNode {
            ListNode() = default;
        public:
            ListNode *nextNode;
            T value;
            explicit ListNode(T value) : nextNode(nullptr), value(value) {};
            ~ListNode() = default;
        };

        ListNode *head = nullptr;
        int listLength;

    public:
        class const_iterator;
        SortedList<T>();
        SortedList<T>(const SortedList &list);
        ~SortedList<T>();
        void clearList();

        template<class Condition>
        SortedList<T> filter(Condition condition) const;
        template<class Modifier>
        SortedList<T> apply(Modifier modifier) const;
        void copyListContent(const SortedList<T> &from);
        void remove(const_iterator iterator);
        const_iterator begin() const;
        const_iterator end() const;
        int length() const;
        SortedList<T> &operator=(const SortedList<T> &list);
        void insert(T newElement);
    };

    /**
 * @tparam Condition - A boolean function
 * @param condition - A boolean function that defines the condition the values in the new list must follow
 * @return - Returns a copy of the sorted list with values that do not pass the given condition removed
 */
    template<class T>
    template<class Condition>
    SortedList<T> SortedList<T>::filter(Condition condition) const {
        SortedList<T> filtered_list = SortedList<T>();
        for (const_iterator iterator = begin(); !(iterator == end()); ++iterator) {
            if (condition(*iterator)) {
                filtered_list.insert(*iterator);
            }
        }
        return filtered_list;
    }

    /**
 * @tparam Modifier - A function that receives a T object and returns a modified T object
 * @param modifier - The modifying function
 * @return - A copy of the list with all it's values changed according with the modifier operation
 */
    template<class T>
    template<class Modifier>
    SortedList<T> SortedList<T>::apply(Modifier modifier) const {
        SortedList<T> modified_list = SortedList<T>();
        for (const_iterator iterator = begin(); !(iterator == end()); ++iterator) {
            modified_list.insert(modifier(*iterator));
        }
        return modified_list;
    }

    template<class T>
    /**
 * Constructs an empty sorted-list
 */
    SortedList<T>::SortedList() : listLength(0) {}

    /**
         * Constructs a deep-copy of a given SortedList
         * @param list
         */
    template<class T>
    SortedList<T>::SortedList(const SortedList &list) : listLength(list.listLength) {
        copyListContent(list);
    }

    /**
 * Freeing the memory of the list by freeing each node
 */
    template<class T>
    SortedList<T>::~SortedList<T>() {
        clearList();
    }

    /**
     * @tparam T - The values of the sorted list
     * @return - An iterator that points to the first node of the lost
     */
    template<class T>
    typename SortedList<T>::const_iterator SortedList<T>::begin() const {
        return const_iterator(this, 0);
    }

    /**
    * @tparam T - The values of the sorted list
    * @return - An iterator that points to the place after the last node
    */
    template<class T>
    typename SortedList<T>::const_iterator SortedList<T>::end() const {
        return const_iterator(this, listLength);
    }

    template<class T>
    int SortedList<T>::length() const {
        return listLength;
    }

    template<class T>
    void SortedList<T>::insert(T newElement) {
        if (listLength == 0) {
            head = new ListNode(newElement);
            listLength++;
            return;
        }
        ListNode *current_node = head;
        ListNode *previous_node = nullptr;
        while (current_node != nullptr && current_node->value < newElement) {
            previous_node = current_node;
            current_node = current_node->nextNode;
        }
        ListNode *newNode;
        if (previous_node != nullptr) {
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
    class SortedList<T>::const_iterator {
    private:
        const_iterator() = default;

        friend class SortedList;

        int currentIndex{};
        const SortedList<T> *sortedList;

        const_iterator(const SortedList<T> *sortedList, int index);

    public:
        const_iterator(const const_iterator &iterator);
        const_iterator &operator=(const const_iterator &iterator) = default;
        const_iterator &operator++();
        const const_iterator operator++(int);
        bool operator==(const const_iterator &iterator) const;
        const T &operator*();
    };

    /**
    * Removes the node
    * @param iterator
    */
    template<class T>
    void SortedList<T>::remove(SortedList::const_iterator iterator) {
        ListNode *dummy = head;
        ListNode *previous_node = nullptr;
        for (int i = 0; i < iterator.currentIndex; i++) {
            previous_node = dummy;
            dummy = dummy->nextNode;
        }
        if (previous_node == nullptr) {
            head = dummy->nextNode;
            delete dummy;
        } else {
            previous_node->nextNode = dummy->nextNode;
            delete dummy;
        }
        iterator.currentIndex--;
        listLength--;
    }

    template<class T>
    SortedList<T> &SortedList<T>::operator=(const SortedList<T> &list) {
        if (this == &list) {
            return *this;
        }
        copyListContent(list);
        listLength = list.listLength;
        return *this;
    }

    /**
     * Copy the contents of a given list into the current list
     * @param from
     */
    template<class T>
    void SortedList<T>::copyListContent(const SortedList<T> &from) {
        if (from.listLength == 0) {
            return;
        }
        ListNode *dummy = from.head->nextNode;
        auto *temp_node = new ListNode(from.head->value);
        ListNode *current_node = temp_node;
        for (int i = 1; i < from.listLength; i++) {
            current_node->nextNode = new ListNode(dummy->value);
            dummy = dummy->nextNode;
            current_node = current_node->nextNode;
        }
        clearList();
        head = temp_node;
    }

    /**
    *  Deletes every node in the list from the memory
    */
    template<class T>
    void SortedList<T>::clearList() {
        ListNode *to_delete = nullptr;
        while (head != nullptr) {
            to_delete = head;
            head = head->nextNode;
            delete to_delete;
        }
    }

    /**
     * Constructs a list iterator with a given index of a node to point to
     * @tparam T - Value type of the list
     * @param sortedList
     * @param index
     */
    template<class T>
    SortedList<T>::const_iterator::const_iterator(const SortedList<T> *sortedList, int index)
            :  currentIndex(index), sortedList(sortedList) {}
    /**
     * Constructs an iterator copy of a given iterator
     * @tparam T
     * @param iterator
     */
    template<class T>
    SortedList<T>::const_iterator::const_iterator(const SortedList<T>::const_iterator &iterator)
            : currentIndex(iterator.currentIndex), sortedList(iterator.sortedList) {}

    /**
     * advanced the iterator to the next node
     * @tparam T
     * @param iterator
     * @throws out_of_range if the iterator points to the node after the end of the list
     */
    template<class T>
    typename SortedList<T>::const_iterator &SortedList<T>::const_iterator::operator++() {
        if (currentIndex >= sortedList->listLength) {
            throw std::out_of_range(ERROR_OUT_OF_RANGE);
        }
        ++currentIndex;
        return *this;
    }

    /**
     * advanced the iterator to the next node
     * @tparam T
     * @param iterator
     * @throws out_of_range if the iterator points to the node after the end of the list
     */
    template<class T>
    const typename SortedList<T>::const_iterator SortedList<T>::const_iterator::operator++(int) {
        if (currentIndex >= sortedList->listLength) {
            throw std::out_of_range(ERROR_OUT_OF_RANGE);
        }
        const_iterator previous = *this;
        ++*this;
        return previous;
    }

    /**
     * Compares to list iterators
     * @tparam T
     * @param iterator
     * @return True - if the iterators are of the same list and point to the same index
     */
    template<class T>
    bool SortedList<T>::const_iterator::operator==(const SortedList<T>::const_iterator &iterator) const {
        return currentIndex == iterator.currentIndex && sortedList == iterator.sortedList;
    }

    /**
     * @tparam T
     * @return - The value inside the node the iterator currently points to
     */
    template<class T>
    const T &SortedList<T>::const_iterator::operator*() {
        ListNode *current_node = sortedList->head;
        for (int i = 0; i < currentIndex; i++) {
            current_node = current_node->nextNode;
        }
        return current_node->value;
    }
}

#endif //MTM_EX2_SORTEDLIST_H
