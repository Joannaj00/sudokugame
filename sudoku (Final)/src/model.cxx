#include "model.hxx"

using namespace ge211;

Model::Model()
        : current_grids_(grid_counts_, std::vector<int>(grid_counts_)),
          initial_grids_(grid_counts_, std::vector<int>(grid_counts_)),
          solution_{
                  {5, 3, 4, 6, 7, 8, 9, 1, 2},
                  {6, 7, 2, 1, 9, 5, 3, 4, 8},
                  {1, 9, 8, 3, 4, 2, 5, 6, 7},
                  {8, 5, 9, 7, 6, 1, 4, 2, 3},
                  {4, 2, 6, 8, 5, 3, 7, 9, 1},
                  {7, 1, 3, 9, 2, 4, 8, 5, 6},
                  {9, 6, 1, 5, 3, 7, 2, 8, 4},
                  {2, 8, 7, 4, 1, 9, 6, 3, 5},
                  {3, 4, 5, 2, 8, 6, 1, 7, 9}
          },
          seconds(0),
          difficulty_(0),
          user_grids_(grid_counts_, std::vector<int>(grid_counts_)),
          easy_{
                  {5, 3, 4, 0, 7, 8, 9, 1, 2},
                  {6, 0, 2, 1, 9, 5, 0, 4, 8},
                  {1, 9, 0, 3, 4, 2, 5, 6, 7},
                  {0, 5, 9, 7, 0, 1, 4, 2, 3},
                  {4, 2, 6, 8, 5, 3, 0, 9, 1},
                  {7, 1, 3, 9, 2, 4, 8, 5, 0},
                  {9, 6, 1, 0, 3, 7, 2, 8, 4},
                  {2, 8, 0, 4, 1, 9, 0, 3, 5},
                  {3, 4, 5, 2, 8, 6, 1, 0, 9}
          },
          medium_{
                  {5, 3, 0, 0, 7, 8, 9, 0, 2},
                  {6, 0, 2, 1, 0, 5, 0, 4, 8},
                  {0, 9, 0, 3, 4, 0, 5, 0, 7},
                  {0, 5, 0, 0, 0, 1, 0, 2, 3},
                  {4, 0, 6, 8, 0, 3, 0, 9, 0},
                  {7, 1, 0, 0, 2, 0, 8, 0, 0},
                  {9, 0, 1, 0, 3, 0, 2, 8, 0},
                  {2, 0, 0, 4, 1, 0, 0, 3, 5},
                  {0, 4, 5, 2, 0, 6, 0, 0, 9}
          },
          hard_{
                  {5, 3, 0, 0, 0, 8, 0, 0, 2},
                  {6, 0, 0, 1, 0, 0, 0, 0, 8},
                  {0, 0, 0, 3, 0, 0, 5, 0, 7},
                  {0, 0, 0, 0, 0, 0, 0, 2, 3},
                  {0, 0, 6, 0, 0, 0, 7, 0, 0},
                  {7, 0, 0, 0, 2, 0, 0, 0, 0},
                  {9, 0, 0, 0, 3, 0, 2, 0, 0},
                  {2, 0, 0, 0, 0, 0, 0, 3, 5},
                  {0, 4, 0, 2, 0, 6, 0, 0, 0}
          }
{
    for (int i = 0; i < grid_counts_; i++) {
        for (int j = 0; j < grid_counts_; j++) {
            user_grids_[i][j] = 0;
        }
    }


}
//checks if the position is empty
bool Model::is_empty_grid(int x, int y) const
{
    if (user_grids_[x][y] == ' ' || user_grids_[x][y]==0) {
        return true;
    }
    return false;
}

bool Model::is_modifiable(int x, int y) const
{
    if (initial_grids_[x][y] == 0) {
        return true;
    }
    return false;
}

//checks if the position conflicts with the numbers in the same row, column,
// or grid
bool Model::is_conflicted(int x, int y) const
{

    for (int i = 0; i < 9; i++) {
        if (i != y && current_grids_[x][i] == current_grids_[x][y]) {
            return true;
        }
        if (i != x && current_grids_[i][y] == current_grids_[x][y]) {
            return true;
        }
    }
    if (check_grid(x, y) == true) {
        return true;
    }
    return false;
}

bool Model::check_grid(int x, int y) const
{
    int x_pos = (x / 3) * 3;
    int y_pos = (y / 3) * 3;

    for (int i = x_pos; i < x_pos + 3; i++) {
        for (int j = y_pos; j < y_pos + 3; j++) {
            if (i != x && j != y && current_grids_[x][y] == current_grids_[i][j]) {
                return true;
            }
        }
    }
    return false;
}


int Model::current_number_at(int x, int y) const{
    return current_grids_[x][y];
}

int Model::solution_number_at(int x, int y) const{
    return solution_[x][y];
}

void Model::set_game_home(){
    difficulty_=0;
}

void Model::set_game_easy()
{
    difficulty_ = 1;

    for (int i=0;i<grid_counts_;i++){
        for(int j=0;j<grid_counts_;j++){
            initial_grids_[i][j]=easy_[i][j];
            current_grids_[i][j]=easy_[i][j];
            user_grids_[i][j]=easy_[i][j];
        }
    }
}

void Model::set_game_medium()
{
    difficulty_ = 2;


    for (int i=0;i<grid_counts_;i++){
        for(int j=0;j<grid_counts_;j++){
            initial_grids_[i][j]= medium_[i][j];
            current_grids_[i][j]=medium_[i][j];
            user_grids_[i][j]=medium_[i][j];
        }
    }
}

void Model::set_game_hard()
{
    difficulty_ = 3;

    for (int i=0;i<grid_counts_;i++){
        for(int j=0;j<grid_counts_;j++){
            initial_grids_[i][j]=hard_[i][j];
            current_grids_[i][j]=hard_[i][j];
            user_grids_[i][j]=hard_[i][j];
        }
    }
}


bool Model::game_complete() const{
    for (int i=0;i<grid_counts_;i++){
        for(int j=0;j<grid_counts_;j++){
            if(current_grids_[i][j]!=solution_[i][j] &&
            user_grids_[i][j]!=solution_[i][j]){
                return false;
            }
        }
    }
    return true;
}


Model::Position Model::hint() {

    for (int i = last_hint_position_.x; i < grid_counts_; i++) {
        for (int j = (i > last_hint_position_.x ? 0 : last_hint_position_.y +
                1); j < grid_counts_; j++) {
            if (user_grids_[i][j] == 0 && solution_[i][j] != 0) {
                last_hint_position_ = Position{i, j};
                return last_hint_position_;
            }
        }
    }

    // Return an invalid position if no valid hint is available.
    last_hint_position_ = Position{0, 0};  // Reset hint position
    return Position{-1, -1};
}

void Model::play_move(int x, int y, int number)
{
    if (number < 0 || number > 9) {
        throw std::out_of_range("Number must be between 0 and 9");
    }

    if (!is_modifiable(x, y)) {
        throw std::invalid_argument("Cell is not modifiable");
    }

    if (!is_empty_grid(x, y)) {
        throw std::invalid_argument("Cell is not empty");
    }

    // Temporarily update the grid
    current_grids_[x][y] = number;
    user_grids_[x][y] = number;

    if (is_conflicted(x, y)) {
        // Rollback changes if number conflicts
        current_grids_[x][y] = 0;
        user_grids_[x][y] = 0;
        throw std::invalid_argument("Move conflicts with existing numbers");
    }
}

int Model::game_stage() const{
    return difficulty_;
}

void
Model::on_frame(double dt)
{
    seconds+=dt;
}