
/*! \file stdafx.h
    \brief �������������� ���������������� ���������.
*/


#include <cmath>
#include <ctime> 
#include <cstdio>
#include <cstdlib>
#include <exception>

#ifdef __unix__ 
  #include <unistd.h>
#elif defined _WIN32 
  #include <windows.h>
#endif


#pragma warning(push)

#pragma warning(disable:4127)
#pragma warning(disable:4251)

#include <QAction>
#include <QApplication>
#include <QCheckBox> 
#include <QColor>
#include <QComboBox>
#include <QCoreApplication> 
#include <QDate>
#include <QDebug>
#include <QDomElement>
#include <QFile>
#include <QFileDialog>
#include <QGraphicsItem> 
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHash> 
#include <QIcon>
#include <QLabel>
#include <QLayout> 
#include <QLine>
#include <QLineEdit>
#include <QList> 
#include <QListIterator>
#include <QMenu>
#include <QMessageBox>
#include <QPixmap>
#include <QPoint> 
#include <QPointF>
#include <QPushButton>
#include <QRect> 
#include <QRectF>
#include <QString>
#include <QTextCodec>
#include <QTextEdit> 
#include <QTimer>
#include <QToolBar>
#include <QThread>
#include <QValidator>
#include <QVariant> 
#include <QVector>
#include <QWheelEvent>


#include <QtGui/QMainWindow>


#pragma warning(pop)

class GraphWidget;
class FreeComment;
class Lifeline;
class Message;
class Sumleditor;
class SumleditorClass;


/** ���� ��������� "��������������" */
static QColor warning_color;
/** ���� ��������� "������" */
static QColor error_color;
/** ���� ��������� "��������" */
static QColor attention_color;
/** ���� ��������� "�����������" */
static QColor normal_color;

struct ElementMetaInfo;

enum Action;


