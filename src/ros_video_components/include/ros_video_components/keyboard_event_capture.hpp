//QT
#include <QObject>
#include <QKeyEvent>

class Keyboard_Event_Capture : public QObject {
    Q_OBJECT



	public:
        Keyboard_Event_Capture(QObject *parent = 0);
        void keyPressEvent (QKeyEvent * key);
};
