#include "common.h"
#include "feeder.h"
#include "broker.h"

class Strategy {
public:
    Strategy(const char* name, int id);
    virtual ~Strategy();
    void Init(Feeder* feeder, Broker* broker);
    void CreateOrder(LocalOrderInfo* order);
    void CreateCancel(LocalCancelInfo* order);

    virtual void OnTick(MarketDataField* data) {};
    void ProcessMessage(MemoryMessage* message);

    virtual void OnRtnOrder(LocalRtnOrder* pOrder) {};
    virtual void OnRtnTrade(LocalRtnTrade* pTrade) {};
    virtual void StrategyErrorInsert(LocalOrderInfo* order) {};
    virtual void StrategyErrorCancel(LocalOrderInfo* order) {};

public:
    CTwoBuffer* buf_ = nullptr;
    std::vector<MemoryMessage*> vec_msg_;
    std::vector<MarketDataField*> vec_md_;

protected:
    string name_;
    int id_;

    Broker* broker_;
    Feeder* feeder_;
};



class Thuner : public Strategy {
public:
    Thuner(const char* name, int id);
    ~Thuner();
    virtual void OnTick(MarketDataField* data) override;
    virtual void OnRtnOrder(LocalRtnOrder* pOrder) override;
    virtual void OnRtnTrade(LocalRtnTrade* pTrade) override;
    virtual void StrategyErrorInsert(LocalOrderInfo* order) override;
    virtual void StrategyErrorCancel(LocalOrderInfo* order) override;
};
