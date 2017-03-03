    size_t   strlen(char *)                             // size_t : unsigned integer
    
    unsigned long strtoul(char *, char **, int base)         ex) base = 10        // 10 base #    
    int sprintf(char *str, const char *format, ...);    
    int snprintf(char *str, size_t size, const char *format, ...);  // buffer 'size' to store string

    char *   strtok(char *str, const char *delimeter);  ex) *delimeter = " ,.-;"
      ;if str != null, strtok starts searching from the beginning. 
      ;if str == null, strtok continues searching with the previous string.
