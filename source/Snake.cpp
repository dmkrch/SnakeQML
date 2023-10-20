#include "../header/Snake.h"

#include <QString>
#include <QDebug>

#include "../header/Constants.h"

#include <algorithm>

Snake::Snake()
    : m_direction(gameengine::MovementDirection::Right)
{
    // create head of snake and 2 other cells
    m_cells << new SnakeCell(headImgUrl, 2, 0);
    m_cells << new SnakeCell(bodyImgUrl, 1, 0);
    m_cells << new SnakeCell(bodyImgUrl, 0, 0);

    emit snakeCellsChanged();
}

void Snake::Move()
{
    if (m_direction == gameengine::MovementDirection::Nothing)
		return;

	// When snake moves, head moves to new direction. Each previous body cell transforms to next body cell coordinates

	// calculate new coords of head
    int newX = m_cells[0]->getX();
    int newY = m_cells[0]->getY();

	switch(m_direction)
	{
    case gameengine::MovementDirection::Up:
		--newY;
		break;
    case gameengine::MovementDirection::Down:
		++newY;
		break;
    case gameengine::MovementDirection::Right:
		++newX;
		break;
    case gameengine::MovementDirection::Left:
		--newX;
		break;
	default:
		break;
	}

    if (newX == maxCells)
        newX = 0;
    else if (newY == maxCells)
        newY = 0;
    else if (newX == -1)
        newX = maxCells - 1;
    else if (newY == -1)
        newY = maxCells - 1;

    int tempX = -1;
    int tempY = -1;

    for (auto & snakeCell : m_cells)
    {
        tempX = snakeCell->getX();
        tempY = snakeCell->getY();

        snakeCell->setX(newX);
        snakeCell->setY(newY);

        newX = tempX;
        newY = tempY;
    }
}

void Snake::GetHeadCoords(int& x, int& y) const
{
    x = m_cells[0]->getX();
    y = m_cells[0]->getY();
}

bool Snake::IsHeadHitsBody() const
{
    if (m_cells.size() < 2)
		return false;

    int headX = m_cells[0]->getX();
    int headY = m_cells[0]->getY();

    return std::any_of(m_cells.begin() + 1, m_cells.end(), [&headX, &headY](SnakeCell * cell)
	{
        return (cell->getX() == headX) && (cell->getY() == headY);
	});
}

void Snake::EatFood(int val)
{
	int newX = 0;
	int newY = 0;

	for (int i = 0; i < val; ++i)
	{
        newX = m_cells.back()->getX();
        newY = m_cells.back()->getY();

		// insert new body cell to opposite side of current direction
		switch (m_direction)
		{
        case gameengine::MovementDirection::Down:
			--newY;
			break;
        case gameengine::MovementDirection::Up:
			++newY;
			break;
        case gameengine::MovementDirection::Right:
			--newX;
			break;
        case gameengine::MovementDirection::Left:
			++newX;
			break;
		default:
			return;
		}

        m_cells << new SnakeCell(bodyImgUrl, newX, newY);
        emit snakeCellsChanged();
	}
}

void Snake::SetDirection(gameengine::MovementDirection direction)
{
	m_direction = direction;
}

gameengine::MovementDirection Snake::GetDirection() const
{
	return m_direction;
}

int Snake::getCellsCount() const
{
    return m_cells.size();
}

QObject *Snake::getAt(int index)
{
    if (index < 0 || index >= m_cells.count())
        return nullptr;

    return m_cells[index];
}

ObjectType SnakeCell::GetType() const
{
	return ObjectType::SnakeCell;
}
