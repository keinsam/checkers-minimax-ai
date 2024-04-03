CPP = g++ -std=c++11 -Wall
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system

TESTDIR = tests
BUILDDIR = bin
SRCDIR = src
MODDIR = src/Modele
ELEMDIR = src/Modele/Elements
UTILSDIR = src/utils

# commande make all
all: $(BUILDDIR)/test_help
	./$<

# commande make test_i
test: $(BUILDDIR)/test
	./$<
test_incognito: $(BUILDDIR)/test_incognito
	./$<
test_dames: $(BUILDDIR)/test_dames
	./$<
test_safari: $(BUILDDIR)/test_safari
	./$<






# fichiers excutables
$(BUILDDIR)/test_help: $(BUILDDIR)/TestHelp.o
	$(CPP) -o $@ $^ $(LDLIBS)

$(BUILDDIR)/test: $(BUILDDIR)/Test.o $(BUILDDIR)/Screen.o $(BUILDDIR)/Controlleur.o \
                   $(BUILDDIR)/Info_Joueur.o $(BUILDDIR)/Info_Joueur_I.o $(BUILDDIR)/Info_Joueur_S.o \
				   $(BUILDDIR)/Jeu.o $(BUILDDIR)/JeuI.o $(BUILDDIR)/JeuD.o $(BUILDDIR)/JeuS.o \
                   $(BUILDDIR)/JeuI.o $(BUILDDIR)/JeuS.o $(BUILDDIR)/utils.o $(BUILDDIR)/Case.o $(BUILDDIR)/Emplacement.o \
				   $(BUILDDIR)/PionI.o $(BUILDDIR)/PionD.o $(BUILDDIR)/PionS.o $(BUILDDIR)/Capture.o \
				   $(BUILDDIR)/Joueur.o
	$(CPP) -o $@ $^ $(LDLIBS)

$(BUILDDIR)/test_incognito: $(BUILDDIR)/PionI.o $(BUILDDIR)/Case.o $(BUILDDIR)/Joueur.o $(BUILDDIR)/Jeu.o $(BUILDDIR)/JeuI.o $(BUILDDIR)/utils.o $(BUILDDIR)/Info_Joueur_I.o $(BUILDDIR)/TestI.o
	$(CPP) -o $@ $^ $(LDLIBS)

$(BUILDDIR)/test_dames: $(BUILDDIR)/PionD.o $(BUILDDIR)/Case.o $(BUILDDIR)/Capture.o $(BUILDDIR)/Joueur.o $(BUILDDIR)/Jeu.o $(BUILDDIR)/JeuD.o $(BUILDDIR)/utils.o $(BUILDDIR)/TestD.o
	$(CPP) -o $@ $^ $(LDLIBS)

$(BUILDDIR)/test_safari: $(BUILDDIR)/PionS.o $(BUILDDIR)/Case.o $(BUILDDIR)/Emplacement.o $(BUILDDIR)/Joueur.o $(BUILDDIR)/Jeu.o $(BUILDDIR)/JeuS.o $(BUILDDIR)/utils.o $(BUILDDIR)/Info_Joueur_S.o $(BUILDDIR)/TestS.o
	$(CPP) -o $@ $^ $(LDLIBS)






# fichiers objets des utils
$(BUILDDIR)/utils.o: $(UTILSDIR)/utils.cpp $(UTILSDIR)/utils.hpp 
	$(CPP) -c $< -o $@

$(BUILDDIR)/Jeu_name.o: $(UTILSDIR)/Jeu_name.hpp 
	$(CPP) -c $< -o $@

$(BUILDDIR)/Info_Joueur.o: $(UTILSDIR)/Info_Joueur.cpp $(UTILSDIR)/Couleurs.hpp $(UTILSDIR)/Animal.hpp $(UTILSDIR)/Info_Joueur.hpp
	$(CPP) -c $< -o $@

$(BUILDDIR)/Info_Joueur_I.o: $(UTILSDIR)/Info_Joueur_I.cpp $(UTILSDIR)/Couleurs.hpp $(UTILSDIR)/Animal.hpp $(UTILSDIR)/Info_Joueur.hpp
	$(CPP) -c $< -o $@

$(BUILDDIR)/Info_Joueur_S.o: $(UTILSDIR)/Info_Joueur_S.cpp $(UTILSDIR)/Couleurs.hpp $(UTILSDIR)/Animal.hpp $(UTILSDIR)/Info_Joueur.hpp
	$(CPP) -c $< -o $@




# fichiers objets des éléments
$(BUILDDIR)/Pion.o: $(ELEMDIR)/Pion.hpp
	$(CPP) -c $< -o $@

$(BUILDDIR)/PionI.o: $(ELEMDIR)/PionI.cpp $(ELEMDIR)/Pion.hpp $(ELEMDIR)/PionI.hpp $(UTILSDIR)/Couleurs.hpp
	$(CPP) -c $< -o $@

$(BUILDDIR)/PionD.o: $(ELEMDIR)/PionD.cpp $(ELEMDIR)/Pion.hpp $(ELEMDIR)/PionD.hpp $(UTILSDIR)/Couleurs.hpp
	$(CPP) -c $< -o $@

$(BUILDDIR)/PionS.o: $(ELEMDIR)/PionS.cpp $(ELEMDIR)/Pion.hpp $(ELEMDIR)/PionS.hpp
	$(CPP) -c $< -o $@

$(BUILDDIR)/Case.o: $(ELEMDIR)/Case.cpp $(ELEMDIR)/Pion.hpp $(ELEMDIR)/Case.hpp $(UTILSDIR)/Couleurs.hpp
	$(CPP) -c $< -o $@

$(BUILDDIR)/Capture.o: $(ELEMDIR)/Capture.cpp $(ELEMDIR)/PionD.hpp $(ELEMDIR)/Case.hpp $(ELEMDIR)/Capture.hpp
	$(CPP) -c $< -o $@

$(BUILDDIR)/Emplacement.o: $(ELEMDIR)/Emplacement.cpp $(ELEMDIR)/Emplacement.hpp
	$(CPP) -c $< -o $@




# fichiers objets des classes du modèle
$(BUILDDIR)/Joueur.o: $(MODDIR)/Joueur.cpp $(ELEMDIR)/Case.hpp $(ELEMDIR)/Pion.hpp
	$(CPP) -c $< -o $@

$(BUILDDIR)/Jeu.o: $(MODDIR)/Jeu.cpp $(MODDIR)/JeuI.hpp $(MODDIR)/JeuD.hpp $(MODDIR)/JeuS.hpp $(ELEMDIR)/Case.hpp $(UTILSDIR)/Info_Joueur.hpp $(UTILSDIR)/Jeu_name.hpp
	$(CPP) -c $< -o $@

$(BUILDDIR)/JeuI.o: $(MODDIR)/JeuI.cpp $(MODDIR)/Jeu.hpp $(MODDIR)/JeuI.hpp $(ELEMDIR)/Case.hpp $(UTILSDIR)/utils.hpp $(UTILSDIR)/Info_Joueur_I.hpp
	$(CPP) -c $< -o $@

$(BUILDDIR)/JeuD.o: $(MODDIR)/JeuD.cpp $(MODDIR)/Jeu.hpp $(MODDIR)/JeuD.hpp $(ELEMDIR)/Case.hpp $(ELEMDIR)/Capture.hpp
	$(CPP) -c $< -o $@

$(BUILDDIR)/JeuS.o: $(MODDIR)/JeuS.cpp $(MODDIR)/Jeu.hpp $(MODDIR)/JeuS.hpp $(ELEMDIR)/Case.hpp $(ELEMDIR)/Emplacement.hpp $(UTILSDIR)/utils.hpp
	$(CPP) -c $< -o $@




# fichiers objets des classes du controlleur
$(BUILDDIR)/Screen.o: $(SRCDIR)/Screen.cpp $(SRCDIR)/Screen.hpp \
  $(UTILSDIR)/Info_Joueur.hpp $(UTILSDIR)/Couleurs.hpp $(UTILSDIR)/Animal.hpp \
  $(UTILSDIR)/Jeu_name.hpp $(UTILSDIR)/Info_Joueur_I.hpp $(UTILSDIR)/Info_Joueur_S.hpp \
  $(SRCDIR)/Controlleur.hpp $(MODDIR)/Jeu.hpp $(ELEMDIR)/Pion.hpp \
  $(ELEMDIR)/Case.hpp $(UTILSDIR)/Couleurs.hpp \
  $(MODDIR)/Joueur.hpp $(UTILSDIR)/Jeu_name.hpp \
  $(UTILSDIR)/Info_Joueur.hpp
	$(CPP) -c $< -o $@


$(BUILDDIR)/Controlleur.o: $(SRCDIR)/Controlleur.cpp $(SRCDIR)/Controlleur.hpp $(MODDIR)/Jeu.hpp \
  $(ELEMDIR)/Pion.hpp $(ELEMDIR)/Case.hpp $(UTILSDIR)/Couleurs.hpp \
  $(MODDIR)/Joueur.hpp $(UTILSDIR)/Jeu_name.hpp $(UTILSDIR)/Info_Joueur.hpp \
  $(UTILSDIR)/Animal.hpp $(UTILSDIR)/Jeu_name.hpp $(SRCDIR)/Screen.hpp \
  $(UTILSDIR)/Info_Joueur.hpp $(UTILSDIR)/Couleurs.hpp $(UTILSDIR)/Animal.hpp \
  $(ELEMDIR)/PionI.hpp $(ELEMDIR)/PionS.hpp $(MODDIR)/JeuI.hpp $(MODDIR)/JeuS.hpp \
  $(ELEMDIR)/Emplacement.hpp $(MODDIR)/JeuD.hpp
	$(CPP) -c $< -o $@








# fichiers tests
$(BUILDDIR)/TestHelp.o: $(TESTDIR)/TestHelp.cpp
	$(CPP) -c $< -o $@

$(BUILDDIR)/Test.o: $(TESTDIR)/Test.cpp $(MODDIR)/Jeu.hpp $(ELEMDIR)/Case.hpp $(ELEMDIR)/Pion.hpp $(UTILSDIR)/Couleurs.hpp $(UTILSDIR)/Animal.hpp $(UTILSDIR)/Jeu_name.hpp $(UTILSDIR)/Info_Joueur.hpp $(SRCDIR)/Screen.hpp
	$(CPP) -c $< -o $@

$(BUILDDIR)/TestI.o: $(TESTDIR)/TestI.cpp $(MODDIR)/Jeu.hpp $(MODDIR)/JeuI.hpp $(ELEMDIR)/Pion.hpp $(ELEMDIR)/PionI.hpp $(ELEMDIR)/Case.hpp $(UTILSDIR)/Couleurs.hpp $(UTILSDIR)/Jeu_name.hpp $(UTILSDIR)/Info_Joueur.hpp $(UTILSDIR)/Info_Joueur_I.hpp
	$(CPP) -c $< -o $@

$(BUILDDIR)/TestD.o: $(TESTDIR)/TestD.cpp $(MODDIR)/Jeu.hpp $(MODDIR)/Joueur.hpp $(MODDIR)/JeuD.hpp $(ELEMDIR)/Pion.hpp $(ELEMDIR)/PionD.hpp $(ELEMDIR)/Case.hpp $(ELEMDIR)/Capture.hpp $(UTILSDIR)/Couleurs.hpp $(UTILSDIR)/Jeu_name.hpp $(UTILSDIR)/Info_Joueur.hpp #$(UTILSDIR)/Info_Joueur_D.hpp
	$(CPP) -c $< -o $@

$(BUILDDIR)/TestS.o: $(TESTDIR)/TestS.cpp $(MODDIR)/Jeu.hpp $(MODDIR)/JeuS.hpp $(ELEMDIR)/Emplacement.hpp
	$(CPP) -c $< -o $@





# commande make clean
clean:
	rm -f $(BUILDDIR)/*.o

# créer le repertoire /bin s'il n'existe pas
$(shell mkdir -p $(BUILDDIR))
