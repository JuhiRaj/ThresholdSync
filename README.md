Software for threshold adjust in J-PET
======================================

Compilation
===========

	git clone https://github.com/JPETTomography/ThresholdSync.git
	
	cd ThresholdSync
	
	git submodule update --init --recursive
	
	cmake .
	
	make


Using
=====

	./thresholdsync root_file input_thresholds output_thresholds

It requires root file with histogram after last measurement,
text file with threshold used in this measurement
and the name of file to writenew threshold values.