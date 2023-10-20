import QtQuick 2.12
import QtQuick.Window 2.12
import my.gameengine 1.0

Item
{
    height: _engine.cellSize * 20; width: _engine.cellSize * 20;
    focus: true
    Keys.onUpPressed: _engine.snakeDirection = MovementDirection.Up
    Keys.onDownPressed: _engine.snakeDirection = MovementDirection.Down
    Keys.onRightPressed: _engine.snakeDirection = MovementDirection.Right
    Keys.onLeftPressed: _engine.snakeDirection = MovementDirection.Left

    Text
    {
        id: gameoverTxt
        text: "GAMEOVER! YOUR SCORE: " + _engine.getSnake().count + " POINTS !";
        visible: _engine.isGameOver
        anchors.fill: parent
        font.family: "Helvetica"
        font.pointSize: 20
        color: "red"
        z: 1;
    }

    Repeater
    {
        id: snakeRepeater
        model: _engine.getSnake().count

        delegate: Image
        {
            width: _engine.cellSize; height: _engine.cellSize

            // !!! need to get one object at a time because of big amounts of signals slots refreshes !!!
            property var modelObj : _engine.getSnake().getAt(model.index)

            source: modelObj.image
            x: modelObj.x * 30
            y: modelObj.y * 30

            rotation:
            {
                if (model.index === 0)
                {
                    if (_engine.snakeDirection === MovementDirection.Up)
                        return 270.0;
                    else if(_engine.snakeDirection === MovementDirection.Down)
                        return 90.0;
                    else if (_engine.snakeDirection === MovementDirection.Right)
                        return 0.0;
                    else if (_engine.snakeDirection === MovementDirection.Left)
                        return 180.0;
                    else
                        return 0;
                }
            }

            Behavior on rotation
            {
                NumberAnimation
                {
                    duration: 30
                }
            }
        }
    }

    Repeater
    {
        id: foodRepeater
        model: _engine.foodCount

        delegate: Image
        {
            id: img
            width: _engine.cellSize; height: _engine.cellSize

            property var foodObj : _engine.getFoodAt(model.index)

            source: foodObj.image
            x: foodObj.x * 30
            y: foodObj.y * 30

            RotationAnimation
            {
                id: rotateCritter
                target: img
                duration: 3000
                running: !_engine.isGameOver
                property real lastAngle: 0
                from: 0;
                to: 360;
                loops: Animation.Infinite;

                onStarted: lastAngle = to;
                onStopped: from = lastAngle;
            }
        }
    }
}
