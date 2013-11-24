/**
 * ToroidalClock5.cpp
 *
 * Toroidal Clock 5
 * Window displays time using text surrounded by arcs to represent hours, minutes, seconds.
 *
 * Created 2013-08-17
 * Author Stanley Hawkeye
 *
 * Licensed under The MIT License
 */

#include "ToroidalClock5.h"

#include <QTime>
#include <QDate>
#include <QPainter>

ToroidalClock5::ToroidalClock5(QWindow *parent) : QWindow(parent)
{
	this->setFlags(flags() | Qt::FramelessWindowHint | Qt::WindowStaysOnBottomHint | Qt::Tool);
	this->setModality(Qt::NonModal);
	this->setWidth(210);
	this->setHeight(210);

	m_backingStore = new QBackingStore(this);
	timerId = startTimer(1000);
}

ToroidalClock5::~ToroidalClock5()
{
	this->killTimer(timerId);
	delete m_backingStore;
}

void ToroidalClock5::exposeEvent(QExposeEvent *)
{
	render();
}

void ToroidalClock5::render()
{
	if (!isExposed())
		return;

	QRect rect(0, 0, width(), height());
	m_backingStore->beginPaint(rect);

	QPaintDevice *device = m_backingStore->paintDevice();
	QPainter painter(device);

	renderClock(&painter);

	m_backingStore->endPaint();
	m_backingStore->flush(rect);
}

void ToroidalClock5::timerEvent(QTimerEvent *event)
{
	if(this->timerId == event->timerId())
		this->render();
}

void ToroidalClock5::resizeEvent(QResizeEvent* event)
{
	m_backingStore->resize(event->size());
	int side = qMin(width(), height());
	QRegion maskedRegion(width() / 2 - side / 2, height() / 2 - side / 2, side, side, QRegion::Ellipse);
	setMask(maskedRegion);
	if (isExposed())
		render();
}

void ToroidalClock5::renderClock(QPainter* p)
{
	// time
	QTime time = QTime::currentTime();
	QDate date = QDate::currentDate();

	p->setRenderHint(QPainter::Antialiasing);

	// put the center in the center
	p->translate(width() / 2, height() / 2);
	// make it scale with the window
	int smalestSide = qMin(width(), height());
	p->scale(smalestSide / 210.0, smalestSide / 210.0);


	// background
	p->setBrush(markerColor);
	p->drawEllipse(-110,-110,220,220);

	// small markers
	p->setBrush(hourColor);
	p->setPen(minuteColor);
	for (int j = 0; j < 60; ++j) {
		if ((j % 5) != 0)
			p->drawLine(92, 0, 96, 0);
		p->rotate(6.0);
	}

	p->rotate(-180);
	p->setPen(Qt::NoPen);

	// hours
	p->save();
	p->rotate(3);
	p->setBrush(hourColor);
	int hour = time.hour();
	if(hour >= 12)
		hour -= 12;
	for(int i = 0; i < hour; i++)
	{
		p->drawPolygon(hourMarker,12);
		p->rotate(30);
	}
	p->restore();

	// minutes
	p->save();
	p->setBrush(minuteColor);
	p->rotate(3);
	for(int i = 0; i < time.minute(); i++)
	{
		p->drawPolygon(minuteMarker,4);
		p->rotate(6.0);
	}
	p->restore();

	// seconds
	p->save();
	p->rotate(3);
	p->setBrush(secondColor);
	for(int i = 0; i < time.second(); i++)
	{
		p->drawPolygon(secondMarker,4);
		p->rotate(6.0);
	}
	p->restore();

	// markers
	p->setBrush(markerColor);
	for(int i = 0; i < 12; i++)
	{
		p->drawRect(40, -1, 60, 2);
		p->rotate(30);
	}

	QString dateString = QString().sprintf("%04i-%02i-%02i",date.year(),date.month(),date.day());
	QString timeString = QString().sprintf("%02i-%02i-%02i", time.hour(), time.minute(), time.second());

	p->rotate(180);
	p->setPen(textColor);

	p->setFont(QFont("Tahoma", 13));
	p->drawText(-40, -20, 80, 20, Qt::AlignTop | Qt::AlignHCenter, timeString);

	p->setFont(QFont("Tahoma", 10.2));
	p->drawText(-40, 0, 80, 15, Qt::AlignTop | Qt::AlignHCenter, dateString);

	p->setFont(QFont("Tahoma", 10));
	p->drawText(-40, 15, 80, 30, Qt::AlignTop | Qt::AlignHCenter, QString(daysOfTheWeek[date.dayOfWeek()-1]));
}
