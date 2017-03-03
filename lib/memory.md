

    int memset( void *addr, int, size_t );
 
    void *memcpy( void * destination, const void * source, size_t num );    
      ; return destination

ex>

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
