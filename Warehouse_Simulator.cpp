#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "Crate.h"
#include "ArrivalQueue.h"
#include "Shelf.h"
#include "Warehouse.h"
#include <algorithm>

int main()
{
    std::vector<Crate> sortingFloor;
    Warehouse warehouse;
    ArrivalQueue<Crate> arrivalQueue;
    int const SHELF_LIMIT = 10;
    Crate moveCrate;

    int weight;
    std::string UUID;

    std::string crateInfo;
    std::ifstream readInfo("crates_part2.txt");

    if (!readInfo.is_open()) {
        std::cout << "Failed to open file." << std::endl;
        return 1;
    }

    while (getline(readInfo, crateInfo)) {
        std::stringstream splitCrateInfo(crateInfo);
        splitCrateInfo >> weight >> UUID;

        Crate crate = { weight, UUID };
        arrivalQueue.enqueue(crate);
    }

    Node<Shelf>* currentShelfNode = warehouse.getFront();

    int triedCounter = 0;//How many times we have skipped a shelf

    while (!arrivalQueue.isEmpty()) {

        moveCrate = arrivalQueue.getFront(); //Get Front Crate
        Shelf& currentShelf = currentShelfNode->data; //Get First Shelf

        if (triedCounter >= warehouse.getShelfLimit()) //If we have skipped all shelves, we start traversing and sorting through the actual shelves
        {
            Node <Shelf>* loopEndNode = currentShelfNode; //The node where we'll have to end
            if (currentShelfNode->next == nullptr) currentShelfNode = warehouse.getFront();
            else currentShelfNode = currentShelfNode->next;
            //Shelf& currentShelf = currentShelfNode->data;

            do {
                if (sortingFloor.empty()) {
                    sortingFloor.push_back(moveCrate);
                    int size = currentShelf.getTopIndex();
                    for (int i = 0; i <= size; i++)  // when there is only one object the top index is 0, so we shoud check it too
                    {
                        sortingFloor.push_back(currentShelf.pop());

                    }
                }

                std::sort(sortingFloor.begin(), sortingFloor.end(), [](const Crate& a, const Crate& b) {
                    return a.weight < b.weight;
                    }); // sorting alg in the std lib 

                for (Crate crate : sortingFloor)
                {
                    printf("%i ", crate.weight); // used only for debugging
                }
                printf("\n");

                int totalWeight = 0;
                bool isCrateMoved = true;

                for (int i = sortingFloor.size() - 1; i >= 0; i--)
                {
                    int crateWeight = sortingFloor.at(i).weight;

                    if (totalWeight + crateWeight <= 1000) totalWeight += crateWeight;

                    if (!sortingFloor.empty()) { //check if the weight of the shelf is filled
                        if (currentShelf.getCurrentWeight() + sortingFloor.at(i).weight <= 1000)
                        {
                            currentShelf.push(sortingFloor.at(i));
                        }
                        else
                        {
                            currentShelf = currentShelfNode->data;
                            //break;
                        }


                        if (sortingFloor.at(i).uuid == moveCrate.uuid) {
                            arrivalQueue.dequeue();
                        }

                        sortingFloor.pop_back();

                        if (!arrivalQueue.isEmpty()) {
                            moveCrate = arrivalQueue.getFront();
                        }
                    }
                    else break;
                }

                {
                    printf("\n");
                    printf("Updated Print Matrix:");
                    warehouse.matrixPrint();
                }

                if (sortingFloor.empty()) {// this is not the needed check, we need smth else to determine if we have officially put the crate

                    triedCounter = 0;
                    break;

                }
                else {
                    triedCounter++;
                }

                if (currentShelfNode->next == nullptr) currentShelfNode = warehouse.getFront();
                else currentShelfNode = currentShelfNode->next;
                totalWeight = 0;

            } while (currentShelfNode != loopEndNode);

            if (currentShelfNode == loopEndNode) { // where do i put this so it works???
                std::cout << "There is no availability to put the rest of the crates from arrival queue! \n" << std::endl;
                while (!arrivalQueue.isEmpty()) {
                    Crate leftoverCrate = arrivalQueue.dequeue();
                    std::cout << leftoverCrate.uuid << " " << leftoverCrate.weight << "\n" << std::endl;
                }
            }
        }

        if (currentShelf.getCurrentSize() < currentShelf.getBulkLimit() &&
            currentShelf.getCurrentWeight() + moveCrate.weight <= currentShelf.getWeightLimit() &&
            (currentShelf.isEmpty() || moveCrate.weight <= currentShelf.peekLast().weight)) {

            currentShelf.push(moveCrate);
            arrivalQueue.dequeue();
            triedCounter = 0;

            {
                printf("\n");
                printf("Updated Print Matrix:");
                warehouse.matrixPrint();
            }
        }
        else {

            if (currentShelfNode->next == nullptr) currentShelfNode = warehouse.getFront();
            else currentShelfNode = currentShelfNode->next;

            triedCounter++;
        }
    }
    warehouse.matrixPrint();
    printf("\n");
}


