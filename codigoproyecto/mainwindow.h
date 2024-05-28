#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include "personaje.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void on_pushButton_clicked();
    void loadScene(int index);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QList<QImage> images;
    int currentSceneIndex;
    QList<QString> imageFileNames;
    Personaje *personaje;
};

#endif // MAINWINDOW_H
