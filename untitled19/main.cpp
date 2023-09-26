#include <iostream>
#include <ctime>
#include <iomanip>
#include <string>
#include <vector>

struct task {
    std::string name;
    long long time_begin;
    long long time_end;
    int delta_time;
    int hour=0;
    int minute=0;
    int second=0;
};

std::vector<task> tasks;

void end (bool* tmp) {
    if (*tmp) {
        std::time_t time_finish = std::time(nullptr);
        *tmp=false;
        tasks.back().time_end=time_finish;
        tasks.back().delta_time=tasks.back().time_end-tasks.back().time_begin;

        tasks.back().hour=tasks.back().delta_time/3600;
        tasks.back().minute=(tasks.back().delta_time-tasks.back().hour*3600)/60;
        tasks.back().second=tasks.back().delta_time-(tasks.back().hour*3600)-(tasks.back().minute*60);
    }
}

void begin (bool* tmp) {
    if (*tmp) {
        end(tmp);
    }
    *tmp=true;
    std::string name_task;
    std::cout << "Enter the name of the task" << std::endl;
    std::cin >> name_task;
    task new_task;
    new_task.name=name_task;

    std::time_t time_start=std::time(nullptr);
   new_task.time_begin=time_start;
   tasks.push_back(new_task);
}


void status () {
    for (int i=0; i<tasks.size(); ++i) {
        std::cout<<tasks[i].name<<" time spent: "<<tasks[i].hour<<":"<<tasks[i].minute<<":"<<tasks[i].second<<std::endl;
    }
};

int main() {
    std::string command;
    bool tmp=false;
    while (command!="exit") {
        std::cout << "Enter the command" << std::endl;
        std::cin >> command;

        if (command=="exit") {
            return 0;
        }

        if (command=="begin") {
            begin(&tmp);
        }

        if (command=="end") {
            end(&tmp);
        }

        if (command=="status") {
            status();
        }
    }
}
