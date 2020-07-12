#pragma once
#include "Service.h"
#include <QtWidgets/QWidget>
#include <iostream>
#include <vector>
#include "ui_UserInterface.h"
#include <qlayout.h>
#include <QtCore>
#include <QtGui>
#include <QPainter> 
#include <QDebug>
#include <QSlider>
#include <qformlayout.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <random>
#include <iostream>
#include <windows.h>
#include <qtime>
#include <qpalette.h>

class UserInterface : public QWidget
{
public:
    UserInterface(Service srv, QWidget *parent = Q_NULLPTR);
    ~UserInterface();
private:
    Ui::UserInterfaceClass ui;
    Service srv;
    int speed;

    // PRINT SWAPs NUMBERS - <idea>


private:
    int swap_style;
    QGraphicsScene* scene;
    QSlider* size_slider;
    QSlider* speed_slider;
    QVBoxLayout* main_layout;
    QPushButton* bubble_sort;
    QPushButton* selection_sort;
    QPushButton* heap_sort;
    QPushButton* quick_sort;
    QPushButton* new_array;
    QPushButton* start;

private:
    int item_counter;
    void scene_setup();
    void print_bars();
    void init_menu();
    void make_connection();


    //handlers

    void handle_slider_changed();
    void handle_speed_slider_changed();
    void handle_new_array();
    void handle_start();
    void lock_menu(bool);
    void change_step_label(int size = 0);
    void change_size_label(int size);
    void change_current_algorythm_name(std::string name);
    void start_sorting(std::vector<std::pair<int, int>>);
    void delay();


    // set sorting style
    void set_bubble_sort();
    void set_selection_sort();
    void set_heap_sort();
    void set_quick_sort();

};

