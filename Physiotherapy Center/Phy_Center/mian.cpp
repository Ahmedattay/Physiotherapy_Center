#include "Schedular.h"
#include "UI.h"

int main() {
    int Timestep = 30;
    Schedular physioCenter(Timestep);
    UI Ui(&physioCenter);
    physioCenter.loadFile("input1.txt");
    while (physioCenter.shouldContinue())
    {
        physioCenter.MainSimulation(Timestep);//start from step 1
        if (Ui.displayCurrentStatus(Timestep) == 'S') {
            physioCenter.generateOutputFile("output1.txt", Timestep);

            break;
        }
    Timestep++;
    }
    return 0;
}