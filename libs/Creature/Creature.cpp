#include <iostream>

#include "../Date/Date.cpp"

class Creature {
private:
    short
        hunger_,
        boredom_;

    bool isAlive_;
    const std::string c_birthdate_ = Date().getDateString();
    
    void passTime();

public:
    Creature(int min = 0, int max = 5);
    // Specification C4 - Overload «
    friend std::ostream& operator<<(std::ostream& stream, Creature& c);

    void listen();
    void play();
    void feed();

};

Creature::Creature(int min, int max) {
    srand(time(0));
    max++;
    hunger_ = (rand() % max) + min;
    boredom_ = (rand() % max) + min;
    isAlive_ = true;
}


std::ostream& operator<<(std::ostream& stream, Creature& c) {
    std::string status = (c.isAlive_) ? "Alive" : "RIP";
    return (
        stream 
            << "Hunger: " << c.hunger_ 
            << " | "
            << "Boredom: " << c.boredom_
            << " | "
            << "Status: " << status
    );
}

void Creature::listen() {
    std::cout << *this;
    passTime();
}

void Creature::play() {
    
    passTime();
}

void Creature::feed() {
    
    passTime();
}

void Creature::passTime() {
    hunger_++;
    boredom_++;
}