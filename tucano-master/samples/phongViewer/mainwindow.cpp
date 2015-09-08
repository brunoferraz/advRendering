#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QDebug"
/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
/**
 * @brief MainWindow::initialize
 * This function have a hard code mesh file and a directory of
 * shader
 * @todo Motify application to start winthout mesh file loaded.
 */
void MainWindow::initialize( void )
{
    /**
     ** Add a Mesh File and Shader Dir into a private var
     **/
    ui->glwidget->setMeshFile("../samples/models/toy.ply");
    ui->glwidget->setShaderDir("../effects/shaders/");
    ui->glwidget->initialize();
    /**
     * @brief createActions
     * Add this function to create a callback (events) to menu
     */
    createActions();
}

void MainWindow::keyPressEvent(QKeyEvent *ke)
{
    int key = ke->key();
    int modifiers = ke->modifiers();

    if (modifiers == 0 && key == Qt::Key_Escape)
    {
        close();
    }

    ke->accept();
}

/**
 * @brief MainWindow::createActions
 * This function only create a callback to menu events
 * @todo create content to About and close file
 */
void MainWindow::createActions(){
    connect(ui->actionQuit          , SIGNAL(triggered())   , this  , SLOT(quit())          );
    connect(ui->actionOpen          , SIGNAL(triggered())   , this  , SLOT(open())          );
    connect(ui->actionAbout         , SIGNAL(triggered())   , this  , SLOT(about())         );
    connect(ui->actionAboutQt       , SIGNAL(triggered())   , this  , SLOT(aboutqt())         );
}

/**
 * @brief MainWindow::close
 * Close a Mesh File (not yet implemented)
 */
void MainWindow::close(){
}

/**
 * @brief MainWindow::quit
 * Quit from application
 */
void MainWindow::quit(){
     qApp->quit();
}

/**
 * @brief MainWindow::about
 * Show a about window (not yet implemented)
 */
void MainWindow::about(){
}

/**
 * @brief MainWindow::aboutqt
 * Show the about window about QT
 */
void MainWindow::aboutqt(){
        qApp->aboutQt();
}

/**
 * @brief MainWindow::open
 * Open new Mesh File
 */
void MainWindow::open(){
QFileDialog     *fd;
QString         filter;

  fd = new QFileDialog();
  fd->setDirectory(sampleDir);
  FileName = fd->getOpenFileName(this,tr("Open Mesh Files"),sampleDir,"Mesh Files ( *.ply)", &filter);
  if (!FileName.isEmpty()){
    ui->glwidget->setMeshFile(FileName.toStdString());
    ui->glwidget->initialize();
  }
}

