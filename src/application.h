#pragma once
#include "broker.h"
#include "feeder.h"

class Application {
public:
    Application(Feeder* feeder, Broker* broker): feeder_(feeder), broker_(broker){

    };
    ~Application() {

    };

    void StartWork() {
        thread worker(&Application::Run, this);
        worker.detach();
    };

    void Run() {
        while (true) {
            broker_->Dispatch();
            feeder_->Dispatch();
        }
    }

private:
    Broker* broker_;
    Feeder* feeder_;
};