//
// Created by lucas on 12/7/2020.
//

#ifndef FINAL_RECTANGULARBUTTON_H
#define FINAL_RECTANGULARBUTTON_H

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


class RectangularButton {
private:
    RectangleShape _rectangleButton;
    bool _isActive;
public:
    /** @brief Sets button
    * @desc Sets button. In this case, it will be a rectangle button, as both parameters are vector2fs.
    * @param Size/Vector2f
    * @param Position/Vector2f
    */
    void setButton(Vector2f, Vector2f);

    /** @brief Returns the _buttonRect
    * @desc Returns the member rectangle shape, will be called by a rectangular button object. Will check "isActive" for
    * coloring.
    * @return rectangleshape
    */
    RectangleShape getButton() ;

    /** @brief Checks if user mouse is hovering over a button.
    * @desc Checks if user mouse location is within button bounds. If it is, _buttonRect will change color
    * (as to indicate hovering). Leave params constant!
    * @param Mouse
    * @param RenderWindow
    * @return Bool (is or isn't hovering)
    */
    bool isHovering(Mouse, const RenderWindow &);

    /** @brief Checks if user event is on a button.
    * @desc Checks if user event is clicked on a button. If it is, return true. Leave params constant!
    * @param Event
    * @return Bool (is or isn't clicked)
    */
    bool isClicked(Event);
};


#endif //FINAL_RECTANGULARBUTTON_H
