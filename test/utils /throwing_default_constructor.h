//
// Created by Клим on 16.07.2023.
//

#ifndef VEC_THROWING_DEFAULT_CONSTRUCTOR_H
#define VEC_THROWING_DEFAULT_CONSTRUCTOR_H


#include <stdexcept>

class throwing_default_constructor {
public:
    throwing_default_constructor(){
        throw std::runtime_error("m");
    }
};


#endif //VEC_THROWING_DEFAULT_CONSTRUCTOR_H
