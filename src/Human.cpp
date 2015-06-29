//
// Created by tattsun on 15/06/29.
//

#include "Human.h"

namespace dust {
    Human::Human(std::string name) {
        this->name_ = name;
    }

    Human::~Human() {
    }

    void Human::SayHello() {
        std::cout << "Hello, my name is " << name_ << "." << std::endl;
    }
}