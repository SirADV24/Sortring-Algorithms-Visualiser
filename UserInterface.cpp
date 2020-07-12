#include "UserInterface.h"

#define window_height 800
#define window_width 1360
#define background_color QColor{208, 211, 212 }
#define button_color QColor{208, 211, 212 }
#define button_chosen QColor{38, 166, 154 }
#define button_font QFont{"Helvetica",10, QFont::Bold }


UserInterface::UserInterface
(Service srv, QWidget *parent) : QWidget(parent), srv{srv}
{
    //TODO check flags for gvievw
    ui.setupUi(this);
    this->setFixedSize(window_width, window_height);
    this->item_counter = this->srv.get_size();
    this->main_layout = new QVBoxLayout{ this };
    this->setWindowTitle(QString::fromStdString("Sort Algorythm Visualiser"));

    // this order
    this->init_menu();
    this->scene_setup();

    this->handle_new_array();
    this->print_bars();
    this->make_connection();
    this->change_size_label(this->item_counter);

    this->set_bubble_sort();
    this->speed = 100;
}

UserInterface::~UserInterface()
{
    delete this->size_slider;
    delete this->speed_slider;
    delete this->main_layout;
    delete this->bubble_sort;
    delete this->selection_sort;
    delete this->heap_sort;
    delete this->quick_sort;
    delete this->new_array;
    delete this->start;
}

void UserInterface::scene_setup()
{
    this->scene = new QGraphicsScene{};
    ui.animation_window->setScene(this->scene);
    ui.animation_window->setBackgroundBrush(QBrush(background_color));
    ui.animation_window->setRenderHint(QPainter::Antialiasing); //smooth things up
    ui.animation_window->setAlignment(Qt::AlignBottom);
    ui.animation_window->setFixedSize(this->size());
    
    
    QWidget* scene_widget = new QWidget{};
    QHBoxLayout* scene_layout = new QHBoxLayout{ scene_widget };
    scene_layout->addWidget(scene_widget);
    this->main_layout->addWidget(scene_widget);
}

void UserInterface::init_menu()
{
    QWidget* menu_widget = new QWidget{this};
    QHBoxLayout* menu_layout = new QHBoxLayout{menu_widget};

    menu_widget->setFixedHeight(this->size().height() / 10);

    this->size_slider = new QSlider{Qt::Horizontal};
    QLabel* slider_name = new QLabel{ "Array size " };
    slider_name->setFont(button_font);
    menu_layout->addWidget(slider_name);
    menu_layout->addWidget(this->size_slider);

    this->speed_slider = new QSlider{ Qt::Horizontal };
    QLabel* speed_slider_name = new QLabel{ "Speed" };
    speed_slider_name->setFont(button_font);
    menu_layout->addWidget(speed_slider_name);
    menu_layout->addWidget(this->speed_slider);
    
    this->bubble_sort = new QPushButton("Bubble sort");
    this->selection_sort = new QPushButton("Selection sort");
    this->heap_sort = new QPushButton("Heap Sort");
    this->quick_sort = new QPushButton("Quick Sort");
    this->start = new QPushButton("START");
    this->new_array = new QPushButton("New array");


    QPalette pal = this->bubble_sort->palette();
    pal.setColor(QPalette::Button, button_color);

    this->bubble_sort->setFlat(true);
    this->bubble_sort->setFont(button_font);
    this->bubble_sort->setPalette(pal);

    this->selection_sort->setFlat(true);
    this->selection_sort->setFont(button_font);
    this->selection_sort->setPalette(pal);

    this->heap_sort->setFlat(true);
    this->heap_sort->setFont(button_font);
    this->heap_sort->setPalette(pal);

    this->quick_sort->setFlat(true);
    this->quick_sort->setFont(button_font);
    this->quick_sort->setPalette(pal);

    this->start->setFlat(true);
    this->start->setFont(button_font);
    this->start->setPalette(pal);

    this->new_array->setFlat(true);
    this->new_array->setFont(button_font);
    this->new_array->setPalette(pal);

    menu_layout->addWidget(this->bubble_sort);
    menu_layout->addWidget(this->selection_sort);
    menu_layout->addWidget(this->heap_sort);
    menu_layout->addWidget(this->quick_sort);
    menu_layout->addWidget(this->new_array);
    menu_layout->addWidget(this->start);

    ui.size_label->setFont(button_font);
    ui.size_label_nr->setFont(button_font);
    ui.steps_label->setFont(button_font);;
    ui.nr_steps_label->setFont(button_font);;

    ui.algorythm_name_label->setFont(button_font);
    ui.algorythm_name->setFont(button_font);

    this->main_layout->addWidget(menu_widget);
}


void UserInterface::make_connection()
{
    QObject::connect(this->size_slider, &QSlider::valueChanged,
        this, &UserInterface::handle_slider_changed);
    QObject::connect(this->speed_slider, &QSlider::valueChanged,
        this, &UserInterface::handle_speed_slider_changed);
    QObject::connect(this->new_array, &QPushButton::pressed, 
        this, &UserInterface::handle_new_array);
    QObject::connect(this->start, &QPushButton::pressed,
        this, &UserInterface::handle_start);
    QObject::connect(this->bubble_sort, &QPushButton::pressed,
        this, &UserInterface::set_bubble_sort);
    QObject::connect(this->selection_sort, &QPushButton::pressed,
        this, &UserInterface::set_selection_sort);
    QObject::connect(this->quick_sort, &QPushButton::pressed,
        this, &UserInterface::set_quick_sort);
    QObject::connect(this->heap_sort, &QPushButton::pressed,
        this, &UserInterface::set_heap_sort);
}

void UserInterface::handle_slider_changed()
{
    auto size = this->size_slider->value() * 120 / 100  + 10;
    this->item_counter = size;

    this->srv.change_size(item_counter);
    QApplication::processEvents();
    this->change_size_label(this->item_counter);
    this->handle_new_array();
}

void UserInterface::handle_speed_slider_changed()
{
    auto size = 100 - this->speed_slider->value();
    if (size < 0)
        size = 0;

    this->speed = size;
}

void UserInterface::handle_new_array()
{
    this->change_size_label(this->item_counter);

    int bar_width = this->size().width() / (this->item_counter * 2);
    // might be bad change this 
    if (bar_width < 10)
        bar_width = 10;
    // focus the bars on the middle
    int position_x = this->size().width() / 2 -
        this->item_counter / 2 * bar_width;
    int position_y = window_height - window_height / 5; // always the same


    this->srv.generate_new_bars(bar_width, position_x, position_y);
    this->print_bars();
    this->scene->update();

}

void UserInterface::handle_start()
{
    this->change_size_label(this->item_counter);

    this->lock_menu(false);

    std::vector<std::pair<int, int>> switches{};
    switch (this->swap_style) {
    case 0:
        switches = this->srv.buble_sort(); break;
    case 1:
        switches = this->srv.selection_sort(); break;
    case 2:
        switches = this->srv.heap_sort(); break;
    case 3:
        switches = this->srv.quick_sort(); break;
    default:
        break;
    }

    this->start_sorting(switches);

    this->lock_menu(true);
}

void UserInterface::lock_menu(bool how)
{
    this->size_slider->setEnabled(how);
    this->bubble_sort->setEnabled(how);
    this->selection_sort->setEnabled(how);
    this->heap_sort->setEnabled(how);
    this->quick_sort->setEnabled(how);
    this->new_array->setEnabled(how);
    this->start->setEnabled(how);

}

void UserInterface::change_step_label(int size)
{
    ui.nr_steps_label->setText(QString::fromStdString(std::to_string(size)));
}

void UserInterface::change_size_label(int size)
{
    ui.size_label_nr->setText(QString::fromStdString(std::to_string(srv.get_all().size())));
}

void UserInterface::change_current_algorythm_name(std::string name)
{
    ui.algorythm_name->setText(QString::fromStdString(name));
}

void UserInterface::start_sorting(std::vector<std::pair<int, int>> moves)
{
    this->change_step_label();
    std::pair<int, int> last_move{ -1, -1 };
    for (int i = 0; i < moves.size(); i++)
    {
        if (last_move != std::make_pair(-1, -1))
        {
            this->srv.switch_color(last_move.first);
            this->srv.switch_color(last_move.second);
        }
        last_move = moves.at(i);
        this->srv.switch_color(last_move.first);
        this->srv.switch_color(last_move.second);

        this->srv.swap_positions(moves.at(i).first, moves.at(i).second);
        this->scene->update();
        this->change_step_label(i);
        this->delay();
    }
    if (last_move != std::make_pair(-1, -1))
    {
        this->srv.switch_color(last_move.first);
        this->srv.switch_color(last_move.second);
        this->scene->update();
        QApplication::processEvents();
    }

}

void UserInterface::delay()
{
    // might change this , very cpu demanding 
    if (this->speed < 1)
    {
        QApplication::processEvents();
        return;
    }
    QTime dieTime = QTime::currentTime().addMSecs(this->speed);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 1);
}

void UserInterface::set_bubble_sort()
{
    this->swap_style = 0;
    this->change_current_algorythm_name("Bubble sort");
}

void UserInterface::set_selection_sort()
{
    this->swap_style = 1;
    this->change_current_algorythm_name("Selection sort");
}

void UserInterface::set_heap_sort()
{
    this->swap_style = 2;
    this->change_current_algorythm_name("Heap sort");
}

void UserInterface::set_quick_sort()
{
    this->swap_style = 3;
    this->change_current_algorythm_name("Quick sort");
}

void UserInterface::print_bars()
{
    if (this->srv.get_all().size() == 0)
        this->handle_new_array();

    for(auto* bar:this->srv.get_all())
        this->scene->addItem(bar);
}

