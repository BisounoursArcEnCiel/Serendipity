//Marche que si le tableau n'est pas vide
//Note: Je ne connais pas assez C++ pour utiliser vector
//ou array. Je fais pour l'instant un truc moche.
int get_array_length(void* array) {
    return sizeof(array)/sizeof(array[0]);
};

//Oui, c'est crade.
int inf = 1000000000000000;
