#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->Letras = this->importData(this->Local);
    setAudio();

    this->columDataSize = 11;
    //this->Letras = LinAlg::Zeros<double>(26, columDataSize);
}

MainWindow::~MainWindow()
{
    this->exportData(this->Local);
    delete ui;
}

void MainWindow::on_Conectar_clicked()
{
    this->wifi = new Client(ui->HostInput->currentText(), ui->PortaInput->text().toInt());
    connect(wifi,SIGNAL(connectionSuccessful()),this,SLOT(onConected()));
}

void MainWindow::on_Desconectar_clicked()
{
    this->wifi->DisconnectFromHost();
    QMessageBox msgBox;
    msgBox.setText("Desconectado");
    msgBox.exec();
}

void MainWindow::on_Cadastrar_clicked()
{
    unsigned int * data = this->wifi->dataReceived();

    //int temp = ui->comboBox->currentIndex();
    for (int i = 0; i < this->columDataSize; ++i)
    {    
        this->Letras(ui->comboBox->currentIndex()+1, i+1) = data[2*i] + 256*data[2*i+1];
    }
    this->exportData(this->Local);
    QMessageBox msgBox;
    msgBox.setText("Letra cadastrada");
    msgBox.exec();
}

void MainWindow::on_start_clicked()
{
    connect(this->wifi, SIGNAL(hasReadData()), this, SLOT(listenSerialData()));
    QMessageBox msgBox;
    msgBox.setText("Começando a leitura");
    msgBox.exec();
}

void MainWindow::listenSerialData()
{
    LinAlg::Matrix<double> dados(1,this->columDataSize);
    unsigned int *data = this->wifi->dataReceived();
    int contador = 0;

    for (int i = 0; i < this->columDataSize; ++i)
    {
        dados(1, i+1) = data[2*i] + 256*data[2*i+1];
    }

    for (unsigned i = 0; i < 26; ++i)
    {
        double teste = ((this->Letras.GetRow(i+1) - dados) * ~(this->Letras.GetRow(i+1) - dados))(1,1);
        if(((this->Letras.GetRow(i+1) - dados) * ~(this->Letras.GetRow(i+1) - dados))(1,1) < ui->lineEdit->text().toDouble() )
        {
            player[i]->play();
            continue;
        }

        contador++;
    }
}

void MainWindow::on_stop_clicked()
{
    disconnect(this->wifi, SIGNAL(hasReadData()), this, SLOT(listenSerialData()));
}

void MainWindow::onConected()
{
    QMessageBox msgBox;
    msgBox.setText("Conexão realizada com sucesso!");
    msgBox.exec();
}

///Exporta e importa arquivos
/// Não sei ao certo, mas acho que o arquivo precisa existir,
/// no caso acho que ele não cria um arquivo
LinAlg::Matrix<double> MainWindow::importData(const char *local)
{
    LinAlg::Matrix<double> ret;
    QFile file(local);
    file.open(QIODevice::ReadOnly);

    QTextStream fileStream(&file);
    QString line;
    std::string str;

    while(!fileStream.atEnd())
    {
        line = fileStream.readLine();
        str = str + line.toStdString();
    }

    ret = str.c_str();
    return ret;
}
void MainWindow::exportData(const char *local)
{
    std::string str;
    str << this->Letras;

    QFile file(local);
    QString texto = QString::fromStdString(str);
    file.open(QIODevice::WriteOnly);

    QTextStream text(&file);
    text << texto;

    file.close();
}

void MainWindow::setAudio()
{
    for(unsigned i = 0; i < 25; ++i)
    {
        QString str = "qrc:/Letras/sounds/Letras/" + QString::number(i+1) + ".mp3";
        //std::cout << str.toStdString() << std::endl;

        player[i] = new QMediaPlayer;
        player[i]->setMedia(QUrl(str));
        player[i]->setVolume(100);
    }
}
