////////////////////测试twobuf的代码
//#include "twobuf.h"
//#include "common.h"
//
//using namespace std;
//
//void producer(CTwoBuffer* buf)
//{
//    for (int i = 0; i != 20; ++i) {
//        if (i % 2 == 0) {
//            MemoryMessage* input = buf->AllocateMessage<LocalStrategy>(1);
//            //printf("input <%x>\n", &input);
//            LocalStrategy* temp = (LocalStrategy*)input->field;
//            temp->strategy_id = 111;
//            strncpy_s(temp->name, "thunder", 8);
//            buf->CloseAllocate<LocalStrategy>();
//        } else {
//            MemoryMessage* input = buf->AllocateMessage<LocalTrade>(2);
//            //printf("input <%x>\n", &input);
//            LocalTrade* temp = (LocalTrade*)input->field;
//            temp->volume = i;
//            temp->price = i * 0.1;
//            buf->CloseAllocate<LocalTrade>();
//        }
//        Sleep(i % 1000);
//    }
//}
//
//void consumer(CTwoBuffer* buf) {
//    int offset = sizeof(MemoryHeader);
//    MemoryHeader* header = buf->GetMemoryHeader();
//    while (true) {
//        if (header->next.load()) {
//            header = buf->GetMemoryHeader();
//            offset = sizeof(MemoryHeader);
//            printf("consumer new header<%x>\n", header);
//        }
//        while (offset < header->offset.load()) {
//            MemoryMessage* msg = (MemoryMessage*)((char*)header + offset);
//            if (msg->header.type == 1) {
//                LocalStrategy* temp = (LocalStrategy*)(msg->field);
//                printf("<LocalStrategy> <%s> <%d>\n", temp->name, temp->strategy_id);
//            }
//            else if (msg->header.type == 2) {
//                LocalTrade* temp = (LocalTrade*)(msg->field);
//                printf("<LocalTrade> <%.2f> <%d>\n", temp->price, temp->volume);
//            }
//            offset += (sizeof(MemoryMessage) + msg->header.length);
//        }
//    }
//}
//
//void consumer1(CTwoBuffer* buf) {
//    std::vector<MemoryMessage*> vec_msg;
//    while (true) {
//        buf->GetMemoryMessage(vec_msg);
//        for (auto& msg : vec_msg) {
//            if (msg->header.type == 1) {
//                LocalStrategy* temp = (LocalStrategy*)(msg->field);
//                printf("<LocalStrategy> <%s> <%d>\n", temp->name, temp->strategy_id);
//            }
//            else if (msg->header.type == 2) {
//                LocalTrade* temp = (LocalTrade*)(msg->field);
//                printf("<LocalTrade> <%.2f> <%d>\n", temp->price, temp->volume);
//            }
//        }
//        vec_msg.clear();
//    }
//}
//
//int main(int argc, char* argv[])
//{
//    printf("MemoryHeader<%d> MemoryMessage<%d> LocalStrategy<%d> LocalTrade<%d>\n", sizeof(MemoryHeader), sizeof(MemoryMessage), sizeof(LocalStrategy), sizeof(LocalTrade));
//    CTwoBuffer* buf = new CTwoBuffer("test");
//    buf->Init();
//
//    //boost::thread consumer_thread(consumer, buf);
//    boost::thread consumer_thread(consumer1, buf);
//    boost::thread producer_thread(producer, buf);
//
//    producer_thread.join();
//    consumer_thread.join();
//}


///////////////////////////////////////类boost::lockfree::stack实现了一个多写入/多读取栈
//#include <boost/thread/thread.hpp>
//#include <boost/lockfree/stack.hpp>
//#include <iostream>
//#include <set>
//#include <boost/atomic.hpp>
//
//boost::atomic_int producer_count(0);
//boost::atomic_int consumer_count(0);
//
//boost::lockfree::stack<int> stack(128);
//
//const int iterations = 1000;
//const int producer_thread_count = 4;
//const int consumer_thread_count = 1;
//
//void producer(void)
//{
//    for (int i = 0; i != iterations; ++i) {
//        int value = ++producer_count;
//        while (!stack.push(value))
//            ;
//    }
//}
//
//boost::atomic<bool> done(false);
//
//void consumer(void)
//{
//    std::set<int> set_values;
//    int value;
//    /*while (!done) {
//        while (stack.pop(value))
//            ++consumer_count;
//    }*/
//
//    while (stack.pop(value)) {
//        ++consumer_count;
//        set_values.insert(value);
//        printf("thread ID<%d> <%d>  size<%d>\n", boost::this_thread::get_id(), consumer_count.load(), set_values.size());
//    }
//
//
//}
//
//int main(int argc, char* argv[])
//{
//    using namespace std;
//    cout << "boost::lockfree::stack is ";
//    if (!stack.is_lock_free())
//        cout << "not ";
//    cout << "lockfree" << endl;
//
//    boost::thread_group producer_threads, consumer_threads;
//
//    for (int i = 0; i != producer_thread_count; ++i)
//        producer_threads.create_thread(producer);
//
//    for (int i = 0; i != consumer_thread_count; ++i)
//        consumer_threads.create_thread(consumer);
//
//    producer_threads.join_all();
//    done = true;
//
//    consumer_threads.join_all();
//
//    cout << "produced " << producer_count << " objects." << endl;
//    cout << "consumed " << consumer_count << " objects." << endl;
//}


//#include "common.h"
////BoostLockFree 单例
//void consumer(void) {
//    while (true) {
//        std::function<void(void)> func;
//        while (Singleton<BoostLockFree>::GetInstance()->free_stack_.pop(func)) {
//            //顺序执行所有的回调函数
//            func();
//        }
//    }
//}
//
////三个生产者, 一个消费者的模式。生产者的位置，1.行情 Feeder::MarketData 2.策略 Strategy::ProxyStrategyReqInsert/Strategy::ProxyStrategyReqCancel/Accout::ProxyStrategyErrorInsert/Accout::ProxyStrategyErrorCancel
////3.交易 Broker Broker::ProxyOnRtnOrder/ProxyOnRtnTrade(LocalRtnTrade* pTrade)
//
//int main(int argc, char* argv[]) {
//    boost::thread consumer_thread(consumer);
//    consumer_thread.join();
//    return 0;
//}


#include "application.h"
#include "strategy.h"

int main(int argc, char* argv[]) {

    Feeder* feeder = new CTP();
    Broker* broker = new Broker();
    Thuner* thuner = new Thuner("thunder", 111);
    thuner->Init(feeder, broker);

    Application* app = new Application(feeder, broker);
    app->StartWork();

    while (true) {
        Sleep(5000);
    }
}