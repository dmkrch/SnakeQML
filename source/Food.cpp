#include "../header/Food.h"

ObjectType Food::GetType() const
{
    return ObjectType::Food;
}

int Food::GetFoodValue() const
{
    return m_foodValue;
}
