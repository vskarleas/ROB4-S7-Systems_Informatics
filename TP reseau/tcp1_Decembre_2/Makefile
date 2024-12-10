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
CC = gcc

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
EXECUTABLES = client server client_LEGACY voting_client voting_server voting_client_2 voting_server_2


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


########################################################
# regles explicites de creation des executables

client : client.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Edition de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) -o $@ $^ $(LDOPTS)

server : server.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Edition de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) -o $@ $^ $(LDOPTS)

client_LEGACY : client_LEGACY.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Edition de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) -o $@ $^ $(LDOPTS)

voting_client : voting_client.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Edition de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) -o $@ $^ $(LDOPTS)

voting_server : voting_server.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Edition de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) -o $@ $^ $(LDOPTS)

voting_client_2 : voting_client_2.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Edition de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) -o $@ $^ $(LDOPTS)

voting_server_2 : voting_server_2.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Edition de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) -o $@ $^ $(LDOPTS)

# regle pour "nettoyer" le r�pertoire
clean:
	rm -fR $(EXECUTABLES) *.o 
