%{
#include "mtpsocket.h"
%}

%rename(mtpsocket) MtpSocket;
class MtpSocket : public QIODevice {
public:
    MtpSocket(QObject* parent = 0);

    %rename(set_host) setHost(const QString& h);
    %rename(set_port) setPort(int p);
    %rename(set_login) setLogin(const QString& h);
    %rename(set_passwd) setPasswd(const QString& h);

    %rename(get_login) getLogin();
    %rename(get_passwd) getPasswd();

    %rename(connet_to_host) connectToHost();
    %rename(send_login) sendLogin();
    %rename(send_passwd) sendPasswd();

    void setHost(const QString& h);
    void setPort(int p);
    void setLogin(const QString& l);
    void setPasswd(const QString& p);

    QString getLogin();
    QString getPasswd();

    void connectToHost();
    void sendLogin();
    void sendPasswd();
};	// end of class MtpSocket
