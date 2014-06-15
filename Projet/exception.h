#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QString>

class Exception{
public:
    Exception(const QString& message, const QString &f="na", unsigned int l=0): info(message),file(f),line(l){}
    QString getInfo() const { return info; }
#ifndef NDEBUG
    // retourne le fichier dans lequel cettte exception a été levée.
    QString getFile() const { return file; }
    // retourne la ligne du fichier à laquelle cette exception a été levée.
    unsigned int getLine() const { return line; }
#endif
private:
    QString info;
    QString file;
    unsigned int line;

};

#endif // EXCEPTION_H
