//
// Created by danie on 24.7.2025.
//

#include "Stavka.h"

int generirajNoviID() {
    static int trenutniID = 0;
    return trenutniID++;
}