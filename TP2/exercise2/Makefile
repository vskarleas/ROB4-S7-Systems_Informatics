EXEC = question2 
CFLAGS = -Wall -ggdb3

all: $(EXEC)


question2: image.h image.c transf_image.h transf_image.c bruitage.c 
	gcc $(CFLAGS) -o question2 image.c transf_image.c bruitage.c

clean:
	rm -f *.o *~ *.backup

vclean:	clean
	rm -f $(EXEC)
