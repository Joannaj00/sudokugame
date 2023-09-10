#include "model.hxx"
#include <catch.hxx>
using Grid = std::vector<std::vector<int>>;
const Model::Grid puzzle1 = {
        {5, 3, 4, 0, 7, 8, 9, 1, 2},
        {6, 0, 2, 1, 9, 5, 0, 4, 8},
        {1, 9, 0, 3, 4, 2, 5, 6, 7},
        {0, 5, 9, 7, 0, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 0, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 0},
        {9, 6, 1, 0, 3, 7, 2, 8, 4},
        {2, 8, 0, 4, 1, 9, 0, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 0, 9}
};

const Model::Grid solution1 = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}
};
TEST_CASE("example test (TODO: replace this)")
{
    CHECK(1 + 1 == 2);
}

//
// TODO: Write preliminary model tests.
//
// These tests should demonstrate your functional requirements.
//
TEST_CASE("Check game difficulty setting functions")
{
    Model model;
    model.set_game_easy();
    CHECK(model.game_stage() == 1);
    model.set_game_medium();
    CHECK(model.game_stage() == 2);
    model.set_game_hard();
    CHECK(model.game_stage() == 3);
    CHECK(model.current_grids_[0][0]==5);
    CHECK(model.seconds==0);
}


TEST_CASE("Game complete"){
    Model model;
    model.current_grids_= puzzle1;
    model.solution_=solution1;
    for(int i=0;i<model.grid_counts_;i++){
        for(int j=0;j<model.grid_counts_;j++){
            if(model.is_modifiable(i,j)){
                model.play_move(i,j,model.solution_[i][j]);

                }
            }
        }

    CHECK(model.game_complete()== true);

}

TEST_CASE("Playing a move")
{
    Model model;
    model.initial_grids_= puzzle1;
    model.play_move(3, 0, 8);
    CHECK(model.current_number_at(3, 0) == 8 );
}


TEST_CASE("detects conflicts")
{
    Model model;
    model.initial_grids_ = puzzle1;

    // checks conflict in row
    model.play_move(3, 0, 4);
    CHECK(model.is_conflicted (0,3));

    // checks conflict in 3x3 square
    model.play_move(1,6,9);
    CHECK(model.is_conflicted (6,1));

    // checks conflict in column
    model.play_move(3, 4, 8);
    CHECK(model.is_conflicted(4,3));
}

TEST_CASE("hint usage")
{
Model model;

model.set_game_easy();

Model::Position expectedFirstHintPosition{0, 3};  // This position is the
// first empty cell in the puzzle.
Model::Position expectedSecondHintPosition{1, 1};  // This position is
// the second empty cell in the puzzle.

Model::Position firstHintPosition = model.hint();
CHECK(firstHintPosition.x == expectedFirstHintPosition.x);
CHECK(firstHintPosition.y == expectedFirstHintPosition.y);

Model::Position secondHintPosition = model.hint();
CHECK(secondHintPosition.x == expectedSecondHintPosition.x);
CHECK(secondHintPosition.y == expectedSecondHintPosition.y);
}