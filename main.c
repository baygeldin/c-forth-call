int main()
{
  // Number of parameters of the called function
  int argc = 3;

  // Pointer to the called function
  int ptr = 0x00000000004005c0;

  // Example parameters
  int p1 = 21;
  char p2 = 'A';
  double p3 = 3.14;

  // Casting to arguments
  int *arg1 = *(int*)&p1;
  int *arg2 = *(int*)&p2;
  int *arg3 = *(int*)&p3;

  // Mocks
  int *arg4 = 1;

  if (argc == 1)
  {
    ((void(*)(void*))ptr)(arg1);
  } else if (argc == 2) {
    ((void(*)(void*, void*))ptr)(arg1, arg2);
  } else if (argc == 3) {
    ((void(*)(void*, void*, void*))ptr)(arg1, arg2, arg3);
  } else {
    ((void(*)(void*, void*, void*, void*))ptr)(arg1, arg2, arg3, arg4);
  }

  return 0;
}
