#include <stdlib.h>
#include <stdio.h>
#include <ffi.h>
#include <dlfcn.h>
#include "foo.h"

int main()
{
  // Function definition
  ffi_cif cif;
  ffi_type *args[3];
  void *values[3];

  // Arguments
  int arg1;
  char *arg2;
  struct bar arg3;

  // Return value
  int res;

  // Custom type definition
  ffi_type bar_type;
  ffi_type *bar_type_elements[3];

  bar_type.size = bar_type.alignment = 0;
  bar_type.elements = &bar_type_elements;
  bar_type.type = FFI_TYPE_STRUCT;

  bar_type_elements[0] = &ffi_type_sint;
  bar_type_elements[1] = &ffi_type_sint;
  bar_type_elements[2] = NULL;

  // Getting pointer to a called function
  char *name = "foo";
  void *handler = dlopen(NULL, RTLD_LAZY);
  if (!handler)
  {
    fprintf(stderr, "dlopen failed: %s\n", dlerror());
    exit(EXIT_FAILURE);
  }
  void *ptr = dlsym(handler, name);
  dlclose(handler);
  
  // Arguments initialization
  values[0] = &arg1;
  args[0] = &ffi_type_sint;
  values[1] = &arg2;
  args[1] = &ffi_type_pointer;
  values[2] = &arg3;
  args[2] = &bar_type;
  
  // Calling :)
  if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 3, &ffi_type_sint, args) == FFI_OK)
    {
      arg1 = 21;
      arg2 = "Uh, Oh";
      arg3.x = 14;
      arg3.y = 88;

      ffi_call(&cif, ptr, &res, values);

      printf("And the dead beef is %d\n", res);
    }

  return 0;
}
