cmake_minimum_required(VERSION 3.4)

project(libforth)
set(CMAKE_BUILD_TYPE Release)

set(PFORTH_BIN "pforth/build/unix")
set(PFORTH_LIB "pforth/csrc")

set(PFORTH_OBJ
  pf_cglue pf_clib pf_core pf_inner pf_io pf_io_none
  pf_mem pf_save pf_text pf_words pfcompil pf_io_posix)
string(REGEX REPLACE "([^;]+)" "${PFORTH_BIN}/\\1.eo.o" SOURCES "${PFORTH_OBJ}")

add_custom_command(
  OUTPUT ${SOURCES}
  # Monkey patch for pforth Makefile. Sort of.
  COMMAND make EMBCCOPTS='-DPF_STATIC_DIC -fPIC' -e
  # FUCK. FUCK THE ESCAPING.
  COMMAND find . -name '*.eo' -exec sh -c 'mv \"$$1\" \"$$\{1%.eo\}.eo.o\"' _ {} \\\;
  WORKING_DIRECTORY ${PFORTH_BIN})

add_custom_target(pforth
  DEPENDS ${SOURCES})

add_library(forth SHARED ${SOURCES} src/custom.c)
add_dependencies(forth pforth)
target_link_libraries(forth ffi dl m)

install(TARGETS forth DESTINATION lib)
install(FILES ${PFORTH_LIB}/pforth.h DESTINATION include)

