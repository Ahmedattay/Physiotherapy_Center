#include "Schedular.h"
#include "UI.h"

int main() {
    int Timestep = 35;
    Schedular physioCenter(Timestep);
    UI Ui(&physioCenter);
    physioCenter.loadFile("input1.txt");
    while (physioCenter.shouldContinue())
    {
    physioCenter.runSimulation(Timestep);//start from step 1
    Timestep++;
    }

    return 0;
}