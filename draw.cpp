#include "draw.h"
#include<QPainter>
draw::draw(QPoint p)
{
    QPainter pain;
    pain.drawPoint(p);
}
