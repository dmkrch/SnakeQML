#include "../header/GameEngine.h"
#include "../header/Constants.h"

#include <QRandomGenerator>

GameEngine::GameEngine(QObject *parent)
{
    m_timer = new QTimer();
    m_snake = new Snake();

    m_foodList << new Food(bananaImgUrl, 5, 7);
    m_foodList << new Food(appleImgUrl, 8, 8);
    m_foodList << new Food(strawberryImgUrl, 7, 2);
    m_foodList << new Food(orangeImgUrl, 9, 1);
    emit foodCountChanged();

    QObject::connect(m_timer, &QTimer::timeout, this, &GameEngine::onNewMove);
}

void GameEngine::Start() const
{
    m_timer->start(300);
}

int GameEngine::getCellSize() const
{
    static int cellSize = 30;
    return cellSize;
}

QObject *GameEngine::getFoodAt(int index) const
{
    if (index < 0 || index >= m_foodList.count())
        return nullptr;

    return m_foodList[index];
}

int GameEngine::getFoodCount() const
{
    return m_foodList.size();
}

void GameEngine::GenerateNewFood()
{
    // generate randomly in maxCells, maxCells coords. but not in head of snake

    int headX, headY;
    m_snake->GetHeadCoords(headX, headY);
    int randomImgIndex = QRandomGenerator::global()->bounded(0, images.size());

    int randomX = headX;
    int randomY = headY;

    while (randomX == headX && randomY == headY)
    {
        randomX = QRandomGenerator::global()->bounded(0, maxCells);
        randomY = QRandomGenerator::global()->bounded(0, maxCells);
    }

    m_foodList << new Food(images[randomImgIndex], randomX, randomY);
    emit foodCountChanged();
}

void GameEngine::setDirection(int dir)
{
    MovementDirection dirCasted = static_cast<MovementDirection>(dir);

    if ((dirCasted == MovementDirection::Down) && (m_snake->GetDirection() == MovementDirection::Up))
        return;

    if ((dirCasted == MovementDirection::Up) && (m_snake->GetDirection() == MovementDirection::Down))
        return;

    if ((dirCasted == MovementDirection::Left) && (m_snake->GetDirection() == MovementDirection::Right))
        return;

    if ((dirCasted == MovementDirection::Right) && (m_snake->GetDirection() == MovementDirection::Left))
        return;

    m_snake->SetDirection(dirCasted);
    emit directionChanged();
}

QObject *GameEngine::getSnake() const
{
    return m_snake;
}

int GameEngine::getRotation() const
{
    auto dir = m_snake->GetDirection();

    switch(dir)
    {
    case MovementDirection::Right:
        return 0;
    case MovementDirection::Down:
        return 90;
    case MovementDirection::Left:
        return 180;
    case MovementDirection::Up:
        return 270;
    default:
        return 0;
    }
}

int GameEngine::getDirection() const
{
    return static_cast<int>(m_snake->GetDirection());
}

bool GameEngine::getGameover() const
{
    return m_isGameover;
}

void GameEngine::onNewMove()
{
    m_snake->Move();

    if (m_snake->IsHeadHitsBody())
    {
        m_timer->stop();

        m_isGameover = true;
        emit gameOverChanged();
        return;
    }

    int headX, headY;
    m_snake->GetHeadCoords(headX, headY);

    auto it = std::find_if(m_foodList.begin(), m_foodList.end(), [headX, headY](Food * food)
    {
        return (food->getX() == headX) && (food->getY() == headY);
    });

    // snake's head is on food
    if (it != m_foodList.end())
    {
        m_snake->EatFood((*it)->GetFoodValue());

        m_foodList.erase(it);
        emit foodCountChanged();

        m_timer->setInterval(m_timer->interval() * 0.9);

        GenerateNewFood();
    }
}
