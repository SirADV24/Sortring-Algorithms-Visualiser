#include "Service.h"
#include <random>
#include <iostream>
#include <stack>

int get_random() {
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<int> distribution(50, 350);

    return distribution(generator);
}

void my_swap(Bar* first, Bar* second) {
    Bar* temp = first;
    first = second;
    second = temp;
}

Bar* min_bar(Bar* first, Bar* second){return (*first < *second) ? first : second;}

int min_int(int x, int y) { return (x < y) ? x : y; }

Service::Service
(int actual_size): bars{ std::vector<Bar*>{} }, actual_size{actual_size}{}

Service::Service() :
    bars{ std::vector<Bar*>{} }, actual_size{ 10 }{}

Service::~Service()
{

}

std::vector<Bar*> Service::get_all()
{
	return this->bars;
}

int Service::get_size()
{
    return this->actual_size;
}

void Service::swap_positions(int i, int j)
{
    int aux = this->bars.at(i)->get_height();
    this->bars.at(i)->set_height(this->bars.at(j)->get_height());
    this->bars.at(j)->set_height(aux);
}

void Service::switch_color(int position)
{
    this->bars.at(position)->switch_color();
}

void Service::generate_new_bars
(int bar_width, int position_x, int position_y)
{
    this->clear_bars();

    for (int i = 0; i < this->actual_size; ++i)
    {
        Bar* new_bar = new Bar{ position_x, position_y,
            get_random(), bar_width };
        this->bars.push_back(new_bar);
        position_x += bar_width;
    }
}

void Service::clear_bars()
{
    for (auto* bar : bars)
        delete[] bar;
    this->bars.clear();
}

void Service::change_size(int counter)
{
    this->actual_size = counter;
}

std::vector<std::pair<int, int>> Service::buble_sort()
{
    // we will store here every move of the sorting algorythm
    std::vector<std::pair<int, int>> answer{};
    std::vector<Bar*> dummy_bars{};

    for (std::size_t i = 0; i < this->bars.size(); i++)
        dummy_bars.push_back(new Bar{ *this->bars.at(i) });

    bool swapped;

    for (size_t i = 0; i < dummy_bars.size() - 1; i++)
    {
        swapped = false;
        for (size_t j = 0; j < dummy_bars.size() - i - 1; j++)
            if (*dummy_bars[j] > *dummy_bars[j+1])
            {
                answer.push_back(std::make_pair(j, j + 1));
                std::swap(dummy_bars[j], dummy_bars[j + 1]);
                swapped = true;
            }
        if (swapped == false)
            break;
    }

    for (auto* dummy : dummy_bars)
        delete[] dummy;

    return answer;
}

std::vector<std::pair<int, int>> Service::selection_sort()
{
    std::vector<std::pair<int, int>> answer{};
    std::vector<Bar*> dummy_bars{};

    for (std::size_t i = 0; i < this->bars.size(); i++)
        dummy_bars.push_back(new Bar{ *this->bars.at(i) });

    for(size_t i = 0 ; i < dummy_bars.size() - 1; ++i)
        for(size_t j = i + 1; j < dummy_bars.size(); ++j)
            if (*dummy_bars[i] > * dummy_bars[j])
            {
                answer.push_back(std::make_pair(i, j));
                std::swap(dummy_bars[i], dummy_bars[j]);
            }

    for (auto* dummy : dummy_bars)
        delete[] dummy;


    return answer;
}

std::vector<std::pair<int, int>> Service::heap_sort()
{
    std::vector<std::pair<int, int>> answer{};
    std::vector<Bar*> dummy_bars{};

    for (std::size_t i = 0; i < this->bars.size(); i++)
        dummy_bars.push_back(new Bar{ *this->bars.at(i) });

    // we turn dummy_bars into a maxheap
    for (int i = 1; i < dummy_bars.size(); i++)
        if (*dummy_bars[i] > * dummy_bars[(i - 1) / 2])
        {
            int j = i;
            while (*dummy_bars[j] > * dummy_bars[(j - 1) / 2])
            {
                answer.push_back(std::make_pair(j, (j - 1) / 2));
                std::swap(dummy_bars[j], dummy_bars[(j - 1) / 2]);
                j = (j - 1) / 2;
            }
        }

    for (int i = dummy_bars.size() - 1; i > 0; i--)
    {
        std::swap(dummy_bars[0], dummy_bars[i]);
        answer.push_back(std::make_pair(0, i));

        int j = 0, index;

        do
        {
            index = (2 * j + 1);
            if (index >= i)
                break;

            // if left child is smaller than  
            // right child point index variable  
            if (*dummy_bars[index] < *dummy_bars[index + 1] && index < (i - 1))
                index++;
            // if parent is smaller than child  
            // then swapping parent with child  
            if (*dummy_bars[j] < *dummy_bars[index] && index < i)
            {
                std::swap(dummy_bars[j], dummy_bars[index]);
                answer.push_back(std::make_pair(j, index));
            }

            j = index;

        } while (index < i);
    }

    for (auto* dummy : dummy_bars)
        delete[] dummy;


    return answer;
}

std::vector<std::pair<int, int>> Service::quick_sort()
{
    // iterative version
    std::vector<std::pair<int, int>> answer{};
    std::vector<Bar*> dummy_bars{};

    for (std::size_t i = 0; i < this->bars.size(); i++)
        dummy_bars.push_back(new Bar{ *this->bars.at(i) });

    std::stack<int> stack{};
    stack.push(0);
    stack.push(dummy_bars.size() - 1);

    while (!stack.empty())
    {
        auto high = stack.top(); stack.pop();
        auto low = stack.top(); stack.pop();

        //partition
        auto pivot = *dummy_bars[high];
        int i = low - 1;
        for (int j = low; j < high; ++j)
            if (*dummy_bars[j] < pivot)
            {
                i++;
                answer.push_back(std::make_pair(i, j));
                std::swap(dummy_bars[i], dummy_bars[j]);
            }
        std::swap(dummy_bars[i + 1], dummy_bars[high]);
        answer.push_back(std::make_pair(i + 1, high));
        int p = i + 1;

        if (p - 1 > low)
        {
            stack.push(low);
            stack.push(p-1);
        }

        if (p + 1 < high)
        {
            stack.push(p + 1);
            stack.push(high);
        }
    }

    for (auto* dummy : dummy_bars)
        delete[] dummy;


    return answer;
}
