#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <string>
#include <QApplication>
#include <QFileInfo>
#include <QTextStream>
#include <QFileDialog>
#include <QMainWindow>
#include <QLabel>
#include <QMessageBox>
class Node
    {
    public:
        int key;
        char symbol;
        Node* left, * right;

        Node()
        {
            left = right = NULL;
        }

        Node(Node* L, Node* R)
        {
            left = L;
            right = R;
           this-> key = L->key + R->key;
        }
    };

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    QString on_pushButton_clicked();

    void on_pushButton_2_clicked();


    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
};



    struct MyCompare
    {
        bool operator()(const Node* l, const Node* r) const { return l->key < r->key; }
    };
#endif // MAINWINDOW_H
