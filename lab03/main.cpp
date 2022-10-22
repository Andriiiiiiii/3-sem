#include <iostream>
#include <random>

using namespace std;

using State = int;

class MainState 
{
public:
    virtual bool contains(State s) const = 0;
    //virtual ~MainState() = default;
};

// copy
class DiscreteState : public MainState 
{
private:
    State const s0;
public:
    DiscreteState(State s0) : s0(s0) {}
    bool contains(State s) const override 
    {
        return s == s0;
    }
};

// copy 
class SegmentState : public MainState 
{
private:
    State const begin_s0, end_s0;
public:
    SegmentState(State begin_s0, State end_s0) :
        begin_s0(begin_s0), end_s0(end_s0) {}
    bool contains(State s) const override 
    {
        return begin_s0 <= s and end_s0 >= s;
    }
};


class ProbabilityTest 
{
private:
    State const E_min, E_max;

public:
    ProbabilityTest(State E_min, State E_max):
        E_min(E_min), E_max(E_max) { }

    float test(
        const MainState& system,
        unsigned test_count,
        unsigned seed) const {
        default_random_engine reng(seed);
        uniform_int_distribution<int>dstr(E_min, E_max);

        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt)
        {
            if (system.contains(dstr(reng)))
            {
                ++good;
            }
        }
        return
            static_cast<float>(good)
            / static_cast<float>(test_count);
    }


};


/*int main() {
    DiscreteState d(0);
    SegmentState s(0, 100);
    ProbabilityTest pt(-1000, 1000);
    cout << pt.test(d, 20000, 1) << endl;
    cout << pt.test(s, 20000, 1) << endl;
}*/
int main()
{
    // Задание 2.1-2.2
    const DiscreteState d(1); //c
    const SegmentState s(10, 10); //c
    ProbabilityTest pt(-1000, 1000); //c
    random_device rd;

    int seed;

    cout << "Test_count;    " << "Prob-D;   " << "Prob-S;" << endl;
    for (int i = 1; i < 10*pow(10,3); i += 10)
    {
        seed = 2;
        cout << i << ";    ";
        float sumd = 0;
        for (int j = 0; j < pow(10, 3); j++)
        {
            sumd += pt.test(d, i, seed);
            seed += 1;
        }
        float resd = sumd / pow(10, 3);
        cout << resd << ";    ";

        float sums = 0;
        for (int j = 0; j < pow(10, 2); j++)
        {
            sums += pt.test(s, i, seed);
            seed += 1;
        }
        float ress = sums / pow(10, 2);
        
        cout << ress << ";" << endl;
    }

    // Задание 2.3
    const SegmentState s1(1, 5);
    const DiscreteState d1(100);
    const DiscreteState d2(300);
    const DiscreteState d3(-900);
    const DiscreteState d4(-200);
    const DiscreteState d5(750);
    /*cout << pt.test(d1, 1000000, rd() % 100) +
        pt.test(d2, 1000000, rd() % 100) +
        pt.test(d3, 1000000, rd() % 100) +
        pt.test(d4, 1000000, rd() % 100) +
        pt.test(d5, 1000000, rd() % 100) << endl;

    cout << pt.test(s1, 1000000, rd() % 100) << endl;*/
    return 0;
}