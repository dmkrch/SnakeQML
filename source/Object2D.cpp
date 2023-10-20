#include "../header/Object2D.h"

Object2D::Object2D(int x, int y)
    : m_x(x)
    , m_y(y)
{

}

int Object2D::getX() const
{
    return m_x;
}

int Object2D::getY() const
{
    return m_y;
}

void Object2D::setX(int x)
{
	m_x = x;
    emit xChanged();
}

void Object2D::setY(int y)
{
	m_y = y;
    emit yChanged();
}

ImageObject2D::ImageObject2D(QString const & imageURL, int x, int y)
    : base_t(x, y)
    , m_image(imageURL)
{

}

void ImageObject2D::setImageUrl(QString const & imageUrl)
{
    m_image = imageUrl;
    emit imageUrlChanged();
}

QString ImageObject2D::getImageUrl() const
{
    return m_image;
}
