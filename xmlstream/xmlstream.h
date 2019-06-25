/**
 *   \file xmlstream.h
 *   \brief 利用QXmlStream 进行读写的类
 */
#ifndef _XMLSTREAM_H
#define _XMLSTREAM_H

#include <QString>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

class XmlStream {
public:
    XmlStream();
    virtual ~XmlStream();

public:
	// 解析文件
	bool readFile( QString filename );
	// 解析字符串
	bool readString( QString str );
	// 写文件
	bool writeFile( QString filename );
	// 写文件
	bool writeString( QString *pStr );

private:
	bool readContent();
	bool readRoot();
	bool readCommon();
	bool readData();
	bool skipUnknown();

private:
	QXmlStreamReader m_reader;

	QXmlStreamWriter m_writer;
};

#endif /* _XMLSTREAM_H */

// This file is set to c + + mode when you set the following content to the bottom and reopen the file
// Local Variables:
// mode: c++
// End:
