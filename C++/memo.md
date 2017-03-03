 . class member function can be accessed without object if it's static
 
 . enum variable can be accessed by class and object both
 
 . main should return "int" type 

  
 . string class size()
 . string class c_str()    (or data() for C++11)
  
  
 . pointer to char in C++
 
     void *memcpy( void * destination, const void * source, size_t num );
       cout << (char *)XX                                   <print content @XX>
       cout << static_cast<char*>XX or printf("%p", XX);   <print content of XX>

  

 
 . initialization in constructor
 
    class VmFile {
  
      private:

       int fd_;
       string filename_;
       uint64_t filesize_;

       pthread_rwlock_t rwlock_;

      public:
       /* 
       VmFile(string filename) { 
         filename_ = filename;
         filesize_ = 0;
         fd_ = -1;
         pthread_rwlock_init(&rwlock_, NULL);
       }
       */
       VmFile(string filename) : filename_(filename), filesize_(0), fd_(-1) {
         pthread_rwlock_init(&rwlock_, NULL);
       }
