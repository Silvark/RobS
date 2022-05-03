
#include <cmath>
#define taillebloc 10

int positiontableau(float p){
    int x  = (int)std::floor(p/taillebloc);
    return x;
}
