cmake_minimum_required(VERSION 3.4)

project(libforth)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")

set(PFORTH_BIN "pforth/build/unix")
set(PFORTH_LIB "pforth/csrc")

set(SOURCES
  pf_cglue pf_clib pf_core pf_inner pf_io pf_io_none
  pf_mem pf_save pf_text pf_words pfcompil pf_io_posix
  ../../../src/custom)
string(REGEX REPLACE "([^;]+)" "\\1.c" PFSOURCE "${SOURCES}")
string(REGEX REPLACE "([^;]+)" "${PFORTH_BIN}/\\1.eo.o" PFOBJ "${SOURCES}")

add_custom_command(
  OUTPUT ${PFOBJ}
  # Monkey patch for pforth Makefile. Sort of.
  COMMAND make EMBCCOPTS='-DPF_STATIC_DIC -fPIC' PFSOURCE='pf_cglue.c pf_clib.c pf_core.c pf_inner.c pf_io.c pf_io_none.c pf_main.c pf_mem.c pf_save.c pf_text.c pf_words.c pfcompil.c pf_io_posix.c ../../../src/custom.c' -e#${PFSOURCE} -e
  # FUCK. FUCK THE ESCAPING.
  COMMAND find . ../../../src -name '*.eo' -exec sh -c 'mv \"$$1\" \"$$\{1%.eo\}.eo.o\"' _ {} \\\;
  WORKING_DIRECTORY ${PFORTH_BIN})
add_custom_target(pforth
  DEPENDS ${PFOBJ})

add_library(forth SHARED ${PFOBJ})
add_dependencies(forth pforth)
target_link_libraries(forth ffi dl m)
set_target_properties(forth PROPERTIES
  LINKER_LANGUAGE C
  EXTERNAL_OBJECT TRUE
  GENERATED TRUE)

install(TARGETS forth DESTINATION lib)
install(FILES ${PFORTH_LIB}/pforth.h DESTINATION include)

add_executable(main examples/main.c)
target_link_libraries(main forth)
set_target_properties(main PROPERTIES
  EXCLUDE_FROM_ALL TRUE
  COMPILE_FLAGS "-rdynamic")

