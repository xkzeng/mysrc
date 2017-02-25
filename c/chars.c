
const char chrtbl[] =
{
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
  'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 
  'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 
  'u', 'v', 'w', 'x', 'y', 'z', 
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 
  'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 
  'U', 'V', 'W', 'X', 'Y', 'Z', 
  '+', '-', '/', '*', ',', '.', '<', '>', ';', ':', 
  '"', '[', ']', '{', '}', '(', ')', '_', '=', '`', 
  '~', '!', '@', '#', '$', '%', '^', '&', '|', '?',
  0
};

struct object
{
  struct object* this;
  void* member1;
  void* member2;
  void* member3;
  int (*op1)(struct object* this, void* arg);
  int (*op2)(struct object* this, void* arg);
  int (*op3)(struct object* this, void* arg);
};
