#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <utils/qttrackballwidget.hpp>
#include <phongshader.hpp>
#include <mesh.hpp>
#include <pointcloud.h>
#include <emitter.h>
#include <QTimer>

class GLWidget : public Tucano::QtTrackballWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    void initialize();
    void paintGL();

    Effects::Phong *phong;
    PointCloud pointCloud;

    Emitter emitter;

    QTimer *timer;


signals:

public slots:
    void loop();
};

#endif // GLWIDGET_H
