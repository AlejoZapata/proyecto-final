#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene),
    currentSceneIndex(0),
    personaje(new Personaje) // Inicializar personaje
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);

    images.append(QImage(":/inicio/Inicio.jpg"));
    images.append(QImage(":/escenarios/barco2.jpg"));

    imageFileNames.append(":/Inicio.jpg");
    imageFileNames.append(":/barco2.jpg");

    loadScene(currentSceneIndex);

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);

    // Instalar filtro de eventos
    ui->graphicsView->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete personaje;
    delete scene;
}

void MainWindow::loadScene(int index)
{
    if (index >= 0 && index < images.size())
    {
        QImage img = images[index];

        scene->clear();

        QPixmap pixmap = QPixmap::fromImage(img);
        pixmap = pixmap.scaled(ui->graphicsView->size(), Qt::KeepAspectRatio);

        scene->addPixmap(pixmap);

        scene->setSceneRect(pixmap.rect());

        qDebug() << "Loaded scene index:" << index;

        ui->pushButton->setVisible(index == 0);

        // Añadir de nuevo el personaje a la escena si el índice es 1
        if (index == 1) {
            if (!scene->items().contains(personaje)) {
                personaje->setPos(scene->sceneRect().center()); // Coloca el personaje en el centro de la escena
                scene->addItem(personaje);
            }
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    currentSceneIndex = 1;

    qDebug() << "Button clicked, new scene index:" << currentSceneIndex;

    loadScene(currentSceneIndex);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        personaje->mover(keyEvent);
        return true;
    }
    return QMainWindow::eventFilter(obj, event);
}
