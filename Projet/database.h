#ifndef DATABASE_H
#define DATABASE_H
#include <QCoreApplication>
#include <QtSql>
#include <QString>
#include <string>
#include <iostream>
#include <QDebug>


#define q2c(string) string.toStdString()

using namespace std;

class Database
{
    QSqlDatabase db;
       string databaseName;

       bool open()
       {
           return this->db.open();
       }
       void close()
       {
           db.close();
       }
   public:
       QSqlQuery query(string q);
       Database(string path, string dbname="QSQLITE");
       ~Database(){db.close();}

       class SaverLoader //gere sauvegarde et chargement de la bdd
       {

           Database& db;
           void init();

       public:
           SaverLoader(Database& database):db(database){}
           void save();
           void load();
       };

       void save()
       {
           SaverLoader(*this).save();
       }

       void load()
       {
           SaverLoader(*this).load();
       }
   };

   class DatabaseException : public std::exception
   {
   protected :
       std::string info;
   public:
       DatabaseException(const std::string& i="") throw() :info(i) {}
       const char* what() const throw()
       {
           return info.c_str();
       }
       ~DatabaseException()throw() {}

};

#endif // DATABASE_H
