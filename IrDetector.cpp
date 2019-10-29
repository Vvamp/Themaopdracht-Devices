#include "IrDetector.hpp"

bool IrDetector::get(){
	detectorPin.refresh();
	return detectorPin.read();
}