https://msdn.microsoft.com/en-us/library/hh279676.aspx

```diff
+ A unique_ptr does not share its pointer. 
+ It cannot be copied to another unique_ptr, passed by value to a function, 
+ or used in any Standard Template Library (STL) algorithm that requires copies to be made. 
+ A unique_ptr can only be moved. 
```
This means that the ownership of the memory resource is transferred to another unique_ptr and the original unique_ptr no longer owns it. We recommend that you restrict an object to one owner, because multiple ownership adds complexity to the program logic. Therefore, when you need a smart pointer for a plain C++ object, use unique_ptr, and when you construct a unique_ptr, use the make_unique helper function.


https://msdn.microsoft.com/en-us/library/hh279676.aspx


```diff
+ The unique_ptr class supersedes auto_ptr, and can be used as an element of STL containers.
```
unique_ptr uniquely manages a resource. Each unique_ptr object stores a pointer to the object that it owns or stores a null pointer. A resource can be owned by no more than one unique_ptr object; when a unique_ptr object that owns a particular resource is destroyed, the resource is freed. A unique_ptr object may be moved, but not copied; for more information, see Rvalue Reference Declarator: &&.

http://ootips.org/yonat/4dev/smart-pointers.html


without smart pointer
---------------------

    void foo()
    {
        MyClass* p(new MyClass);
        p->DoSomething();
        delete p;
    }


with smart pointer
------------------

    void foo()
    {
        auto_ptr<MyClass> p(new MyClass);
        p->DoSomething();
    }

dangling pointer after moving
-----------------------------

    MyClass* p(new MyClass);
    MyClass* q = p;
    delete p;
    p->DoSomething();   // Watch out! p is now dangling!
    p = NULL;           // p is no longer dangling
    q->DoSomething();   // Ouch! q is still dangling!

fix dangling pointer using auto_ptr overloading = 
-------------------------------------------------
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
