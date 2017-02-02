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
