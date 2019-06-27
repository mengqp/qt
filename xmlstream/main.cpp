#include "xmlstream.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	XmlStream stream;
	// stream.readFile( "/root/code/lang/qt/xmlstream/sample.xml" );
	stream.writeFile( "/root/code/lang/qt/xmlstream/test.xml" );

	// QFile f("/root/code/lang/qt/xmlstream/sample.xml");
	// if (!f.open(QFile::ReadOnly | QFile::Text))
	// {
	// 	printf("open error\n");
	// }
    // QTextStream in(&f);
    // qDebug() << f.size() << endl;
	// QString s = in.readAll();
	// // qDebug() << s << endl << s.size() << endl;

	// stream.readString( s );

	QString sw;
	stream.writeString( &sw );
	qDebug() << sw << endl << sw.size() << endl;



    return a.exec();
}
