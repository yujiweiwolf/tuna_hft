#pragma once
#include "common.h"
#include "twobuf.h"
class Accout;

class Broker {
public:
    Broker();
    virtual ~Broker();
    void SubmitOrder(LocalOrderInfo* order);
    void SubmitCancel(LocalCancelInfo* order);
    void Dispatch();
    void ProcessMessage(MemoryMessage* message);
    void AddCallBack(std::function<void(MemoryMessage*)> func);

private:
    CTwoBuffer* buf_ = nullptr;
    std::vector<MemoryMessage*> vec_msg_;
    unordered_map<string, Accout*> vec_accout_;
    std::vector<std::function<void(MemoryMessage*)>> vec_funcs_;
};




