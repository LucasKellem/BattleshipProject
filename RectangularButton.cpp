//
// Created by lucas on 12/7/2020.
//

#include "RectangularButton.h"

void RectangularButton::setButton(const Vector2f size, const Vector2f position){ //Set button. This is for a rectangular button, given how the params are 2 vectors of floats.
    _rectangleButton.setSize(size); //set the size of the button
    _rectangleButton.setPosition(position.x, position.y); //set position of button
    _rectangleButton.setFillColor(Color(255, 255, 255, 0)); //set color white, transparency 0.
    _isActive = false;
}

RectangleShape RectangularButton::getButton() { //This is for a rectangular button.
    if(_isActive){
        _rectangleButton.setFillColor(Color(255, 255, 255, 128)); //Make button not-transparent
    }else{
        _rectangleButton.setFillColor(Color(255, 255, 255, 0)); //Make Transparent
    }
    return _rectangleButton; //Get the rectangleshape.
}

bool RectangularButton::isHovering(const Mouse userMouse, const RenderWindow &myWindow){  //Checks if user mouse is hovering over a button. If it is, _buttonRect will change color (as to indicate hovering). Leave params constant!
    if(_rectangleButton.getGlobalBounds().contains(static_cast<float>(userMouse.getPosition(myWindow).x), static_cast<float>(userMouse.getPosition(myWindow).y))){ //Check collision
        _isActive = true;
        return true;
    }
    else{
        _isActive = false;
        return false;
    }
}

bool RectangularButton::isClicked(const Event userMouse){ //Checks if user event is on a button. If it is, return true. Leave params constant!
    if(_rectangleButton.getGlobalBounds().contains(userMouse.mouseButton.x, userMouse.mouseButton.y)){ //Check collision
        _isActive = true;
        return true;
    }
    else{
        _isActive = false;
        return false;
    }
}