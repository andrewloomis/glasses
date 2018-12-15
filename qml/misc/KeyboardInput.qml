import QtQuick 2.0

Item {
//    focus: true
    Keys.onPressed: {
        switch(event.key)
        {
        case Qt.Key_Left:
            gestureManager.toLeft();
            console.log("Left key pressed");
            break;
        case Qt.Key_Right:
            gestureManager.toRight();
            console.log("Right key pressed");
            break;
        case Qt.Key_Down:
            gestureManager.toDown();
            console.log("Down key pressed");
            break;
        case Qt.Key_Up:
            gestureManager.toUp();
            console.log("Up key pressed");
            break;
        case Qt.Key_Enter:
            gestureManager.select();
            console.log("Enter key pressed");
            break;
        case Qt.Key_A:
            authenticationManager.unlock();
            console.log("A key pressed");
            break;
        case Qt.Key_T:
            gestureManager.select();
            console.log("T key pressed");
            break;
        default:
            console.log("Unrecognized key event: ", event.key);
        }
    }
}
