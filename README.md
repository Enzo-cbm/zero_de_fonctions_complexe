# zero_de_fonctions_complexe
Newton Fractals en C++

Description
Ce projet génère des fractales de Newton dans le plan complexe à l'aide de la
méthode de Newton-Raphson. Le programme implémente une classe de nombres
complexes et applique l’algorithme de Newton sur une grille de points du plan
complexe afin de déterminer vers quelle racine chaque point converge.

Les résultats sont enregistrés dans des fichiers texte pouvant ensuite être
visualisés avec Python, Matlab ou tout autre outil de visualisation.

--------------------------------------------------

Images de fractales

Exemple pour la fonction : z^3 - 1

![Fractale Newton z3-1](images/newton_z3_minus_1.png)

Exemple pour la fonction : z^5 - 2z + 2

![Fractale Newton z5-2z+2](images/newton_z5_minus_2z_plus_2.png)

Exemple pour la fonction : z^4 + z^2 + 1

![Fractale Newton z4+z2+1](images/newton_z4_plus_z2_plus_1.png)

--------------------------------------------------

Fonctionnalités

- Implémentation d'une classe Complexe en C++
- Opérations arithmétiques sur les nombres complexes
- Calcul de dérivée numérique
- Implémentation de la méthode de Newton-Raphson
- Génération de fractales de Newton sur une grille du plan complexe
- Export des résultats dans des fichiers texte

--------------------------------------------------

Structure du projet

.
├── Complexe.hpp
├── Complexe.cpp
├── newton_raphson.cpp
└── images/

Complexe.hpp
Déclaration de la classe Complexe et des fonctions mathématiques.

Complexe.cpp
Implémentation des opérations complexes, de la méthode de Newton et
de la génération de fractales.

newton_raphson.cpp
Programme principal définissant les fonctions étudiées et lançant
la génération des fractales.

--------------------------------------------------

Compilation

Compiler le programme avec :

g++ newton_raphson.cpp Complexe.cpp -o fractale

--------------------------------------------------

Exécution

Lancer le programme avec :

./fractale

Le programme génère plusieurs fichiers texte contenant la convergence
de la méthode de Newton pour différentes fonctions.

--------------------------------------------------

Fonctions étudiées

- z^5 − 2z + 2
- z^4 + z^2 + 1
- z^2 + i
- z + 1/z
- z^3 − 2z + 2
- z^n − 1

--------------------------------------------------

Visualisation

Les fichiers générés contiennent une grille indiquant vers quelle racine
chaque point du plan complexe converge. Ces données peuvent être utilisées
pour reconstruire les fractales à l'aide d'outils de visualisation.

--------------------------------------------------

Auteur

Enzo Coranson
