#ifndef MISC_H
    #define MISC_H

// Pour les arêtes du graphe des blobs
    #ifndef D_LIM
        #define D_LIM 0.5
    #endif

// Pour rapprocher deux objets de deux blobs différents
    #ifndef T_BLOB
        #define T_BLOB 0.5
    #endif

// Pour créer un nouveau cluster dans K-Means
    #ifndef T_CLUST
        #define T_CLUST 0.5
    #endif

// Pour passer d'une méthode de numérotation de graphe à l'autre
    #ifndef T_KNOW
        #define T_KNOW 0.5
    #endif

// Nombre de niveaux de sérendipité
    #ifndef T_LEVEL
        #define T_LEVEL 5
    #endif

    #ifndef INFINITY
        #define INFINITY -1
    #endif

    #define RESET   "\033[0m"
    #define BLACK   "\033[30m"      /* Black */
    #define RED     "\033[31m"      /* Red */
    #define GREEN   "\033[32m"      /* Green */
    #define YELLOW  "\033[33m"      /* Yellow */
    #define BLUE    "\033[34m"      /* Blue */
    #define MAGENTA "\033[35m"      /* Magenta */
    #define CYAN    "\033[36m"      /* Cyan */
    #define WHITE   "\033[37m"      /* White */
    #define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
    #define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
    #define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
    #define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
    #define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
    #define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
    #define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
    #define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

#endif //MISC_H
