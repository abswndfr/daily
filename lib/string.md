string size
----------------
    size_t   strlen(char *)                             // size_t : unsigned integer


parsing string into token
-------------------------
    char *   strtok(char *str, const char *delimeter);  ex) *delimeter = " ,.-;"
      ;if str != null, strtok starts searching from the beginning. 
      ;if str == null, strtok continues searching with the previous string.


string to number
----------------
    unsigned long strtoul(char *, char **, int base)         ex) base = 10        // 10 base #    


number to string
----------------
    int sprintf(char *str, const char *format, ...);    
    int snprintf(char *str, size_t size, const char *format, ...);  // buffer 'size' to store string


    int main ()
    {
      int fd, len;
      char buf[100];

      fd = open("sprintf.txt", O_CREAT | O_RDWR, 0767);
      for(int i=0; i<100 ; i++) {
        len = sprintf(buf, "%d\n", i);
        write(fd, buf, len);
      }
      close(fd);
      return 0;
    }
