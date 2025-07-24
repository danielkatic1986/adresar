#include <iostream>

#include "Meni.h"
#include "Adresar.h"

int main() {
    bool izvrsavaj = true;
    char izbor = 0;

    while (izvrsavaj) {
        IspisMenija();
        std::cout << "Unesite izbor: ";
        std::cin >> izbor;
        if (izbor == 'X' || izbor == 'x') {
            izvrsavaj = false;
        }
    }
    
    return 0;
}