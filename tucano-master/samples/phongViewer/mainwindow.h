#ifndef __MAINWINDOW__
#define __MAINWINDOW__

#include <QMainWindow>
#include "glwidget.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initialize( void );

private:
    Ui::MainWindow *ui;
    void createActions();
    QString FileName;
    QString sampleDir = "../sample/models/";

protected:
    void keyPressEvent(QKeyEvent *ke);

private slots:

    void open();
    void close();
    void quit();
    void about();
    void aboutqt();

};

#endif // MAINWINDOW
