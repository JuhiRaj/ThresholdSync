Software for threshold adjust in J-PET
======================================
Note : The Layer Coefficients are as follows: Ratio Layer 1 / Layer 2 to 1.149 and Layer 1 / Layer 3 to 1.500
Please make sure you make these changes in the ThresholdSync main.cpp (Run-5)

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
and the name of file to write new threshold values.
