#include "Schedular.h"
#include "UI.h"

int main() {
    int Timestep = 35;
    Schedular physioCenter(Timestep);
    UI Ui(&physioCenter);
    physioCenter.loadFile("input1.txt");
    while (physioCenter.shouldContinue())
    {
    physioCenter.runSimulation(Timestep); // Start from timestep 1
    Ui.displayCurrentStatus(Timestep);
    Timestep++;
    }
    physioCenter.Create_Out_File(Timestep);
    return 0;
}