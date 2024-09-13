#ifndef __RELPOSMENU_HPP
#define __RELPOSMENU_HPP

#include <SFML/Graphics.hpp>
#include <chrono>

#include "TextRectangle.hpp"
#include "display_structs.hpp"
#include "event_structs.hpp"

#define BACK_X_OUTPUT_OPTION -1

enum RelPosMenuOutAction{
	REL_POS_MENU_NO_ACTION,
	REL_POS_MENU_BACK,
	REL_POS_MENU_CONFIRM,
};

class RelativePositionMenu {
public:
	RelativePositionMenu(bool font_load_success, sf::Font &text_font);
	~RelativePositionMenu();
	bool poll(SFEvent &event_data);
	void draw(float scaling_factor, sf::RenderTarget &window);
	void reset_data();
	std::chrono::time_point<std::chrono::high_resolution_clock> last_input_processed_time;
	void reset_output_option();
	void prepare(float scaling_factor, int view_size_x, int view_size_y, BottomRelativePosition curr_bottom_pos);
	void insert_data();
	RelPosMenuOutAction selected_index = RelPosMenuOutAction::REL_POS_MENU_NO_ACTION;
	BottomRelativePosition selected_confirm_value = BOT_REL_POS_END;
private:
	struct RelPosMenuData {
		int option_selected = -1;
		int menu_width;
		int menu_height;
		int pos_x;
		int pos_y;
	};
	RelPosMenuData future_data;
	TextRectangle **labels;

	int num_options_per_screen;
	int elements_start_id;
	int min_elements_text_scaling_factor;
	int width_factor_menu;
	int width_divisor_menu;
	int base_height_factor_menu;
	int base_height_divisor_menu;
	float min_text_size;
	float max_width_slack;
	sf::Color menu_color;
	std::string title;

	int num_elements_per_screen;
	int num_title_back_x_elements;
	int num_elements_displayed_per_screen;
	int num_vertical_slices;
	int title_back_x_start_id;
	int back_x_id;
	int title_id;

	std::chrono::time_point<std::chrono::high_resolution_clock> last_action_time;
	const float action_timeout = 0.1;
	int option_selected = -1;
	bool *selectable_labels;
	RelPosMenuData loaded_data;
	sf::RectangleShape menu_rectangle = sf::RectangleShape(sf::Vector2f(1, 1));


	bool is_option_selectable(int index);
	void set_output_option(int index);
	std::string get_string_option(int index);
	void class_setup();
	void prepare_options();
	void base_prepare(float menu_scaling_factor, int view_size_x, int view_size_y);
	void after_class_setup_connected_values();
	void prepare_text_slices(int x_multiplier, int x_divisor, int y_multiplier, int y_divisor, int index, float text_scaling_factor, bool center = false);
	bool can_execute_action();
	void up_code(bool is_simple);
	void down_code(bool is_simple);
	void left_code();
	void right_code();
	void option_selection_handling();
	bool is_option_element(int option);
	void set_default_cursor_position();
	void decrement_selected_option(bool is_simple);
	void increment_selected_option(bool is_simple);
};
#endif
