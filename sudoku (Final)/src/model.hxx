#pragma once

#include <ge211.hxx>
#include <vector>

class Model
{
public:
    Model();
    using Position = ge211::Posn<int>;

    using Grid = std::vector<std::vector<int>>;

    static constexpr int grid_counts_ = 9;

    bool is_empty_grid(int x, int y) const;
    bool is_modifiable(int x,int y) const;
    bool is_conflicted(int x, int y) const;
    bool check_grid(int x, int y) const;
    int current_number_at(int x, int y) const;
    int solution_number_at(int x, int y) const;
    void play_move(int x, int y, int number);

    Position hint();

    void set_game_easy();
    void set_game_medium();
    void set_game_hard();
    void set_game_home();
    bool game_complete() const;
    int game_stage() const;
    void on_frame(double dt);

    Grid current_grids_{grid_counts_, std::vector<int>(grid_counts_)};
    Grid initial_grids_{grid_counts_, std::vector<int>(grid_counts_)};
    Grid solution_{grid_counts_, std::vector<int>(grid_counts_)};

    double seconds=0.0;

private:
    int difficulty_;



    Grid user_grids_{grid_counts_, std::vector<int>(grid_counts_)};
    Grid easy_{grid_counts_, std::vector<int>(grid_counts_)};
    Grid medium_{grid_counts_, std::vector<int>(grid_counts_)};
    Grid hard_{grid_counts_, std::vector<int>(grid_counts_)};

    Position last_hint_position_{0, 0};
};