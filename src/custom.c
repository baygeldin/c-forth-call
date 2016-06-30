#include "../pforth/csrc/pf_all.h"
#include <ffi.h>
#include <dlfcn.h>
#include <stdlib.h>

void *handler;

static cell_t CCall(cell_t count, cell_t func) {
  int res;
  int i;
  ffi_cif cif;
  ffi_type **args = (ffi_type**)malloc(count * sizeof(*args));
  void **values = (void**)malloc(count * sizeof(void*));

  /* Example with custom structure!
   * Forth has structures too, so it's a good idea to map them somehow.
   *
   * struct bar arg3;
   * ffi_type bar_type;
   * ffi_type *bar_type_elements[count];
   * bar_type.size = bar_type.alignment = 0;
   * bar_type.elements = bar_type_elements;
   * bar_type.type = FFI_TYPE_STRUCT;
   * bar_type_elements[0] = &ffi_type_sint;
   * bar_type_elements[1] = &ffi_type_sint;
   * bar_type_elements[2] = NULL;
   * */

  char name[255];
  ForthStringToC(name, (char *)func, sizeof(name));
  void *ptr = dlsym(handler, name);

  int params[50];

  for (i=0; i < count; i++) {
    params[i] = (int)POP_DATA_STACK;
    values[i] = &params[i];
    args[i] = &ffi_type_sint;
  }

  if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, count, &ffi_type_sint, args) == FFI_OK) {
    ffi_call(&cif, ptr, &res, values);
  }

  return res;
}

#ifdef PF_NO_GLOBAL_INIT

/* If your loader does not support global initialization, then you
 must define PF_NO_GLOBAL_INIT and provide a function to fill
 the table. Some embedded system loaders require this! */

#define NUM_CUSTOM_FUNCTIONS (1)
CFunc0 CustomFunctionTable[NUM_CUSTOM_FUNCTIONS];

Err LoadCustomFunctionTable(void) {
    CustomFunctionTable[0] = CCall;
    return 0;
}

#else

/* If your loader supports global initialization (most do) then
 just create the table like this. */

CFunc0 CustomFunctionTable[] ={
    (CFunc0) CCall,
};

#endif

Err CompileCustomFunctions(void) {
    Err err;
    int i = 0;
    handler = dlopen(NULL, RTLD_LAZY);
    if (!handler)
    {
      fprintf(stderr, "dlopen failed: %s\n", dlerror());
      exit(EXIT_FAILURE);
    }
    /* TODO: We also need dclose(handler) somewhere. */
    err = CreateGlueToC("CCALL", i++, C_RETURNS_VALUE, 2);
    if( err < 0 ) return err;

    return 0;
}

