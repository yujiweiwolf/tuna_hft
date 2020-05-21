#include "twobuf.h"

CTwoBuffer::CTwoBuffer(const char* title) : buf_name_(title){

}

CTwoBuffer::~CTwoBuffer(){

}

void CTwoBuffer::Init() {
    data1_ = new char[DATALENGTH];
    data2_ = new char[DATALENGTH];
    memset(data1_, 0, DATALENGTH);
    memset(data2_, 0, DATALENGTH);
    header_ = (MemoryHeader*)data1_;
    header_->msg_count.store(0);
    header_->offset.store(sizeof(MemoryHeader));
    header_->next.store(false);
    flag = 1;
    printf("data1 <%x>, data2 <%x>, offset<%d>  flag <%d>\n", data1_, data2_, header_->offset.load(), flag);

    read_offset = sizeof(MemoryHeader);
    read_header_ = header_;
}

MemoryHeader* CTwoBuffer::GetMemoryHeader() {
    return header_;
}

bool CTwoBuffer::IsCrossBoundary(int length) {
    return (header_->offset.load() + sizeof(MemoryMessage) + length > DATALENGTH);
}

void CTwoBuffer::SetMemoryHeader() {
    header_->next.store(true);
    if (flag == 1) {
        memset(data2_, 0, DATALENGTH);
        header_ = (MemoryHeader*)data2_;
        flag = 2;
    } else {
        memset(data1_, 0, DATALENGTH);
        header_ = (MemoryHeader*)data1_;
        flag = 1;
    }
    header_->msg_count.store(0);
    header_->offset.store(sizeof(MemoryHeader));
    header_->next.store(false);
}


void CTwoBuffer::GetMemoryMessage(std::vector<MemoryMessage*>& vec_msg) {
    //读当前内存
    while (read_offset < read_header_->offset.load()) {
        MemoryMessage* msg = (MemoryMessage*)((char*)read_header_ + read_offset);
        vec_msg.push_back(msg);
        read_offset += (sizeof(MemoryMessage) + msg->header.length);
    }
    //读下一块内存
    if (read_header_->next.load()) {
        read_header_ = header_;
        read_offset = sizeof(MemoryHeader);
        printf("consumer new header<%x>\n", read_header_);

        while (read_offset < read_header_->offset.load()) {
            MemoryMessage* msg = (MemoryMessage*)((char*)read_header_ + read_offset);
            vec_msg.push_back(msg);
            read_offset += (sizeof(MemoryMessage) + msg->header.length);
        }
    }
}



//CycleArray::CycleArray(){
//    //read_index_.store(0);
//    write_index_.store(0);
//}
//
//CycleArray::~CycleArray(){
//
//}

//void CycleArray::WriteData(MarketDataField* data) {
//    int mod = write_index_.load() & (FEEDERLENGTH - 1);
//    memcpy(dataArray_ + mod, data, datalenth);
//    write_index_.add(1);
//}
