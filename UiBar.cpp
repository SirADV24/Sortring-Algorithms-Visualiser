
#include "UiBar.h"

#define bar_color QColor{48, 63, 159 }
#define bar_swaped_swaped QColor{211, 47, 47 } 


Bar::Bar(int x, int y, int height, int width):
x{ x }, y{ y }, height{ -height }, width{ width }, is_switched{false}{}

Bar::Bar(const Bar& other):
x{ other.x }, y{ other.y }, height{ other.height },width{ other.width }, is_switched{ other.is_switched }{}

Bar::Bar()
{
	this->x = 0; this->y = 0; this->height = 0; this->width = 0; this->is_switched = false;
}

Bar::~Bar()
{
	//TODO
}

int Bar::get_height()
{
	return this->height;
}

void Bar::set_height(int new_height)
{
	this->height = new_height;
}

void Bar::switch_color()
{
	this->is_switched = !this->is_switched;
}

QRectF Bar::boundingRect() const
{
	return QRectF(x, y, width, height);
}

void Bar::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	QRectF rec = this->boundingRect();
	QBrush Brush{ bar_color };

	if(this->is_switched)
		Brush.setColor(bar_swaped_swaped);

	painter->fillRect(rec, Brush);

	painter->drawRect(rec);
}

void Bar::advance(int phase)
{

}

bool Bar::operator>(const Bar& other)
{
	return std::abs(this->height) >std::abs(other.height);
}

bool Bar::operator>=(const Bar& other)
{
	return std::abs(this->height) >= std::abs(other.height);
}

bool Bar::operator<(const Bar& other)
{
	return std::abs(this->height) < std::abs(other.height);
}

bool Bar::operator<=(const Bar& other)
{
	return std::abs(this->height) <= std::abs(other.height);
}

void Bar::operator=(const Bar& other)
{
	this->x = other.x;
	this->y = other.y;
	this->height = other.height;
	this->width = other.width;
	// TRY only height
}

bool Bar::operator==(const Bar& other)
{
	return this->height == other.height;
}

Bar& Bar::operator*()
{
	return *this;
}
