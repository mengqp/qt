#include "xmlstream.h"
#include <QFile>
#include <QDebug>

XmlStream::XmlStream()
{
}

XmlStream::~XmlStream()
{
}

bool XmlStream::readFile(QString filename)
{
    bool bRtn = FALSE;
    QFile file(filename);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        printf("file open error\n");
        return false;
    }

    m_reader.clear();
    m_reader.setDevice(&file);

    bRtn = readContent();
    file.close();

    return bRtn;
}

bool XmlStream::readString(QString str)
{
    bool bRtn = FALSE;
    m_reader.clear();
    m_reader.addData(str);

    bRtn = readContent();

    return bRtn;
}

bool XmlStream::readContent(void)
{
    m_reader.readNext();
    while (!m_reader.atEnd()) {
        if (m_reader.isStartElement()) {
            if (m_reader.name() == "root") {
                readRoot();
            }
            else {
                m_reader.raiseError(QObject::tr("Not a root file"));
            }
        }
        else {
            m_reader.readNext();
        }
    }

    if (m_reader.hasError()) {
        printf("m_reader has error\n");
        return false;
    }

    return true;
}

bool XmlStream::readRoot(void)
{
    bool bRtn = true;

    m_reader.readNext();
    while (!m_reader.atEnd()) {
        if (m_reader.isEndElement()) {
            m_reader.readNext();
            break;
        }

        if (m_reader.isStartElement()) {
            if (m_reader.name() == "common") {
                bRtn = readCommon();
            }
            else if (m_reader.name() == "data") {
                bRtn = readData();
            }
            else {
                bRtn = skipUnknown();
            }
        }
        else {
            m_reader.readNext();
        }

        if (!bRtn)
            return bRtn;
    }

    return true;
}

bool XmlStream::readCommon(void)
{
    m_reader.readNext();
    while (!m_reader.atEnd()) {
        if (m_reader.isEndElement()) {
            m_reader.readNext();
            break;
        }

        if (m_reader.isStartElement()) {
            qDebug() << m_reader.name();
            if (m_reader.name() == "fac_no") {
                int fac_no = m_reader.readElementText().toInt();
                printf("fac_no=%d\n", fac_no);
            }
            else if (m_reader.name() == "quest_id") {
                int quest_id = m_reader.readElementText().toInt();
                printf("quest_id=%d\n", quest_id);
            }
            else if (m_reader.name() == "type") {
                QString type = m_reader.readElementText();
                qDebug() << "type =" << type;
            }
            else {
                skipUnknown();
            }
        }

        m_reader.readNext();
    }
    return true;
}

bool XmlStream::readData(void)
{
    foreach (QXmlStreamAttribute var, m_reader.attributes().toList()) {
        if (var.name() == "operation") {
            qDebug() << "operation=" << var.value();
        }
    }

    m_reader.readNext();

    while (!m_reader.atEnd()) {
        if (m_reader.isEndElement()) {
            m_reader.readNext();
            break;
        }

        if (m_reader.isStartElement()) {
            qDebug() << m_reader.name();
            if (m_reader.name() == "value") {
                printf("list num=%d\n", m_reader.attributes().size());
                foreach (QXmlStreamAttribute var,
                         m_reader.attributes().toList()) {
                    if (var.name() == "id") {
                        qDebug() << "id=" << var.value();
                    }
                }
                int value = m_reader.readElementText().toInt();
                printf("value=%d\n", value);
            }
            else {
                skipUnknown();
            }
        }

        m_reader.readNext();
    }
    return true;
}

bool XmlStream::skipUnknown(void)
{
    m_reader.readNext();
    while (!m_reader.atEnd()) {
        if (m_reader.isEndElement()) {
            m_reader.readNext();
            break;
        }

        if (m_reader.isStartElement()) {
            skipUnknown();
        }
        else {
            m_reader.readNext();
        }
    }
    return true;
}

bool XmlStream::writeFile(QString filename)
{
    QXmlStreamWriter writer;
    QFile file(filename);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        printf("open error\n");
        return false;
    }
    try {
        QString dtd;
        QXmlStreamWriter writer_dtd(&dtd);

        writer_dtd.writeStartElement("dtd");
        writer_dtd.writeCharacters("This is a Test dtd String!");
        writer_dtd.writeEndElement();


        writer.setDevice(&file);
        writer.setAutoFormatting(true);
        //文档开始
        writer.writeStartDocument();

        //写文档内容
        writer.writeStartElement("BQTable");
        writer.writeAttribute("att", "test");
        writer.writeStartElement("BQTitle");
        writer.writeAttribute("id", "1_1");
        writer.writeCharacters("This is a Test String!");
        writer.writeEndElement();
		writer.writeDTD(dtd);
		writer.writeEndElement();

        //文档结束
        m_writer.writeEndDocument();
    } catch (...) {
        return false;
    }
    return true;
}

bool XmlStream::writeString(QString *pStr)
{
    pStr->clear();
    QString dtd;
    QXmlStreamWriter writer_dtd(&dtd);
    //文档开始
    writer_dtd.writeStartDocument();

    writer_dtd.writeStartElement("dtd");
    writer_dtd.writeCharacters("This is a Test dtd String!");
    writer_dtd.writeEndElement();

    //文档结束
    writer_dtd.writeEndDocument();

    QXmlStreamWriter writer(pStr);

    writer.setAutoFormatting(true);
    //文档开始
    writer.writeStartDocument();

    //写文档内容
    writer.writeStartElement("BQTable");
    writer.writeAttribute("att", "test");
    writer.writeStartElement("BQTitle");
    writer.writeAttribute("id", "1_1");
    writer.writeCharacters("This is a Test String!");
    writer.writeEndElement();
    writer.writeDTD(dtd);

    writer.writeEndElement();

    //文档结束
    writer.writeEndDocument();

    return true;
}
