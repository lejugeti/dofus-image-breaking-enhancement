# dofus-image-breaking-enhancement

## But
Projet visant à créer des images de brisage d'objets de toutes pièces pour ensuite faire du machine learning dessus.

## Contexte
Au sein du mmorpg Dofus, le joueur est amené à pouvoir améliorer des équipements grâce à des objets appelés **runes**. 
Ces runes s'obtiennent en détruisant des équipements au sein du jeu. 
Malheureusement, la formule  pour connaître combien de runes on peut obtenir en brisant un objet n'est pas connue précisément. Seules des approximations existent.

J'ai décidé d'essayer de faire du machine learning sur des données de brisage. Mais ces données sont longues à accumuler manuellement.
Pour m'aider, j'ai besoin d'un programme qui va détecter en jeu les moments où je fais effectivement du brisage, et consigner les données récoltées.

Mais pour obtenir un tel programme capable de détecter et segmenter des données du jeu, par exemple avec un algorithme YOLO, j'ai encore une fois besoin de données du jeu. 
Plus précisément, j'ai besoin d'images où tous les éléments d'une session de brisage sont présents.

C'est là qu'intervient dofus-image-breaking-enhancement. Créer des images plausibles de brisage pour entraîner ultérieurement un algorithme de segmentation dessus.

## Exemple de sortie de l'algorithme

Des exemples de ce que peut produire l'algorithme sont consultables dans le dossier `./exemples`.
