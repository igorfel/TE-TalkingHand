#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMessageBox>
#include <QString>
#include <QFile>
//#include <QTimer>

#include <Communication/client.h>
#include <SistemasdeControle/headers/primitiveLibs/LinAlg/matrix.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    LinAlg::Matrix<double> importData(const char* local);
    void exportData(const char* local);

    void setAudio();

private slots:
    void on_Conectar_clicked();
    void on_Desconectar_clicked();
    void on_Cadastrar_clicked();
    void on_start_clicked();
    void listenSerialData();
    void on_stop_clicked();
    void onConected();

private:
    Client *wifi;
    Ui::MainWindow *ui;
    QMediaPlayer *player[25];
    LinAlg::Matrix<double> Letras;
    int columDataSize;
    QString LetraJaReconhecida;

    const char* Local = ":/Letras/sounds/Letras.txt";
};

#endif // MAINWINDOW_H
