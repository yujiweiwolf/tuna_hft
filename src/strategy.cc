#include <thread>
#include "strategy.h"
#include "accout.h"

Strategy::Strategy(const char* name, int id): name_(name), id_(id){
    buf_ = new CTwoBuffer(name);
    feeder_ = nullptr;
    broker_ = nullptr;
}

Strategy::~Strategy() {

}

void Strategy::Init(Feeder* feeder, Broker* broker) {
    feeder_ = feeder;
    broker_ = broker;

    std::function<void(MarketDataField*)> func = std::bind(&Strategy::OnTick, this, placeholders::_1);
    feeder_->AddCallBack(func);
    std::function<void(MemoryMessage*)> func1 = std::bind(&Strategy::ProcessMessage, this, placeholders::_1);
    broker_->AddCallBack(func1);
}


void Strategy::ProcessMessage(MemoryMessage* message) {
    switch (message->header.type)
    {
    case STRATEGY_REQ_INSERT:
        
        break;
    case STRATEGY_REQ_CANCEL:
        
        break;
    case API_RTN_ORDER:
        
        break;
    case API_RTN_CANCEL:
        
        break;
    default:
        printf("<%s> <%d> no need to process %d type message\n", __FUNCTION__, __LINE__, message->header.type);
        break;
    }
}

void Strategy::CreateOrder(LocalOrderInfo* order) {
 /*   MemoryMessage* input = buf_->AllocateMessage<LocalOrderInfo>(1);
    LocalOrderInfo* temp = (LocalOrderInfo*)input->field;

    buf_->CloseAllocate<LocalOrderInfo>();*/
    broker_->SubmitOrder(order);
}

void Strategy::CreateCancel(LocalCancelInfo* order) {
    //MemoryMessage* input = buf_->AllocateMessage<LocalCancelInfo>(1);
    //LocalCancelInfo* temp = (LocalCancelInfo*)input->field;

    //buf_->CloseAllocate<LocalCancelInfo>();
    broker_->SubmitCancel(order);
}


Thuner::Thuner(const char* name, int id) : Strategy(name, id) {

}

Thuner::~Thuner() {

}

void Thuner::OnTick(MarketDataField* data) {
    //产生报单或者撤单请求
    LocalOrderInfo order;
    CreateOrder(&order);
}


void Thuner::OnRtnOrder(LocalRtnOrder* pOrder) {

}

void Thuner::OnRtnTrade(LocalRtnTrade* pTrade) {

}

void Thuner::StrategyErrorInsert(LocalOrderInfo* order) {

}

void Thuner::StrategyErrorCancel(LocalOrderInfo* order) {

}


