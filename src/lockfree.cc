#include "lockfree.h"

BoostLockFree::BoostLockFree() {

}

BoostLockFree::~BoostLockFree() {

}

void BoostLockFree::AddFunction(std::function<void(void)>& func) {
	free_stack_.push(func);
}
