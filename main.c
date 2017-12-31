#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct TEmployee {
  struct TEmployee         * m_Next;
  struct TEmployee         * m_Bak;
  char                     * m_Name;
} TEMPLOYEE;

#endif /* __PROGTEST__ */

TEMPLOYEE        * newEmployee  ( const char      * name,
                                  TEMPLOYEE       * m_Next ) {
  TEMPLOYEE * l;
  char * new_name;

  if ( name == NULL ) {
    new_name = NULL;
  }
  else {
    new_name = (char*) malloc ( 100 * sizeof ( *new_name ) );
    strcpy(new_name, name);
  }

  l = (TEMPLOYEE*) malloc ( sizeof ( *l ) );
  l -> m_Next = m_Next;
  l -> m_Bak  = NULL;
  l -> m_Name = new_name;

  return l;
}
TEMPLOYEE        * cloneList    ( TEMPLOYEE       * src ) {
  if ( src == NULL ) return NULL;

  TEMPLOYEE * copy, * tmp, * tmp2;
  tmp = src;
  //* to copy a linked list with arbitary pointers
  //* we chose the method explained here: http://techieme.in/cloning-linked-list-having-next-and-random-pointer/
  while ( tmp != NULL ) {       //* while list isnt at the end ..
    TEMPLOYEE * newnode;
    newnode = newEmployee ( tmp -> m_Name, tmp -> m_Next );   //* create a copy of the node, pointing to the next original node
    tmp -> m_Next = newnode;    //* point the original node to the copy
    tmp = tmp -> m_Next -> m_Next; //* jump to the next original node ( since a copy is now the next node, jump twice )
  }

  tmp = src;

  while ( tmp != NULL ) {
    if ( tmp -> m_Bak == NULL )    //* m_Bak is an arbitary pointer
      tmp -> m_Next -> m_Bak = NULL;
    else
      tmp -> m_Next -> m_Bak = tmp -> m_Bak -> m_Next;   //* copy the arbitary pointer
    tmp = tmp -> m_Next -> m_Next;  //* jump
  }

  tmp = src;
  copy = tmp -> m_Next;

  //* simply seperate the two lists
  while ( tmp != NULL ) {
    tmp2 = tmp -> m_Next;
    if ( tmp -> m_Next != NULL )
      tmp -> m_Next = tmp->m_Next->m_Next;
    if ( tmp2 -> m_Next != NULL )
      tmp2 -> m_Next = tmp2 -> m_Next -> m_Next;
    tmp = tmp -> m_Next;
  }
  return copy;
}



void               freeList     ( TEMPLOYEE       * src )
{
  TEMPLOYEE * tmp;

  while ( src != NULL )
  {
    tmp = src;
    src = src -> m_Next;
    free(tmp -> m_Name);
    tmp -> m_Bak = NULL;
    free ( tmp );
  }
}

#ifndef __PROGTEST__
int                main         ( int               argc,
                                  char            * argv [] ) {
  TEMPLOYEE * a, *b;
  char tmp[100];
  assert ( sizeof ( TEMPLOYEE ) == 3 * sizeof ( void * ) );

  a = NULL;
  b = cloneList ( a );

  freeList(a);



  b = cloneList ( newEmployee ( NULL, NULL ) );

  freeList(a);

  a = NULL;
  a = newEmployee ( "Peter", a );
  a = newEmployee ( "John", a );
  a = newEmployee ( "Joe", a );
  a = newEmployee ( "Maria", a );
  b = cloneList ( a );
  printf("%s\n", b -> m_Next -> m_Name);
  assert(a == NULL && b && b->m_Name == NULL);




  a -> m_Bak = a -> m_Next;
  a -> m_Next -> m_Next -> m_Bak = a -> m_Next -> m_Next -> m_Next;
  a -> m_Next -> m_Next -> m_Next -> m_Bak = a -> m_Next;

  assert ( a
           && ! strcmp ( a -> m_Name, "Maria" )
           && a -> m_Bak == a -> m_Next );
  assert ( a -> m_Next
           && ! strcmp ( a -> m_Next -> m_Name, "Joe" )
           && a -> m_Next -> m_Bak == NULL );
  assert ( a -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Name, "John" )
           && a -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next -> m_Next );
  assert ( a -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
           && a -> m_Next -> m_Next -> m_Next -> m_Bak == a -> m_Next );
  assert ( a -> m_Next -> m_Next -> m_Next -> m_Next == NULL );

  b = cloneList ( a );
  strncpy ( tmp, "Moe", sizeof ( tmp ) );
  a = newEmployee ( tmp, a );
  strncpy ( tmp, "Victoria", sizeof ( tmp ) );
  a = newEmployee ( tmp, a );
  strncpy ( tmp, "Peter", sizeof ( tmp ) );
  a = newEmployee ( tmp, a );
  if (b -> m_Next -> m_Next -> m_Bak == b -> m_Next -> m_Next -> m_Next)
    printf("%s\n", b -> m_Next -> m_Next -> m_Name);
  b -> m_Next -> m_Next -> m_Next -> m_Bak = b -> m_Next -> m_Next;
  assert ( a
           && ! strcmp ( a -> m_Name, "Peter" )
           && a -> m_Bak == NULL );

  assert ( a -> m_Next
           && ! strcmp ( a -> m_Next -> m_Name, "Victoria" )
           && a -> m_Next -> m_Bak == NULL );
  assert ( a -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Name, "Moe" )
           && a -> m_Next -> m_Next -> m_Bak == NULL );
  assert ( a -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Name, "Maria" )
           && a -> m_Next -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next -> m_Next -> m_Next );
  assert ( a -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Joe" )
           && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Bak == NULL );
  assert ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "John" )
           && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next );
  assert ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
           && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next -> m_Next -> m_Next );
  assert ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  assert ( b
           && ! strcmp ( b -> m_Name, "Maria" )
           && b -> m_Bak == b -> m_Next );
  assert ( b -> m_Next
           && ! strcmp ( b -> m_Next -> m_Name, "Joe" )
           && b -> m_Next -> m_Bak == NULL );
  assert ( b -> m_Next -> m_Next
           && ! strcmp ( b -> m_Next -> m_Next -> m_Name, "John" )
           && b -> m_Next -> m_Next -> m_Bak == b -> m_Next -> m_Next -> m_Next );
  assert ( b -> m_Next -> m_Next -> m_Next
           && ! strcmp ( b -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
           && b -> m_Next -> m_Next -> m_Next -> m_Bak == b -> m_Next -> m_Next );
  assert ( b -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  freeList ( a );
  b -> m_Next -> m_Bak = b -> m_Next;
  a = cloneList ( b );
  assert ( a
           && ! strcmp ( a -> m_Name, "Maria" )
           && a -> m_Bak == a -> m_Next );
  assert ( a -> m_Next
           && ! strcmp ( a -> m_Next -> m_Name, "Joe" )
           && a -> m_Next -> m_Bak == a -> m_Next );
  assert ( a -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Name, "John" )
           && a -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next -> m_Next );
  assert ( a -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
           && a -> m_Next -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next );
  assert ( a -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  assert ( b
           && ! strcmp ( b -> m_Name, "Maria" )
           && b -> m_Bak == b -> m_Next );
  assert ( b -> m_Next
           && ! strcmp ( b -> m_Next -> m_Name, "Joe" )
           && b -> m_Next -> m_Bak == b -> m_Next );
  assert ( b -> m_Next -> m_Next
           && ! strcmp ( b -> m_Next -> m_Next -> m_Name, "John" )
           && b -> m_Next -> m_Next -> m_Bak == b -> m_Next -> m_Next -> m_Next );
  assert ( b -> m_Next -> m_Next -> m_Next
           && ! strcmp ( b -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
           && b -> m_Next -> m_Next -> m_Next -> m_Bak == b -> m_Next -> m_Next );
  assert ( b -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  freeList ( b );
  freeList ( a );


  return 0;
}
#endif /* __PROGTEST__ */
