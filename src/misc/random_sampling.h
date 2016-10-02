#include <stdlib.h>
#include <time.h>

#include <misc.h>
#include <Element.h>
#include <exceptions.h>

struct sampling {
    //the set of selected elements
    Element* reservoir;
    //the set of non-selected elements
    Element* set;
};

sampling swap(sampling sample_set, Element e, int i, int j) {
    if (sample_set.set[i].equals(e)) {
	sample_set.set[i] = sample_set.reservoir[j];
    };
    sample_set.reservoir[j] = e;
    return sample_set;
};

Element* random_selection(Element* initial_set, int number_selected) {
    //initial_set est supposé non vide !!
    int n = get_array_length(initial_set);
    if (number_selected > n) {
	throw WrongLength();
    };
    if (number_selected == n) {
	return initial_set;
    };
    int i, j;
    sampling sample_set;
    Element sample_set.reservoir[number_selected];
    Element sample_set.set[n];

    //initialisation du réservoir
    for(j=0; j < number_selected; j++) {
	sample_set.reservoir[j] = initial_set[j];
    };
    //initialisation du set
    for(i=0; i < number_selected; i++) {
	sample_set.set[i] = initial_set[0].empty();
    };
    for(i=number_selected; i < n; i++) {
	sample_set.set[i] = initial_set[i];
    };

    //Sampling
    srand (time(NULL));
    for(i=number_selected; i < n; i++) {
	j = rand() % i;
	if (j < number_selected) {
	    sample_set = swap(sample_set, initial_set[i], i, j);
	};
    };
    return sample_set.reservoir;
};