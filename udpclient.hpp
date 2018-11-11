#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include <iostream>
#include <QMap>

using namespace std;

class udpClient : public QObject
{
      Q_OBJECT
private:

    char* userName;

    quint8 cnt = 0;                                 //za odbrojavanje poslatih beacon-a za proveru starih/novih clanova mreže
    QUdpSocket   *UDPsocket;
    QHostAddress *ip_adress;                       //ip adresa klijenta
    QHostAddress *ip_broatcastAdress;              //broadcast adresa (255.255.255.255)
    QMap<QByteArray , QByteArray> users, usersOld; //Kontejner koji sadrzi staru i novu listu korisnika.

	void beaconResponce(QHostAddress address);
	void userResponse(QHostAddress address,  char* buffer, int readCount);
	void msgResponse (QHostAddress address,  char* buffer, int readCount);
	
public:

    udpClient();

	private slots:
	void sendMsg     ();
	void proces_datagram();
	void sendBeacon();

};

#endif // UDPCLIENT_H
