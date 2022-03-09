//
// Created by lucas on 12/7/2020.
//

#include "CircularButton.h"

void CircularButton::setButton(const float radius, const Vector2f position){ //Set button. This is for a circular button, given how the params are 1 float (for radius) and 1 vector of floats.
    _circleButton.setRadius(radius); //set radius of button
    _circleButton.setPosition(position.x, position.y); //set position of button
    _circleButton.setFillColor(Color(255, 255, 255, 0)); //set color white, transparency 0.
    _isActive = false;
}

CircleShape CircularButton::getButton() { //This is for a circular button.
    if(_isActive){
        _circleButton.setFillColor(Color(255, 255, 255, 128)); //Make button not-transparent
    }else{
        _circleButton.setFillColor(Color(255, 255, 255, 0)); //Make Transparent
    }
    _isActive = false;
    return _circleButton; //Get the circleshape.
}

bool CircularButton::isClicked(const Event userMouse){ //Checks if user event is on a button. If it is, return true. Leave params constant!
    if(_circleButton.getGlobalBounds().contains(userMouse.mouseButton.x, userMouse.mouseButton.y)){ //Check bounds
        _isActive = true;
        return true;
    }
    else{
        _isActive = false;
        return false;
    }
}

bool CircularButton::isHovering(const int x, const int y){  //Checks if user mouse is hovering over a button. If it is, _circleButton will change color (as to indicate hovering). Leave params constant!
    if(_circleButton.getGlobalBounds().contains(static_cast<float>(x), static_cast<float>(y))){ //Check bounds
        _isActive = true;
        return true;
    }
    else{
        _isActive = false;
        return false;
    }
}