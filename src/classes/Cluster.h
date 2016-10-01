#include <Objet.h>

class Cluster {
 public:
    void change_identifier(int i) = identifier = i;
    //Obtenir l'identifiant du cluster
    int get_identifier();
    //Obtenir la table de hachage des objets
    //présents dans le cluster #self
    void* cluster();
    //Ajouter au set #oo
    int add_to_cluster(Objet oo);
    //Retirer du set #oo
    //(qui peut ne pas être présent dans le
    //cluster -> test de présence nécessaire)
    int remove_from_cluster(Objet oo);
    //Enumération des objets dans le cluster
    //(retourne le tableau d'objets dans le cluster)
    Objet* enumerate_cluster();
 private:
    int identifier = 0;
};
