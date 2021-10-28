// list.c

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

char *input={"( ( a ( x y ) ) ( ( 1 2 ) a ) )"};
int idx = 0;

char GetNextValue( void )
{
   int  skipping = 1;
   char value;

   while (skipping)
   {
      switch( input[idx++] )
      {
         case '(':
            value = '(';
            skipping = 0;
            break;
         case ')':
            value = ')';
            skipping = 0;
            break;
         case ' ':
            break;
         default:
            // Assume atom.
            value = input[idx-1];
            skipping = 0;
            break;
      }
   }

   return value;
}

struct node_s *parse_atom( char value )
{
   struct node_s *node = (struct node_s *) calloc( 1, sizeof( struct node_s ) );

   node->type = TYPE_ATOM;
   node->value = value;

   return node;
}

struct node_s *parse_list( void )
{
   struct node_s *node = (struct node_s *) calloc( 1, sizeof( struct node_s ) );
   char value;

   node->type = TYPE_LIST;

   value = GetNextValue();

   if ( value == '(' )
   {
      node->left = parse_list();
   }
   else if ( value == ')' )
   {
      // Empty
   }
   else
   {
      node->left = parse_atom( value );
   }

   value = GetNextValue();

   if ( value == '(' )
   {
      node->right = parse_list();
   }
   else if ( value == ')' )
   {
      // Empty
   }
   else
   {
      node->right = parse_atom( value );
   }

   // Consume the ')'
   value = GetNextValue();

   return node;
}

void print_list( struct node_s *node )
{
   printf("( ");

   if ( node->left )
   {
      if ( node->left->type == TYPE_LIST )
      {
         print_list( node->left );
      }
      else
      {
         printf("%c ", node->left->value );
      }
   }

   if ( node->right )
   {
      if ( node->right->type == TYPE_LIST )
      {
         print_list( node->right );
      }
      else
      {
         printf("%c ", node->right->value );
      }
   }

   printf(") ");

   return;
}

void main()
{
   struct node_s *node;

   if ( GetNextValue() == '(' )
   {
      node = parse_list();
   }
   else
   {
      printf("bad expression.");
   }

   print_list( node );

   printf("\n");

   return;
}
