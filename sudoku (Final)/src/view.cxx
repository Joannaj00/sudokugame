#include "view.hxx"



//Initializes colors to be used by sprites
static ge211::Color const green_color {160,184,135};
static ge211::Color const selected_color {160,184,200};
static ge211::Color const white_color {255,255,255};
static ge211::Color const black_color {0,0,0};

View::View(Model const& model)
        : model_(model),
          grid_sprite({size_of_cell -5, size_of_cell -5},
                      green_color),
          easy_mode(),
          medium_mode(),
          hard_mode(),
          horizontal_rectangle({360, 5},green_color),
          vertical_rectangle({5,360},green_color),
          individual_box({35,35},black_color),
          white_sprite({55,55}, white_color),
          black_sprite({55,55}, black_color),
          selected_sprite({35,35}, selected_color),
          background_white_sprite({360,
                                   360},
                                  white_color),
          black_rectangle({360,100}, black_color)

{ }

View::Dimensions
View::window_dimensions() const
{
    return {600,600};
}

void
View::draw(ge211::Sprite_set& set, Position pos)
{

    ///Creates screen when the game is in stage 1, the selection screen

    //places two boxes for selection, the easy game or hard game
    if (model_.game_stage() == 0) {
        set.add_sprite(white_sprite, easy_game, 1);
        set.add_sprite(white_sprite, medium_game, 1);
        set.add_sprite(white_sprite, hard_game, 1);

        //Places titles above the two boxes
        ge211::Text_sprite::Builder name_builder(sans30_);
        name_builder << "Easy";
        easy_mode.reconfigure(name_builder);
        set.add_sprite(easy_mode, {easy_game.x - 5, easy_game.y - 65}, 1);

        ge211::Text_sprite::Builder name_builder2(sans30_);
        name_builder2 << "Medium";
        medium_mode.reconfigure(name_builder2);
        set.add_sprite(medium_mode, {medium_game.x - 5, medium_game.y - 65},
                       1);

        ge211::Text_sprite::Builder name_builder3(sans30_);
        name_builder3 << "Hard";
        hard_mode.reconfigure(name_builder3);
        set.add_sprite(hard_mode, {hard_game.x - 5, hard_game.y - 65}, 1);

    }

    else if (model_.game_stage() == 1 || model_.game_stage() == 2 ||
             model_.game_stage() == 3) {

        set.add_sprite(horizontal_rectangle,
                       {120, 120}, 1);
        set.add_sprite(horizontal_rectangle,
                       {120, 240}, 1);
        set.add_sprite(horizontal_rectangle,
                       {120, 360}, 1);
        set.add_sprite(horizontal_rectangle,
                       {120, 480}, 1);
        set.add_sprite(vertical_rectangle,
                       {120, 120}, 1);
        set.add_sprite(vertical_rectangle,
                       {240, 120}, 1);
        set.add_sprite(vertical_rectangle,
                       {360, 120}, 1);
        set.add_sprite(vertical_rectangle,
                       {480, 120}, 1);

        set.add_sprite(title,{230,35},1);
        set.add_sprite(instruction0,{100,490},1);
        set.add_sprite(instruction1,{100,510},1);
        set.add_sprite(instruction2,{100,530},1);
        set.add_sprite(instruction3,{320,490},1);
        set.add_sprite(instruction4,{320,510},1);
        set.add_sprite(instruction5,{320,530},1);
        set.add_sprite(instruction6,{100,550},1);

        int start = 120;



        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                set.add_sprite(individual_box, {i * 40 + start + 5, j * 40
                                                                    + start +
                                                                    5}, 2);
            }
        }
        // the user pressed "f", means that the game is completed
        Position p= {-2,-2};
        if(selection_==p){
            // if the user is correct
            if(model_.game_complete()){
                set.add_sprite(black_rectangle,{140,200},8);
                set.add_sprite(winning_text,{150,210},9);
                ge211::Text_sprite::Builder letter_builder(sans30_);
                letter_builder << score;
                number_sprite.reconfigure(letter_builder);
                set.add_sprite(number_sprite,
                               {200,250},
                               10);

            }
            else{
                set.add_sprite(black_rectangle,{100,200},8);
                set.add_sprite(losing_test,{110,210},9);
            }
        }

        for (int i = 0; i < model_.grid_counts_; i++) {
            for (int j = 0; j < model_.grid_counts_; j++) {
                set.add_sprite(background_white_sprite, {120, 120}, 0);

                // show the current score
                set.add_sprite(score_msg,{0,0},0);
                ge211::Text_sprite::Builder letter(sans30_);
                letter << score;
                number_sprite.reconfigure(letter);
                set.add_sprite(number_sprite,
                               {70,0},
                               10);

                // show the time passed
                set.add_sprite(time_text,{420,0},0);
                ge211::Text_sprite::Builder time_builder(sans30_);
                time_builder << floor(model_.seconds);
                timer_sprite.reconfigure(time_builder);
                set.add_sprite(timer_sprite,{550,0},1);



                ge211::Text_sprite::Builder letter_builder(sans30_);

                if (model_.current_number_at(i, j) == 0) {
                    letter_builder << ' ';
                } else {
                    letter_builder << model_.current_number_at(i, j);
                }

                number_sprite_[i][j].reconfigure(letter_builder);
                set.add_sprite(number_sprite_[i][j],
                               {i * 40 + start + 15, j * 40
                                                     + start + 5},
                               3);

                Position pos = {i, j};
                if (model_.is_conflicted(i,j) && selection_ == pos) {
                    set.add_sprite(selected_sprite,
                                   {i * 40 + start + 5, j * 40
                                                        + start + 5},
                                   5);

                    ge211::Text_sprite::Builder builder(sans30_);

                    if (model_.is_conflicted(i, j)) {
                        builder.color(ge211::Color::medium_red());
                    } else {
                        builder.color(ge211::Color::medium_blue());
                    }

                    if (model_.current_number_at(i, j) == 0) {
                        builder << ' ';
                    } else {
                        builder << model_.current_number_at(i, j);
                    }

                    number_sprite_[i][j].reconfigure(builder);
                    set.add_sprite(number_sprite_[i][j],
                                   {i * 40 + start + 15, j * 40
                                                        + start + 5},
                                   6);
                }
                if(model_.is_modifiable(i,j)) {
                    ge211::Text_sprite::Builder builder(sans30_);

                    if (model_.is_conflicted(i, j)) {
                        builder.color(ge211::Color::medium_red());
                    } else {
                        builder.color(ge211::Color::medium_blue());
                    }

                    if (model_.current_number_at(i, j) == 0) {
                        builder << ' ';
                    } else {
                        builder << model_.current_number_at(i, j);
                    }

                    number_sprite_[i][j].reconfigure(builder);
                    set.add_sprite(number_sprite_[i][j],
                                   {i * 40 + start + 15, j * 40
                                                         + start + 5},
                                   6);
                }

                if(model_.is_modifiable(i,j) && selection_==pos){
                    set.add_sprite(selected_sprite,
                                   {i * 40 + start + 5, j * 40
                                                        + start + 5},
                                   5);

                    ge211::Text_sprite::Builder builder(sans30_);
                }

            }
        }
    }
}

// Transforms a screen position into a board position
View::Position
View::screen_to_board(View::Position pos) const
{
    return {pos.x /size_of_cell , pos.y /size_of_cell};
}