# !/bin/sh
# export QMAKESPEC=/opt/qt-everywhere-opensource-src-4.7.3/mkspecs/qws/linux-arm-gnueabi-g++
# make distclean
echo "./gui.sh [type] type = cd/dd/cr(cross debug/desk debug/cross releas), other default is cr"

if [ $# -ne 1 ];
then
	echo "param is default"
	exit
# else
	# echo $1
fi

if [ "$1"x = "cd"x ];
then
	echo "cross debug project"
	# export QMAKESPEC=/opt/qt-everywhere-opensource-src-4.7.3/mkspecs/qws/linux-arm-gnueabi-g++
	# QMAKE=/opt/qt-everywhere-opensource-src-4.7.3/bin/qmake
	QMAKE=/opt/qt-arm-4.8.3/bin/qmake
	CONFIG="CONFIG+=Debug"
elif [ "$1"x = "dd"x ];
then
	echo "desk debug project"
  # QMAKE=/home/mengqp/local/pro/qtsdk-2010.05/qt/bin/qmake
	QMAKE=/usr/bin/qmake-qt4
	CONFIG="CONFIG+=Debug"
elif [ "$1"x = "cr"x ];
then
	echo "cross release project"
	# export QMAKESPEC=/opt/qt-everywhere-opensource-src-4.7.3/mkspecs/qws/linux-arm-gnueabi-g++
	# QMAKE=/opt/qt-everywhere-opensource-src-4.7.3/bin/qmake
	# export QMAKESPEC=/opt/qt-arm-4.8.3/mkspecs/qws/linux-omapl138-g++/
	QMAKE=/opt/qt-arm-4.8.3/bin/qmake
	CONFIG="CONFIG+=release"
else
	echo "cross release project"
	# QMAKE=/opt/qt-everywhere-opensource-src-4.7.3/bin/qmake
	QMAKE=/opt/qt-arm-4.8.3/bin/qmake
	CONFIG="CONFIG+=release"
fi

$QMAKE -project -Wall  -o  svgui.pro -after "TARGET=svgui" $CONFIG  "OBJECTS_DIR = build/obj" "MOC_DIR = build/moc"  "QT += gui core svg"
$QMAKE -makefile svgui.pro   -o Makefile

make
