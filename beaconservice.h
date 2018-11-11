#ifndef BEACONSERVICE_H
#define BEACONSERVICE_H

#include <QObject>
#include <QThread>
#include <iostream>

using namespace std;

class beaconService : public QThread
{
		Q_OBJECT
public:
		beaconService();
private:
		void run();
signals:
	 void timerInterupt();
	 
public slots:

};

#endif // BEACONSERVICE_H
