#pragma once

#include <QPainter>
#include <qgraphicsitem.h>
#include <qcolor.h>

#include <QPainter>
#include <qgraphicsscene.h>
#include <qgraphicsitem.h>

class Bar : public QGraphicsItem 
{
private:
	int x;
	int y;
	int height;
	int width;
	bool is_switched;
public:
	Bar(int x, int y, int height, int width);
	Bar(const Bar& other);
	Bar();
	~Bar();

	int get_height();
	void set_height(int new_height);
	void switch_color();

	QRectF boundingRect() const;
	void paint
	(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

	void advance(int phase);

	bool operator >(const Bar& other);
	bool operator >=(const Bar& other);
	bool operator < (const Bar& other);
	bool operator <=(const Bar& other);
	void operator =(const Bar& other);
	bool operator ==(const Bar& other);
	Bar& operator*();
};