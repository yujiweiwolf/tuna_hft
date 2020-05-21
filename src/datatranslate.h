//#pragma once
//#include "common.h"
//#include "twobuf.h"
//
//void GetMemoryMessage(std::vector<MemoryMessage*>& vec_msg, CTwoBuffer* buf) {
//    int offset = sizeof(MemoryHeader);
//    MemoryHeader* header = buf->GetMemoryHeader();
//    if (header->next.load()) {
//        header = buf->GetMemoryHeader();
//        offset = sizeof(MemoryHeader);
//        printf("consumer new header<%x>\n", header);
//    }
//    while (offset < header->offset.load()) {
//        MemoryMessage* msg = (MemoryMessage*)((char*)header + offset);
//        vec_msg.push_back(msg);
//        offset += (sizeof(MemoryMessage) + msg->header.length);
//        printf("GetMemoryMessage   header <%x>, offset<%d> \n", header, offset);
//    }
//}
//
