#include"Controller.hpp"
#ifndef MY_CONTROLLER
// Path: Controller.cpp
// Compare this snippet from Controller.hpp:

Controller::Controller() :Controller(0){
    
}

Controller::Controller(int motorID):Controller(motorID, 0, 0, 0) {

}

Controller::Controller(int motorID, float p, float i, float d):
motorID(motorID), p(p), i(i), d(d) {
    this->lastError = 0;
    this->error = 0;
    this->integral = 0;
    this->derivative = 0;
    this->targetVelocity = 0;
    this->currentVelocity = 0;
}

void Controller::setTargetVelocity(float targetVelocity) {
    this->targetVelocity = targetVelocity;
}

float Controller::getCurrentVelocity() {
    return this->currentVelocity;
}
#endif