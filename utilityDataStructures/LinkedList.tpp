namespace uds{
    
    template<typename T>
    LinkedList<T>::LinkedList(){
        this->head = nullptr;
        this->size = 0;
    }   

    template<typename T>
    LinkedList<T>::~LinkedList(){
        if(head != nullptr){
            clear();
        }
    } 

    template<typename T>
    T* LinkedList<T>::toArray(){
        T* array= new T[this->size];
        for (int i = 0; i < this->size; i++)
        {
            array[i] = this->get(i);
        }
        return array;
    }

    template<typename T>
    void LinkedList<T>::add(const T value){
        typename Collection<T>::template Node<T> *newNode = new typename Collection<T>::template Node<T>(value, head);
        head = newNode;
        this->size++;
    }

    template<typename T>
    void LinkedList<T>::addAt(const T value, int index){
        this->validateIndex(index);
        
        typename Collection<T>::template Node<T>* currentNode = head;
        typename Collection<T>::template Node<T>* previousNode = nullptr;
        for(int i=0; i<index; i++){
            previousNode = currentNode;
            currentNode = currentNode->next;
        }

        if(previousNode == nullptr){
            head = new typename Collection<T>::template Node<T>(value, currentNode);
        }
        else{
            previousNode->next = new typename Collection<T>::template Node<T>(value, currentNode);
        }
        this->size++;
    }

    template<typename T>
    void LinkedList<T>::addAtFront(const T value){
        add(value);
    }

    template<typename T>
    void LinkedList<T>::addAtBack(const T value){
        if(head == nullptr){
            head = new typename Collection<T>::template Node<T>(value, nullptr);
            this->size++;
        }else{
            typename Collection<T>::template Node<T>* currentNode = head;
            while(currentNode->next != nullptr){
                currentNode = currentNode->next;
            }
            currentNode->next = new typename Collection<T>::template Node<T>(value, nullptr);
            this->size++;
        }
    }

    template<typename T>
    T LinkedList<T>::get(int index){
        this->validateIndex(index);
        
        typename Collection<T>::template Node<T>* currentNode = head;
        for(int i=0; i<index; i++){
            currentNode = currentNode->next;
        }
        return currentNode->value;
    }

    template<typename T>
    void LinkedList<T>::remove(int index){
        getAndRemove(index);
    }

    template<typename T>
    T LinkedList<T>::getAndRemove(int index){
        this->validateIndex(index);
        
        typename Collection<T>::template Node<T>* currentNode = head;
        typename Collection<T>::template Node<T>* previousNode = nullptr;
        for(int i=0; i<index; i++){
            previousNode = currentNode;
            currentNode = currentNode->next;
        }

        T returnValue = currentNode->value;
        if(previousNode == nullptr){
            head = head->next;
        }
        else{
            previousNode->next = currentNode->next;
        }

        delete currentNode;
        this->size--;
        return returnValue;
    }

    template<typename T>
    int LinkedList<T>::getSize(){
        return this->size;
    }

    template<typename T>
    void LinkedList<T>::print(){
        std::cout << "Linked list: " << std::endl;
        std::cout << "\tsize: " << this->size << std::endl;
        std::cout << "\tnodes: [";
        for(int i=0; i<this->size; i++){
            std::cout << this->get(i);
            if(i != this->size - 1){
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }

    template<typename T>
    void LinkedList<T>::deleteNode(typename Collection<T>::template Node<T>* node){
        if(node->next != nullptr){
            deleteNode(node->next);
        }
        this->size--;
        delete node;
    }

    template<typename T>
    void LinkedList<T>::clear(){
        deleteNode(head);
        head = nullptr;
    }

    template<typename T>
    void LinkedList<T>::reverse(){
        if(head == nullptr){
            return;
        }
        typename Collection<T>::template Node<T>* previous = nullptr;
        typename Collection<T>::template Node<T>* current = head;
        typename Collection<T>::template Node<T>* next = nullptr;
       
        while(current != nullptr){
            next = current->next;
            current->next = previous;
            previous = current;
            current = next;
        }
        head = previous;
    }

    template<typename T>
    template<typename U>
    LinkedList<T>::LinkedListIterator<U>::LinkedListIterator(typename Collection<U>::template Node<U>* start){
        this->current = start;
    }

    template<typename T>
    template<typename U>
    U LinkedList<T>::LinkedListIterator<U>::getNext(){
        if(current == nullptr){
            throw std::out_of_range("Attempt to acces index out of list range");
        }

        U returnValue = current->value;
        current = current->next;
        return returnValue;
    }

    template<typename T>
    template<typename U>
    bool LinkedList<T>::LinkedListIterator<U>::hasNext(){
        return current == nullptr ? false : true;
    }


    template<typename T>
    Iterator<T>* LinkedList<T>::getIterator(){
        return new LinkedListIterator<T>(head);
    }
}