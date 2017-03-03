open
----

    int open(const char *, int oflag [, mode_t mode]);  // open("a.txt", O_CREAT, 0644);
      O_CLOEXEC  
      O_EXCL  
      766 -> 764 


stat
----

    int fstat(int, struct stat *);    cf) int stat(char *, struct stat *);


    struct stat buf;
    if(fstat(fd, &buf) == 0) {  // get file stat
      stat_dump(FLAGS_name.c_str(), &buf);    
      ftruncate(fd, (off_t)ul)  // change size 
    } 

    void stat_dump(const char *name, struct stat *buf)
    {
      std::cout <<  "--- : " << name << std::endl;
      std::cout <<  " ID of device containing file : " << buf->st_dev << std::endl;
      std::cout <<  " inode number                 : " << buf->st_ino << std::endl;
      std::cout <<  " file type and mode           : " << buf->st_mode << std::endl;
      std::cout <<  " number of hard links         : " << buf->st_nlink << std::endl;
      std::cout <<  " user ID of owner             : " << buf->st_uid << std::endl;
      std::cout <<  " group ID of owner            : " << buf->st_gid << std::endl;
      std::cout <<  " device ID (if special file)  : " << buf->st_rdev << std::endl;
      std::cout <<  " total size, in bytes         : " << buf->st_size << std::endl;
      std::cout <<  " blocksize for filesystem I/O : " << buf->st_blksize << std::endl;
      std::cout <<  " number of blocks allocated   : " << buf->st_blocks << std::endl;
      std::cout <<  " time of last access          : " << buf->st_atim.tv_sec << std::endl;
      std::cout <<  " time of last modification    : " << buf->st_mtim.tv_sec << std::endl;
      std::cout <<  " time of last status change   : " << buf->st_ctim.tv_sec << std::endl;
    }



truncate
----

    ftruncate(int, offt_t);
    

close
----

    close


read
----

    ssize_t read(int fd, void *buf, size_t count);
    
    for(int i=0; i<block_count; i++) {
      read(fd, data, block_size);     
      std::cout << data << std::endl; 
    }

write
-----

    ssize_t write(int fd, const void *buf, size_t count);
      ;file pointer advances by return value(written/read bytes)
     
     
    for(int i=0; i<ul; i++) 
    {
      len = sprintf(data, "%d\n", i);
      write(fd, data, len);
    }


l_seek
------

    off_t lseek(int fd, off_t offset, int whence);
      ;can adjust the offset
