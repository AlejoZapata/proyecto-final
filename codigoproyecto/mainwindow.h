#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QMainWindow>
#include <QPushButton>
#include <QList>
#include <QImage>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void loadScene(int index);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QList<QImage> images;
    int currentSceneIndex;
    QList<QString> imageFileNames;
};

#endif // MAINWINDOW_H
