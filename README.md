# RobS
Worms-like game created for an OOP course in ROB4

# WiC_LOG # May 08, 2022 @ 12h10
Benjamin, pour régler ton bug, il fallait faire la chose suivante : déclarer une fonction "virtuelle" dans weapon.hpp.
En effet, l'objet Weapon est abstrait. On faisait un vecteur de Weapon, et on essayait d'appeler la fonction fctgravity sur cet objet. Je suppose qu'on avait pas d'erreurs car vis à vis de la compilation, on appelait un truc qui existait entre guillemets, mais rien de concret. En déclarant la classe, tout se ficelle bien.
Bien à toi,
Wilou'

# WiC_LOG # June 06, 2022 @ 23h03
Je compte bien améliorer cette branche, mais ça fait 48h que je suis dessus et je suis fatigué

### Points d'intérêt

* La séparation des entitées, de l'user interface et du terrain
* Les constructeurs & destructeurs `Entity`, `Weapon` & `Rob`
* Le nombre de lignes de code
