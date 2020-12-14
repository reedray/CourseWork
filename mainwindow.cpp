#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
bool isOpen=0;


Node *root1;
QVector<bool> code;
QMap<char, QVector<bool> > table;
void BuildTable(Node* root)
{
    if (root->left != NULL)
    {
        code.push_back(0);
        BuildTable(root->left);
    }

    if (root->right != NULL)
    {
        code.push_back(1);
        BuildTable(root->right);
    }

    if (root->left == NULL && root->right == NULL)
    {
        table[root->symbol] = code;

    }
    if (code.size() != 0)
        code.pop_back();

}


QFile file;
QString str = nullptr;
QString MainWindow::on_pushButton_clicked()
{


    str=QFileDialog::getOpenFileName(0,"Выбор файла","","*.txt");
        if(str!=nullptr)
        {

            isOpen=1;
        }
        return str;

}

void MainWindow::on_pushButton_2_clicked()
{
    if(!isOpen)
    {
        QMessageBox::critical(this,"Предупреждение","Выберите файл");
        return;

    }
    if(str==nullptr)
    {
        return;
    }
    file.setFileName(str);
    file.open(QIODevice::ReadOnly);


    QMap<char, int> map;
            char ch;
            while (file.getChar(&ch))
            {
                map[ch]++;
            }

           static  QVector<Node*> list;
                for (QMap<char, int>::iterator itr = map.begin(); itr != map.end(); ++itr)
                {
                    Node* ptr = new Node;
                    ptr->symbol = itr.key();
                    ptr->key = itr.value();
                    list.push_back(ptr);



                }
                while (list.size() != 1)
                    {

                      std::sort(list.begin(),list.end(),MyCompare());
                        Node* SonL = list.front();
                        list.erase(list.begin());
                        Node* SonR = list.front();
                        list.erase(list.begin());


                        Node* parent = new Node(SonL, SonR);

                        list.push_back(parent);


                    }


               Node* root = list.front();
               root1=root;
                    BuildTable(root);

                    file.close();
                    file.open(QIODevice::ReadOnly);
                    QFile file1;
                    file1.setFileName("newArchive.myArchive");
                    file1.open(QIODevice::WriteOnly);
                    QTextStream stream(&file1);
                        int count = 0; char buf = 0;
                        char symb;
                        while (file.getChar(&symb))
                        {
                            QVector<bool> x = table[symb];

                            for (int i = 0; i < x.size(); i++)
                            {
                                buf = buf | x[i] << (7 - count);
                                count++;
                                  if (count == 8)
                                {
                                    count = 0;
                                    stream<<buf;
                                    buf = 0;
                                }
                            }
                        }
                        file1.close();
                        file.close();
                        ui->pushButton_2->hide();



}




void MainWindow::on_pushButton_3_clicked()
{
    QString str1=QFileDialog::getOpenFileName(0,"Выбор файла","","*.myArchive");
      QFile file2;
      file2.setFileName(str1);
    if(! file2.open(QIODevice::ReadOnly))
       { QMessageBox::critical(this,"Предупреждение","Выберите файл");
    return;
    }

    QTextStream out(stdout);

    Node* temp =root1;
    int count = 0;
    char byte;
    file.open(QIODevice::ReadOnly);
    int size=file2.size();
    file2.getChar(&byte);
    size--;

    QFile file3;
    file3.setFileName("Archive.txt");
    file3.open(QIODevice::WriteOnly);
    QTextStream zapis(&file3);



        while (size!=0)
            {
                bool b = byte & (1 << (7 - count));
                if (b)
                temp = temp->right;
                else
                temp = temp->left;
                if (temp->left == NULL && temp->right == NULL)
                {
                   zapis << temp->symbol;
                   temp = root1;
                }
                count++;
                if (count == 8)
                {
                    count = 0;
                    file2.getChar(&byte);
                    size--;


                }
            }
    file2.close();
    file3.close();
    file.close();
    hide();

}
