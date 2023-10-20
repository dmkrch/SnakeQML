#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QTimer>
#include <QDebug>

#include "Snake.h"
#include "Food.h"

class GameEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int cellSize READ getCellSize CONSTANT)
    Q_PROPERTY(int foodCount READ getFoodCount NOTIFY foodCountChanged)
    Q_PROPERTY(int isGameOver READ getGameover NOTIFY gameOverChanged)
    Q_PROPERTY(int snakeDirection READ getDirection WRITE setDirection NOTIFY directionChanged)

    using base_t = QObject;

public:
    GameEngine(QObject * parent = nullptr);

    // general
    void Start() const;
    int getCellSize() const;

    // food
    Q_INVOKABLE QObject * getFoodAt(int index) const;
    int getFoodCount() const;
    void GenerateNewFood();

    // snake
    Q_INVOKABLE QObject * getSnake() const;

    // direction
    void setDirection(int dir);
    int getDirection() const;
    Q_INVOKABLE int getRotation() const;

    // gameover
    bool getGameover() const;

private slots:
    void onNewMove();

signals:
    void foodCountChanged();
    void gameOverChanged();
    void directionChanged();

private:
    void SnakeEatsFoodAction();

private:
    Snake * m_snake;
    QTimer * m_timer;
    QVector<Food*> m_foodList;
    bool m_isGameover = false;
};

#endif // GAMEENGINE_H
