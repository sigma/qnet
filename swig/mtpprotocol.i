%{
#include "mtpprotocol.h"
%}

%rename(mtpprotocol) MtpProtocol;
class MtpProtocol {

    %rename(line_available) lineAvailable;
    %rename(read_line) readLine;
    %rename(install_io) installIO;
    %rename(uninstall_io) uninstallIO;
    %rename(write_line) writeLine;

public:
    MtpProtocol(QObject *parent = 0);

    bool lineAvailable() const;
    QString readLine();
    void installIO(QIODevice* CONSUMED);
    void uninstallIO();
    void writeLine(const QString& txt);

private:
    QIODevice *io;
};	// end of class MtpProtocol
