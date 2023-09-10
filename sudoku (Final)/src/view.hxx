#pragma once

#include "model.hxx"

//Initializes the size of each individual square/cell
static int const size_of_cell = 60;
static ge211::geometry::Posn<int> easy_game{130,300};
static ge211::geometry::Posn<int> medium_game{255, 300};
static ge211::geometry::Posn<int> hard_game{380,300};
static ge211::geometry::Posn<int> restart_game{120, 300};

class View
{
public:
    /// Dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// Positions will use `int` coordinates.
    using Position = ge211::Posn<int>;

    ///Defines the View class
    explicit View(Model const& model);

    ///Returns initial board dimensions
    Dimensions window_dimensions() const;

    ///Defines draw function which will add sprites to screen
    void draw(ge211::Sprite_set& set, Position pos);

    ///Allows you to convert pixel locations (mouse position) to what grid on
    /// the board it is so it's easier to understand
    Position screen_to_board(Position screen_pos) const;
    Position selection_{-1,-1};
    int score;


private:
    Model const& model_;


    ///Defines sprites for draw
    ge211::Rectangle_sprite const grid_sprite;
    ge211::Text_sprite number_sprite_[9][9];
    ge211::Text_sprite number_sprite;
    ge211::Text_sprite timer_sprite;
    ge211::Font sans30_{"sans.ttf", 20};
    ge211::Font small_sans_{"sans.ttf", 15};
    ge211::Font big_sans_{"sans.ttf", 30};
    ge211::Text_sprite easy_mode;
    ge211::Text_sprite medium_mode;
    ge211::Text_sprite hard_mode;
    ge211::Text_sprite score_msg{"Score: ",sans30_};
    ge211::Rectangle_sprite horizontal_rectangle;
    ge211::Rectangle_sprite vertical_rectangle;
    ge211::Rectangle_sprite individual_box;
    ge211::Rectangle_sprite white_sprite;
    ge211::Rectangle_sprite black_sprite;
    ge211::Rectangle_sprite selected_sprite;
    ge211::Rectangle_sprite background_white_sprite;
    ge211::Rectangle_sprite black_rectangle;
    ge211::Text_sprite const title{"SUDOKU",big_sans_};
    ge211::Text_sprite const instruction0{"Red number= wrong input",small_sans_};
    ge211::Text_sprite const instruction1{"Blue number= right input",small_sans_};
    ge211::Text_sprite const instruction2{"'q'= Quit",small_sans_};
    ge211::Text_sprite const instruction3{"'h'= Hint",small_sans_};
    ge211::Text_sprite const instruction4{"backspace= delete",small_sans_};
    ge211::Text_sprite const instruction5{"space bar= deselect",small_sans_};
    ge211::Text_sprite const winning_text{"CONGRATSSSSSSs!!!"
                                          "Your score is: ",sans30_};
    ge211::Text_sprite const losing_test{"Please Try Again",sans30_};
    ge211::Text_sprite const time_text{"time passed: ",sans30_};
    ge211::Text_sprite const instruction6{"press 'f' when finished",small_sans_};


};