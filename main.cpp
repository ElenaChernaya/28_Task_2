#include <iostream>
#include <thread>
#include <mutex>
#include <vector>


std::mutex mtx;

void way (int& time, char& name)
{

    std::this_thread::sleep_for(std::chrono::seconds(time));

    mtx.lock();
    std::cout << "The train " << name << " arrived at the station!" << std::endl;

    std::string command = "unknown";
    std::cout << "Enter the command \"depart\" to leave the train from the station\n";

    while (command != "depart")
    {
        std::cin >> command;
    }

    std::cout << "The train " << name << " left the station" << std::endl;
    mtx.unlock();

}


int main() {
    const int size = 3;

    //заполняем вектор времени в пути для каждого поезда
    std::cout << "Enter the travel time for the train:\n";
    int time;
    std::vector<int> travelTime;
    for (int i = 0; i < size; ++i)
    {
        std::cin >> time;
        travelTime.push_back(time);
    }

    std::vector<char> name {'A', 'B', 'C'};
    std::vector<std::thread> t;

    for(int i = 0; i < size; ++i)
    {
        mtx.lock();
        t.emplace_back(std::thread(way, std::ref(travelTime[i]), std::ref(name[i])));
        mtx.unlock();
    }

    for(int i = 0; i < size; ++i)
    {
        t[i].join();
    }
}
