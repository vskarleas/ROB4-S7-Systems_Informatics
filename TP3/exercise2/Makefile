#############################################################################
# Fichier Makefile 
# UE Informatique Systeme - Polytech Sorbonne - 2024/2025
#############################################################################
#############################################################################
# This version of make file includes tests for all the previous Taches
#############################################################################
# utilisation des variables internes $@ $< $^ $*
# $@ : correspond au nom de la cible
# $< : correspond au nom de la premiere dependance
# $^ : correspond � toutes les d�pendances
# $* : correspond au nom du fichier sans extension 
#       (dans les regles generiques uniquement)
#############################################################################
# information sur la regle executee avec la commande @echo
# (une commande commancant par @ n'est pas affichee a l'ecran)
#############################################################################


#############################################################################
# definition des variables locales
#############################################################################

# compilateur C
CC = clang

# chemin d'acces aux librairies (interfaces)
INCDIR = .

# chemin d'acces aux librairies (binaires)
LIBDIR = .

# options pour l'�dition des liens
LDOPTS = -L$(LIBDIR) -lm

# options pour la recherche des fichiers .o et .h
INCLUDEOPTS = -I$(INCDIR)

# options de compilation
COMPILOPTS = -g -Wall $(INCLUDEOPTS)

# liste des executables
EXECUTABLES = print_data tga2ppm tga2ppm_v2


#############################################################################
# definition des regles
#############################################################################

########################################################
# la r�gle par d�faut
all : $(EXECUTABLES)

########################################################
# regle generique : 
#  remplace les regles de compilation separee de la forme
#	module.o : module.c module.h
#		$(CC) -c $(COMPILOPTS) module.c
%.o : %.c %.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

########################################################
# regles explicites de compilation separee de modules
# n'ayant pas de fichier .h ET/OU dependant d'autres modules

img.o : img.c img.h binary.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

print_data.o : print_data.c img.h binary.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

binary.o : binary.c binary.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

to_ppm_image.o : to_ppm_image.c img.h binary.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

to_ppm_image_v2.o : to_ppm_image_v2.c img.h binary.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

########################################################
# regles explicites de creation des executables

print_data : print_data.o img.o binary.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Edition de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) -o $@ $^ $(LDOPTS)

tga2ppm : to_ppm_image.o img.o binary.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Edition de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) -o $@ $^ $(LDOPTS)

tga2ppm_v2 : to_ppm_image_v2.o img.o binary.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Edition de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) -o $@ $^ $(LDOPTS)



# regle pour "nettoyer" le r�pertoire
clean:
	rm -fR $(EXECUTABLES) *.o 
