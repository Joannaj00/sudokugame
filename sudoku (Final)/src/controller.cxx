#include "controller.hxx"

Controller::Controller()
        : model_(),
          view_(model_),
          mouse_ {0,0}
{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set,mouse_);
}

View::Dimensions
Controller::initial_window_dimensions() const
{
    return view_.window_dimensions();
}

void
Controller::on_frame(double dt){
    model_.on_frame(dt);
}

void
Controller::on_key(ge211::Key key)
{

    if (key== ge211::Key::code('q')) {
        quit();
    }

    if (key == ge211::Key::code('h')) {
        if(!model_.game_complete()){
            view_.score--;
        }
        auto hintPosition = model_.hint();
        if (hintPosition.x >= 0 && hintPosition.y >= 0) { // Valid hint position
            view_.selection_ = hintPosition;  // Select the hint cell
            model_.current_grids_[hintPosition.x][hintPosition.y] = model_
                    .solution_number_at(hintPosition.x,hintPosition.y);
        }
    }

    if (key == ge211::Key::code('\b')) {
        model_.current_grids_[view_.selection_.x][view_.selection_.y]=0;
    }

    if(key==ge211::Key::code('f')){
        view_.selection_= {-2,-2};
        //model_.print();
    }

    if(model_.is_empty_grid(view_.selection_.x,view_.selection_.y)){
        if (key==ge211::Key::code(' ')){
            view_.selection_= {-1,-1};
        }
        if (key== ge211::Key::code('1')) {
            model_.current_grids_[view_.selection_.x][view_.selection_.y]=1;
        }
        if (key== ge211::Key::code('2')) {
            model_.current_grids_[view_.selection_.x][view_.selection_.y]=2;
        }
        if (key== ge211::Key::code('3')) {
            model_.current_grids_[view_.selection_.x][view_.selection_.y]=3;
        }
        if (key== ge211::Key::code('4')) {
            model_.current_grids_[view_.selection_.x][view_.selection_.y]=4;
        }
        if (key== ge211::Key::code('5')) {
            model_.current_grids_[view_.selection_.x][view_.selection_.y]=5;
        }
        if (key== ge211::Key::code('6')) {
            model_.current_grids_[view_.selection_.x][view_.selection_.y]=6;
        }
        if (key== ge211::Key::code('7')) {
            model_.current_grids_[view_.selection_.x][view_.selection_.y]=7;
        }
        if (key== ge211::Key::code('8')) {
            model_.current_grids_[view_.selection_.x][view_.selection_.y]=8;
        }
        if (key== ge211::Key::code('9')) {
            model_.current_grids_[view_.selection_.x][view_.selection_.y]=9;
        }
        if(model_.is_conflicted(view_.selection_.x, view_.selection_.y)){
            view_.score--;
        }
    }


}
void
Controller::on_mouse_down(ge211::Mouse_button m, ge211::Posn<int> position)
{
    View::Position board_pos = view_.screen_to_board(position);


    // on the main menu -- selecting the easy or hard game
    if (model_.game_stage() == 0) {

        if (board_pos == view_.screen_to_board(easy_game)) {
            model_.set_game_easy();
            view_.score=100;
        } else if (board_pos == view_.screen_to_board(medium_game)) {
            model_.set_game_medium();
            view_.score=100;
        } else if (board_pos == view_.screen_to_board(hard_game)) {
            model_.set_game_hard();
            view_.score=100;
        }
    }

            // inside each board - making so that you can only select the squares
            // that are valid - the ones that weren't in the board before
    else if(model_.game_stage() == 1 or model_.game_stage() == 2 or model_.game_stage()==3) {
        View::Position clicked  = {(position.x - 120)/(40), (position.y - 120)/
                               (40)};
        if (clicked.x > 8 || clicked.x < 0 || clicked.y > 8 ||
            clicked.y < 0) {
            return;
        } else {
            view_.selection_ = clicked;
            return;
        }
    }
}
