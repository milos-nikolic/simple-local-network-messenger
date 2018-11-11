#include "udpclient.hpp"
#include <stdio.h>
#include <string.h>
#include <QThread>
#include <QMap>
#include <iostream>

char* insertHostIp()
{
    char*  buffer = (char*) malloc (20);
    cout << "Enter host IP: " ;
    cin >> buffer;
    return buffer;
}

char* insertUsername(){
    char*  buffer = (char*) malloc (20);
    cout << "Enter username: " ;
    cin >> buffer;
    return buffer;
}

void enterMsg(char *msg)
{
    cout << "Enter msg: " ;
    cin >> msg;
}

udpClient::udpClient()
{
	userName            = insertUsername();
	ip_adress           = new QHostAddress(insertHostIp());
	ip_broatcastAdress  = new QHostAddress("255.255.255.255");
	UDPsocket = new QUdpSocket(this);
	UDPsocket->bind(*ip_adress,8008);
	connect(UDPsocket, SIGNAL(readyRead()), this, SLOT(proces_datagram()), Qt::DirectConnection);
}

void udpClient::sendBeacon()
{
   if(cnt == 4)
   {
		QMap<QByteArray, QByteArray>::const_iterator i = users.constBegin();
			
		while ( i != users.constEnd() ) //provera novih korisnika
		{
			if( !usersOld.contains(i.key()) )cout <<  endl <<"New user: " << i.value().data() << endl << "Enter msg: ";
			++i;
		}
			
		i = usersOld.constBegin();
		
		while ( i != usersOld.constEnd() ) //provera ko je otisao
		{
			if( !users.contains(i.key()) ) 
			{
				cout << endl <<"User <" << i.value().data() <<"> left" <<endl<< "Enter msg: ";
			}
			++i;
		}
		
		usersOld = users;
		users.clear();
		cnt = 0;
	}

    cnt++;

    QByteArray Data;
    Data.clear();
    Data.append("BEACON");
    UDPsocket->writeDatagram(Data,*ip_broatcastAdress,8008);
}

void udpClient::sendMsg()
{
	
    char msg[100];
    enterMsg(msg);
    QByteArray Data;
    Data.clear();
    Data.append("MSG=");
    Data.append(msg);
    UDPsocket->writeDatagram(Data,*ip_broatcastAdress,8008);
	
}

void udpClient::beaconResponce(QHostAddress address)
{
	
    QByteArray Data;
    Data.clear();
    Data.append("USER=");
    Data.append(userName);
    UDPsocket->writeDatagram(Data,address,8008);
	
}

void udpClient::userResponse(QHostAddress address,  char* buffer, int readCount){
	
	buffer[readCount] = '\0';
	QByteArray ipAdr = address.toString().toUtf8().constData();
	QByteArray userName;
	userName.clear();
	userName.append(&buffer[5]);
	users[ipAdr] = userName;
	
}

void udpClient::msgResponse( QHostAddress address,  char* buffer, int readCount )
{
	
	buffer[readCount] = '\0';
	QByteArray adr = address.toString().toUtf8().constData();
	
	if( usersOld.contains(adr) )
	{
		cout  << endl << "User: "<< usersOld.value(adr).data() <<  "  " << "Message: ";
	}
	
	cout << &buffer[4] << endl;
	cout <<  "Enter msg: ";
	
}

void udpClient::proces_datagram()
{
    int readCount= 0;
    char buffer[1600];
    QHostAddress address;
    quint16 recPort = 0;

    qint64  datagramSize;

      while (UDPsocket->hasPendingDatagrams())
      {
          datagramSize = UDPsocket->pendingDatagramSize();
          readCount = UDPsocket->readDatagram(buffer , datagramSize, &address, &recPort);
          if(*ip_adress == address)continue;
          if(0 == strncmp(buffer,"BEACON",6))beaconResponce(address);
          if(0 == strncmp(buffer,"USER=" ,5))userResponse  (address,  buffer, readCount);
          if(0 == strncmp(buffer,"MSG="  ,4))msgResponse   (address,  buffer, readCount);
      }
}
