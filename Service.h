
#include "UiBar.h"

class Service {

private:
	std::vector<Bar*> bars;
	int actual_size;

public:
	Service(int actual_size);
	Service();
	~Service();

	std::vector<Bar*> get_all();
	int get_size();
	void swap_positions(int i, int j);
	void switch_color(int position);

	void generate_new_bars
	(int bar_width, int position_x, int position_y);

	void clear_bars();
	void change_size(int counter);

	std::vector<std::pair<int, int>> buble_sort(); 
	std::vector<std::pair<int, int>> selection_sort();
	std::vector<std::pair<int, int>> heap_sort();
	std::vector<std::pair<int, int>> quick_sort();

};