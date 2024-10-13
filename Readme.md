
# Projet d'algorithmes du text

Ce projet est divisé en deux parties : 

1. **Structure de données matricielle** : La première partie utilise une structure de données matricielle.
- Les fichiers tp1matrice.c, triematrice.h,triematriceimplimentation.c

2. **Fonction de hachage** : La deuxième partie utilise une fonction de hachage.
- Les fichiers tp1hachage.c,triehachage.h,triehachageimentation.c

## Exécution du projet

### 1. Utilisation de la structure de données matricielle
Pour exécuter le code utilisant la structure matricielle, vous devez compiler et exécuter avec la commande suivante :

```bash
make prog1
```


### 2. Utilisation de la fonction de hachage
Pour exécuter le code utilisant la fonction de hachage, vous pouvez utiliser la commande suivante :

```bash
make prog2
```

### Exécution des deux programmes en même temps
Si vous souhaitez compiler et exécuter les deux programmes (matriciel et hachage), il vous suffit d'exécuter la commande :

```bash
make
```

Cette commande va compiler les deux programmes et générer les fichiers exécutables correspondants.

## Nettoyage des fichiers générés
Après avoir exécuté les programmes, vous pouvez supprimer les fichiers objets et les exécutables générés en utilisant la commande suivante :

```bash
make clean
```

Cela supprimera tous les fichiers exécutables et objets créés lors de la compilation.

---

## Remarque
- Assurez-vous d'avoir `gcc` installé sur votre machine pour compiler le projet.
- Ce projet a été testé sous un environnement Windows, les commandes peuvent légèrement différer sous un autre système d'exploitation.
