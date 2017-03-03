
    int open(const char *, int oflag [, mode_t mode]);  // open("a.txt", O_CREAT, 0644);
      O_CLOEXEC  
      O_EXCL  
      766 -> 764 
 
    int fstat(int, struct stat *);    cf) int stat(char *, struct stat *);
    
    ftruncate(int, offt_t);
    
    close

    ssize_t read(int fd, void *buf, size_t count);
    
    ssize_t write(int fd, const void *buf, size_t count);
      ;file pointer advances by return value(written/read bytes)
      
    off_t lseek(int fd, off_t offset, int whence);
      ;can adjust the offset
