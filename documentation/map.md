# Map #

La map suivante est donné en exemple :

```clojure
NO ./img/BRICK_3B.PNG
SO ./img/BRICK_3D.PNG
WE ./img/TILE_1A.PNG
EA ./img/TILE_2C.PNG

F 220,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

## Instructions générales ##

* La map doit être fermée/entourée de murs, sinon le programme doit renvoyer
une erreur.
* Mis à part la description de la map, chaque type d’élément peut être séparée
par `une` ou `plusieurs lignes` vides.
* La description de la carte sera toujours en dernier dans le fichier, le reste des
éléments peut être dans `n’importe quel ordre`.
* Sauf pour la map elle-même, les informations de chaque élément peuvent être
séparées par `un` ou `plusieurs` espace(s).
* La carte doit être parsée en accord avec ce qui est présenté dans le fichier. Les
espaces sont une partie valable de la carte, c’est à vous de les gérer correctement. Vous devez pouvoir parser n’importe quelle sorte de carte, tant qu’elle
respecte les règles de carte.
* La map doit être composée d’uniquement ces 6 caractères :
  * `0` pour les espaces vides
  * `1` pour les murs
  * `N`,`S`,`E` ou `W` qui représentent la position de départ
du joueur et son orientation.

Cette simple map doit être valide :

```txt
111111
100101
101001
1100N1
111111
```

## Balises ##

Pour chaque élement, le premier caractère est l’identifiant (un ou deux caractères), suivi de toutes les informations spécifiques à l’élément dans un ordre
strict tel que :

Texture nord :

```txt
NO ./img/BRICK_3B.PNG/texture
```

Les balises acceptées sont donc :

* `NO` pour north
* `EA` pour east
* `WE` pour west
* `SO` pour south

## Autres Balises ##

* identifiant : F, floor, exemple : `F 220,100,0`
* identifiant : C, ceiling, exemple : `C 225,30,0`

Valeurs acceptées : les couleurs R,G,B range `[0,255]` : 0, 255, 255

Il peut y avoir des espaces entre les valeurs.

## Error handling ##

Si un problème de configuration de n’importe quel type est rencontré dans
le fichier, le programme doit quitter et renvoyer "Error\n" suivi d’un message
d’erreur explicite de votre choix.
