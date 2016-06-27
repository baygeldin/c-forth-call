NAME = app
MAIN = main
GLUE = glue
PFORTH_SRC = pforth/csrc
PFORTH_LIB = pforth/build/unix
PFORTH_BIN = pf_cglue pf_clib pf_core \
						 pf_inner pf_io pf_io_none \
						 pf_mem pf_save pf_text \
						 pf_words pfcompil pf_io_posix

all: pforth.o $(GLUE).o $(MAIN).o
	$(CC) -o $(NAME) $? -rdynamic -lffi -ldl -lm

$(MAIN).o: $(MAIN).c
	$(CC) -c -o $@ $< -I$(PFORTH_SRC)

$(GLUE).o: $(GLUE).c
	$(CC) -c -o $@ $< -I$(PFORTH_SRC)

pforth.o: $(PFORTH_BIN:%=$(PFORTH_LIB)/%.eo)
	$(MAKE) -C $(PFORTH_LIB)
	$(LD) -r -o $@ $?

clean:
	rm -f *.o

