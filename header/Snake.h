#pragma once

#include <functional>
#include <QVector>

#include "Object2D.h"

// direction of objects' movement; value is pared with arrow's ascii code on keyboard
enum class MovementDirection
{
    Up = 1,
    Down = 2,
    Right = 3,
    Left = 4,
    Nothing = 5,
};

// snake part of body (head as well)
class SnakeCell : public ImageObject2D
{
    Q_OBJECT

    using base_t = ImageObject2D;
    using base_t::base_t;

public:
   // SnakeCell(QString const & url, int x, int y);
    virtual ~SnakeCell() = default;

	virtual ObjectType GetType() const override;
};

// snake object
class Snake : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int count READ getCellsCount NOTIFY snakeCellsChanged)

public:
    Snake();

	// move snake into m_direction
	void Move();

	// sets head coords to x, y
	void GetHeadCoords(int & x, int & y) const;

	// check if head has same coords as one of body cell
	bool IsHeadHitsBody() const;

	// eat food with value (amount of food)
	void EatFood(int val);

    void SetDirection(const MovementDirection & direction);
	MovementDirection GetDirection() const;

    int getCellsCount() const;

    Q_INVOKABLE QObject * getAt(int index);

signals:
    void snakeCellsChanged();

private:
	// snake head and it's body; snake's head is m_cells[0]
    QVector<SnakeCell*> m_cells;

    // current snake's direction
    MovementDirection m_direction;
};

