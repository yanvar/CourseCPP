#include "pch.h"
#include "..\..\CourseCPP\Simulation\Simulation.h"

using namespace common;
using namespace simulation;
using namespace robotalgo;

TEST(TestCaseName, testSingleCleanSquareHouse) {

    simulation::Simulation sim1(float(150), 1, float(2.5));
    /*sim1.addHouse("..\CourseCPP\House3.txt");

    class AlgoDummy : public RobotAlgorithm {
    public:
        AlgoDummy(std::vector<Direction> dummyStepsSequence);
        Direction nextStep(Direction lastMove, bool& finish) {

           private:
        Algo algoDummy;
        }*/

    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}