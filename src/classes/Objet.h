#include <Element.h>

class Objet: Element {
 public:
    //Donne la distance de l'objet #self à #oo
    //Note: on pourra sortir la fonction de la classe
    float distance_to_object(Objet oo);
    //Les clusters stockent-ils l'objet lui-même ou son identifiant ?
    //Je suppose que c'est l'objet, sinon on utilise la fonction suivante
    //et on stockera les objets dans une table de hachage
    //virtual char** get_identifier();
};
