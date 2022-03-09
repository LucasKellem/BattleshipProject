//
// Created by lucas on 12/7/2020.
//

#ifndef FINAL_CIRCULARBUTTON_H
#define FINAL_CIRCULARBUTTON_H

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


class CircularButton {
private:
    CircleShape _circleButton;
    bool _isActive;
public:
    /** @brief Sets button
    * @desc Sets button. In this case, it will be a circular button, as the first parameter is a float (radius) and the second is a vector2f.
    * @param Radius/Float
    * @param Position/Vector2f
    */
    void setButton(float, Vector2f);

    /** @brief Returns the _circleButton
    * @desc Returns the member circle shape, will be called by a circular button object. Will check "isActive" for
    * coloring.
    * @return circleshape
    */
    CircleShape getButton(); //Not const because a value is changed depending on _isActive

    /** @brief Checks if user event is hovering over a button.
    * @desc Checks if user event is hovering over a button. If it is, _circleButton will change color
    * (as to indicate hovering). Leave params constant!
    * @param Event
    * @return Bool (is or isn't hovering)
    */
    bool isHovering(int, int);

    /** @brief Checks if user event is on a button.
    * @desc Checks if user event is on a button. If it is, return true. Leave params constant!
    * @param Event
    * @return Bool (is or isn't clicked)
    */
    bool isClicked(Event);


};


#endif //FINAL_CIRCULARBUTTON_H
