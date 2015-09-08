#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <utils/qttrackballwidget.hpp>

#include <phongshader.hpp>

class GLWidget : public Tucano::QtTrackballWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    void initialize();
    void paintGL();

signals:

private:
    Effects::Phong *phong;

public slots:
};

#endif // GLWIDGET_H
