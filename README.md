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

