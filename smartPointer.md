http://ootips.org/yonat/4dev/smart-pointers.html

# without smart pointer

    void foo()
    {
        MyClass* p(new MyClass);
        p->DoSomething();
        delete p;
    }


# with smart pointer

    void foo()
    {
        auto_ptr<MyClass> p(new MyClass);
        p->DoSomething();
    }

# dangling pointer after moving

    MyClass* p(new MyClass);
    MyClass* q = p;
    delete p;
    p->DoSomething();   // Watch out! p is now dangling!
    p = NULL;           // p is no longer dangling
    q->DoSomething();   // Ouch! q is still dangling!

# fix dangling pointer using auto_ptr overloading = 
    template <class T>
    auto_ptr<T>& auto_ptr<T>::operator=(auto_ptr<T>& rhs)
    {
        if (this != &rhs) {
            delete ptr;
            ptr = rhs.ptr;
            rhs.ptr = NULL;
        }
        return *this;
    }
