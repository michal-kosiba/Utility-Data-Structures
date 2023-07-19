namespace uds{
    
    template<typename T>
    template<typename U>
    Collection<T>::Node<U>::Node() {
        this->value = U();
        this->next = nullptr;
    }

    template<typename T>
    template<typename U>
    Collection<T>::Node<U>::Node(const U value, Node* next){
        this->value = value;
        this->next = next;
    }

    template<typename T>
    void Collection<T>::validateIndex(int index){
        if(index <= -1){
            throw std::domain_error("Provided negative number for a list index");
        }
        if(index >= this->size){
            throw std::out_of_range("Attempt to acces index out of list range");
        }
    }
}