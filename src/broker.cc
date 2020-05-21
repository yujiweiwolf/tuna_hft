#include "broker.h"
#include "accout.h"

Broker::Broker() {

}

Broker::~Broker() {

}

void Broker::AddCallBack(std::function<void(MemoryMessage*)> func) {
    vec_funcs_.push_back(func);
}

void Broker::Dispatch() {
    for (auto it = vec_accout_.begin(); it != vec_accout_.end();++it) {
        vec_msg_.clear();
        it->second->buf_->GetMemoryMessage(vec_msg_);
        for (auto& msg : vec_msg_) {
            //ProcessMessage(msg);
            for (auto& func : vec_funcs_) {
                func(msg);
            }
        }
    }

    vec_msg_.clear();
    buf_->GetMemoryMessage(vec_msg_);
    for (auto& msg : vec_msg_) {
        for (auto& func : vec_funcs_) {
            func(msg);
        }
        //ProcessMessage(msg);
    }
}

//Broker 内部处理回报
void Broker::ProcessMessage(MemoryMessage* message) {
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

void Broker::SubmitOrder(LocalOrderInfo* order) {
    auto it = vec_accout_.find(order->investor_id);
    if (it != vec_accout_.end()) {
        it->second->SubmitOrder(order);
    }
}

void Broker::SubmitCancel(LocalCancelInfo* order) {

}