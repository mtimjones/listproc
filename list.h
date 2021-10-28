// list.h

struct node_s;

struct node_s
{
   int type;
   struct node_s *left;
   struct node_s *right;
   char value;
};

#define TYPE_LIST    0
#define TYPE_ATOM    1

