#pragma once

#include <QObject>
#include <QtQml/qqml.h>

#include <qobjectdefs.h>
#include <QString>

// type of objects in game
enum class ObjectType
{
	SnakeCell,
	Food,
	Enemy,
};

// base abstract class to every object in game
class Object2D : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int x READ getX WRITE setX NOTIFY xChanged)
    Q_PROPERTY(int y READ getY WRITE setY NOTIFY yChanged)

public:
    Object2D(int x, int y);
    virtual ~Object2D() = default;

    int getX() const;
    int getY() const;

    void setX(int x);
    void setY(int y);

	virtual ObjectType GetType() const = 0;

signals:
    void xChanged();
    void yChanged();

private:
    int m_x = 0;
    int m_y = 0;
};

// abstract class to every object with image in game
class ImageObject2D : public Object2D
{
    Q_OBJECT
    Q_PROPERTY(QString image READ getImageUrl WRITE setImageUrl NOTIFY imageUrlChanged)

    using base_t = Object2D;

public:
    ImageObject2D(QString const & imageURL, int x, int y);
    virtual ~ImageObject2D() = default;

    QString getImageUrl() const;
    void setImageUrl(QString const & imageUrl);

signals:
    void imageUrlChanged();

private:
    QString m_image;
};
