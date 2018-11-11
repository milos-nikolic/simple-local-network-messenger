#include <QCoreApplication>
#include <QtNetwork/QUdpSocket>
#include <QNetworkInterface>
#include <QHostAddress>
#include <QList>
#include <QThread>
#include <iostream>
#include "udpclient.hpp"
#include "beaconservice.h"
#include "messagethread.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
	
    udpClient client;
    beaconService beaconTimer;
    messageThread messageCall;
	
    beaconTimer.start();
    messageCall.start();
	
    QObject::connect(&beaconTimer, SIGNAL(timerInterupt()), &client, SLOT(sendBeacon()), Qt::DirectConnection );
    QObject::connect(&messageCall, SIGNAL(enterMassage()) , &client, SLOT(sendMsg())   , Qt::DirectConnection );
	
    return a.exec();
	
}
