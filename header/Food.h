#pragma once

#include "Object2D.h"

// snake's food to grow in size
class Food : public ImageObject2D
{
    using base_t = ImageObject2D;
    using base_t::base_t;

public:
	virtual ObjectType GetType() const override;

	int GetFoodValue() const;

private:
    int m_foodValue = 1;
};
