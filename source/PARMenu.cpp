#include "PARMenu.hpp"

PARMenu::PARMenu(bool font_load_success, sf::Font &text_font) : OptionSelectionMenu(){
	this->initialize(font_load_success, text_font);
}

PARMenu::~PARMenu() {
}

void PARMenu::class_setup() {
	this->num_elements_per_screen = 5;
	this->min_elements_text_scaling_factor = num_elements_per_screen + 2;
	this->width_factor_menu = 16;
	this->width_divisor_menu = 9;
	this->base_height_factor_menu = 12;
	this->base_height_divisor_menu = 6;
	this->min_text_size = 0.3;
	this->max_width_slack = 1.1;
	this->menu_color = sf::Color(30, 30, 60, 192);
	this->title = this->base_name;
	this->show_back_x = true;
	this->show_x = false;
	this->show_title = true;
}

void PARMenu::setup_title(std::string added_name) {
	this->title = added_name + (added_name != "" ? " " : "") + this->base_name;
}

void PARMenu::insert_data(std::vector<const PARData*>* possible_pars) {
	this->possible_pars = possible_pars;
	this->prepare_options();
}

void PARMenu::reset_output_option() {
	this->selected_index = PAR_MENU_NO_ACTION;
}

void PARMenu::set_output_option(int index) {
	if(index == -1)
		this->selected_index = PAR_MENU_BACK;
	else
		this->selected_index = index;
}

int PARMenu::get_num_options() {
	return (*this->possible_pars).size();
}

std::string PARMenu::get_string_option(int index) {
	return (*this->possible_pars)[index]->name;
}

void PARMenu::prepare(float menu_scaling_factor, int view_size_x, int view_size_y, int current_par) {
	int num_pages = this->get_num_pages();
	if(this->future_data.page >= num_pages)
		this->future_data.page = num_pages - 1;
	int start = this->future_data.page * this->num_elements_per_screen;
	for(int i = 0; i < this->num_elements_per_screen; i++) {
		int index = i + this->elements_start_id;
		if(!this->future_enabled_labels[index])
			continue;
		int par_index = start + i;
		if(par_index == current_par)
			this->labels[index]->setText("<" + (*this->possible_pars)[par_index]->name + ">");
		else
			this->labels[index]->setText((*this->possible_pars)[par_index]->name);
	}
	this->base_prepare(menu_scaling_factor, view_size_x, view_size_y);
}
