# 🎮 Arena de Défis Algorithmiques

**École Nationale des Sciences de l'Informatique (ENSI)**

Un projet en langage C qui contient 4 jeux algorithmiques pour s'entraîner et s'amuser !

---

## 📖 C'est quoi ce projet ?

C'est une **application console** avec 4 défis algorithmiques différents. Chaque défi teste tes compétences en programmation et en résolution de problèmes.

Le projet utilise :
- ✨ Des couleurs dans le terminal pour rendre l'interface jolie
- ⏱️ Un système de score basé sur le temps et les tentatives
- 🎯 Des algorithmes connus (BFS, tri, backtracking...)

---

## 👥 Équipe du Projet

| Défi | Nom | Développeur |
|------|-----|-------------|
| Défi 1 | Le Compte est Bon | Miniar Derouiche |
| Défi 2 | Mastermind | Sara BEN AISSA |
| Défi 3 | Course de Robots | Zeineb Hamzaoui |
| Défi 4 | Tri Ultime | Miniar Derouiche |

---

## 🎯 Les 4 Défis

### 1️⃣ Le Compte est Bon
**But** : Utiliser des nombres donnés pour atteindre un nombre cible

**Comment jouer** :
- Tu reçois 6 nombres (exemple : 50, 25, 10, 5, 3, 2)
- Tu dois atteindre un nombre cible (exemple : 753)
- Tu peux utiliser : `+` `-` `×` `÷`
- Exemple : `75 * 10 = 750` puis `750 + 3 = 753`

---

### 2️⃣ Mastermind Algorithmique
**But** : Deviner un code secret de 4 chiffres

**Comment jouer** :
- L'ordinateur choisit 4 chiffres (exemple : 5 2 8 1)
- Tu as 10 tentatives maximum
- Après chaque essai, tu reçois des indices :
  - 🟢 **Bien placés** : bon chiffre au bon endroit
  - 🟡 **Mal placés** : bon chiffre mais mauvais endroit

---

### 3️⃣ Course de Robots
**But** : Trouver le chemin dans un labyrinthe

**Comment jouer** :
- Un robot doit aller de **S** (départ) à **E** (arrivée)
- Le labyrinthe contient des murs **#**
- Tu dois donner les directions : **N** (Nord), **S** (Sud), **E** (Est), **O** (Ouest)
- Exemple : `EEEESSSEEE` (3 fois Est, 3 fois Sud, 3 fois Est, 1 fois Est)
- Tu as 60 secondes maximum

**Exemple de labyrinthe** :
```
S . . # . . . .
. # . # . . # .
. . . . . # . .
# . # . . . . .
. . . # . . # E
```

---

### 4️⃣ Tri Ultime
**But** : Comparer des algorithmes de tri

**Comment jouer** :
- Tu donnes un tableau de nombres
- Tu fixes un budget de "swaps" (échanges)
- Le programme teste 4 algorithmes de tri :
  - Tri à bulles
  - Tri par sélection
  - Tri par insertion
  - QuickSort
- Le programme te dit quel algorithme est le meilleur pour ton cas

---

## 🔧 Comment installer le projet ?

### Étape 1 : Télécharger le projet
```bash
git clone https://github.com/sara-benaissa/Competitive-Programming-arena.git
cd Competitive-Programming-arena
```

### Étape 2 : Compiler le projet

**Sur Windows** :
```bash
gcc -o jeu.exe main.c common/ui.c tasks/task1/compte_est_bon.c tasks/task2/mastermind.c tasks/task3/course_robots.c tasks/task4/tri_ultime.c -lm
```

**Sur Linux/Mac** :
```bash
gcc -o jeu main.c common/ui.c tasks/task1/compte_est_bon.c tasks/task2/mastermind.c tasks/task3/course_robots.c tasks/task4/tri_ultime.c -lm
```

---

## 🚀 Comment lancer le jeu ?

**Sur Windows** :
```bash
jeu.exe
```

**Sur Linux/Mac** :
```bash
./jeu
```

Tu verras ce menu :
```
****************************************************
*                                                  *
*      ARENA DE DEFIS ALGORITHMIQUES              *
*                                                  *
****************************************************

          1 > Le Compte est Bon
          2 > Mastermind Algorithmique
          3 > Course de Robots
          4 > Tri Ultime
          0 > Quitter

>> Ton choix: _
```

---

## 📁 Structure du Projet

```
Competitive-Programming-arena/
│
├── main.c                      ← Point d'entrée du programme
│
├── common/                     ← Code partagé
│   ├── ui.c                    ← Affichage (couleurs, menus)
│   └── ui.h
│
└── tasks/                      ← Les 4 défis
    ├── task1/                  ← Le Compte est Bon
    │   ├── compte_est_bon.c
    │   └── compte_est_bon.h
    │
    ├── task2/                  ← Mastermind
    │   ├── mastermind.c
    │   └── mastermind.h
    │
    ├── task3/                  ← Course de Robots
    │   ├── course_robots.c
    │   └── course_robots.h
    │
    └── task4/                  ← Tri Ultime
        ├── tri_ultime.c
        └── tri_ultime.h
```

---

## 📊 Système de Score

### Le Compte est Bon
```
Score = 1000 - (opérations × 50) - (secondes × 2)
```
Plus tu utilises d'opérations et de temps, moins tu as de points.

### Mastermind
```
Score = 1000 - (tentatives × 50) - (secondes × 2)
```
Moins d'essais = meilleur score !

### Course de Robots
```
Score de base : 1000 points
Bonus chemin optimal : +500 points
Pénalité temps : -(secondes × 5)
```

**Classement** :
- 900+ points = **MAITRE DU LABYRINTHE** 🏆
- 700-899 = **EXPERT** ⭐
- 500-699 = **AVANCE** 📈
- 300-499 = **INTERMEDIAIRE** 📊
- 0-299 = **DEBUTANT** 🌱

---

## 🎨 Les Couleurs

Le projet utilise des couleurs pour rendre l'interface plus claire :
- 🔵 **Bleu (Cyan)** : Titres et bordures
- 🟢 **Vert** : Succès et validation
- 🔴 **Rouge** : Erreurs et murs
- 🟡 **Jaune** : Questions et avertissements
- ⚪ **Blanc** : Texte normal

---

## 🧠 Ce que tu apprends avec ce projet

- **Structures de données** : tableaux, files, structures
- **Algorithmes** : 
  - Backtracking (recherche récursive)
  - BFS (parcours en largeur)
  - Algorithmes de tri
- **Programmation modulaire** : séparer le code en fichiers
- **Interface utilisateur** : créer des menus sympas dans le terminal

---

## ⚙️ Prérequis

Tu as besoin de :
- **GCC** (compilateur C)
  - Windows : MinGW
  - Linux/Mac : gcc (déjà installé normalement)
- Un **terminal** qui supporte les couleurs ANSI
- Un **éditeur de code** (VSCode, Code::Blocks, ou autre)

---

## 🐛 Problèmes Fréquents

**Les couleurs ne s'affichent pas sur Windows ?**
- Utilise Windows Terminal ou un terminal moderne
- Ou compile sans les couleurs

**Erreur de compilation ?**
- Vérifie que tous les fichiers sont présents
- Assure-toi que GCC est bien installé
- N'oublie pas le `-lm` à la fin (pour les fonctions mathématiques)

---

## 🤝 Contribution

Ce projet est fait pour apprendre ! Si tu veux ajouter :
- Un nouveau défi
- Des améliorations
- Des corrections de bugs

N'hésite pas à proposer tes modifications !

---

## 📝 Notes

- Projet réalisé dans le cadre des études à l'ENSI
- But pédagogique : apprendre les algorithmes de manière ludique
- Langage : C (avec un peu de C standard)

---

**Amuse-toi bien avec les défis ! 🎉**
