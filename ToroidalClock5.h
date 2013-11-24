/**
 * ToroidalClock.h
 *
 * Toroidal Clock Qt Window
 * Displays time using text surrounded by arcs to represent hours, minutes, seconds.
 *
 * Created 2013-08-17
 * Author Stanley Hawkeye
 *
 * Licensed under The MIT License
 */

#ifndef TOROIDIAL_CLOCK_H
#define TOROIDIAL_CLOCK_H

#include <QWindow>
#include <QBackingStore>
#include <QPainter>
#include <QTimerEvent>
#include <QPoint>
#include <QResizeEvent>

class ToroidalClock5 : public QWindow
{
	Q_OBJECT
private:
	int timerId;

	QBackingStore *m_backingStore;

	void render();
	void renderClock(QPainter* );

public:
	explicit ToroidalClock5(QWindow* parent=0);
	~ToroidalClock5();
	void timerEvent(QTimerEvent*);
	void resizeEvent(QResizeEvent*);
	void exposeEvent(QExposeEvent*);

public:
	// markers
	const QPointF hourMarker[12] = {
		QPointF(4,80), // left bottom
		QPointF(-4,80),
		QPointF(-12.720344843559309, 79.08345482501971),
		QPointF(-20.91713345705869, 77.3205892886209),
		QPointF(-28.884749579734212, 74.71058319753664),
		QPointF(-36.53589834221429, 71.28203232461448), // right bottom

		QPointF(-45.241391553040565, 89.32086257053538), // right top
		QPointF(-35.6569819853842, 93.56056667044074),
		QPointF(-25.681907062284765, 96.77520162543794),
		QPointF(-15.425455791768826, 98.92954722233488),
		QPointF(-5,100),
		QPointF(5,100) //left top
	};

	const QPointF minuteMarker[4] = {
		QPointF(-3,60),
		QPointF(-4,80),
		QPointF(4,80),
		QPointF(3,60)
	};

	const QPointF secondMarker[4] = {
		QPointF(-2, 40),
		QPointF(-3, 60),
		QPointF(3, 60),
		QPointF(2, 40)
	};

	// colors
	const QColor markerColor = QColor(0,0,0);
	const QColor hourColor = QColor(40, 7, 250);
	const QColor minuteColor = QColor(250, 7, 246);
	const QColor secondColor = QColor(7, 177, 250);
	const QColor textColor = QColor(255, 255, 255);

	// days of the week
	const char daysOfTheWeek[7][11] = {
		"Monday",
		"Tuesday",
		"Wednesday",
		"Thursday",
		"Friday",
		"Saturday",
		"Sunday",
	};
};

#endif
