

  int memset( void *addr, int, size_t );

    char data[256];
    for(int i=0; i<4096/256; i++) {
      memset(data, 'A'+i, 256);
      pos_w = write(fd, data, 256);
    }




  void *memcpy( void * destination, const void * source, size_t num );    
    ; return destination


    /* memcpy example */
    #include <stdio.h>
    #include <string.h>

    struct p {
      char name[40];
      int age;
    }; 

    struct p person, person_copy;

    int main ()
    {
      char myname[] = "Pierre de Fermat";

      /* using memcpy to copy string: */
      memcpy ( person.name, myname, strlen(myname)+1 );
      person.age = 46;

      /* using memcpy to copy structure: */
      memcpy ( &person_copy, &person, sizeof(person) );

      printf ("person_copy: %s, %d \n", person_copy.name, person_copy.age );

      return 0;
    }
