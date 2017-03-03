class
-----
 . class member function can be accessed without object if it's static
 
 . enum variable can be accessed by class and object both
 
 . main should return "int" type 

string
------
 . string class size()

 . string class c_str()    (or data() for C++11)

 . std::to_str(int/long/float/...);    // requires -std=c++11

    int main ()
    {
      int fd;
      /*
        std::string pi = "pi is " + std::to_string(3.1415926);
        std::cout << pi << '\n';
      */
      fd = open("to_string.txt", O_CREAT | O_RDWR, 0767);
      for(int i=0; i<100 ; i++) {
        write(fd, std::to_string(i).c_str(), std::to_string(i).size());
        write(fd, "\n", 1);
      }
      close(fd);
      return 0;
    }


pointer
-------              
 . pointer to char in C++
 
     void *memcpy( void * destination, const void * source, size_t num );
       cout << (char *)XX                                   <print content @XX>
       cout << static_cast<char*>XX or printf("%p", XX);   <print content of XX>

  

class - constructor
-----------              
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
