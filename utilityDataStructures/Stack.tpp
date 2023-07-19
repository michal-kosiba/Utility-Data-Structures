namespace uds{
    
    template<typename T>
    Stack<T>::Stack(){
        
    }

    template<typename T>
    void Stack<T>::push(T value){
        this->addAtFront(value);
    }

    template<typename T>
    T Stack<T>::pop(){
        return this->getAndRemove(0);
    }

    template<typename T>
    T Stack<T>::peek(){
        return this->get(0);
    }

    template<typename T>
    int Stack<T>::getSize(){
        return LinkedList<T>::getSize();
    }
}