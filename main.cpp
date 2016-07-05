#include <iostream>
#include <sstream>
#include <map>
#include <gethist.h>
#include <threshold_data.h>
using namespace std;
using namespace MathTemplates;
const vector<size_t> layer_size{48,48,96};
const size_t to_hist_index(const JPET_side side,const std::size_t layer,const size_t slot){
	const vector<size_t> layer_start{0,48*2,48*4};
	return layer_start[layer-1]+((side==side_left)?0:layer_size[layer-1])+slot-1;
}
const ThresholdData PerformCalc(const vector<hist<double>>&hists,const ThresholdData&initial){
	auto output=initial;
	auto reference_bin=hists[3][1];
	const vector<double> thr_coeff{300.0/180.0,280.0/180.0,230.0/180.0,1.0};
	const vector<double> layer_coeff{1,1.07,1.27};
	for(threshold_type thr=thr_a;thr<=thr_d;inc(thr))
		for(size_t layer=1;layer<=3;layer++)
			for(JPET_side side=side_left;side<=side_right;inc(side))
				for(size_t slot=1;slot<=layer_size[layer-1];slot++){
					auto actual_events=hists[int(thr)][to_hist_index(side,layer,slot)].Y();
					auto should_be=reference_bin.Y()*(thr_coeff[int(thr)]/layer_coeff[layer-1]);
					if(!should_be.contains(actual_events))
						output.Get(thr,side,layer,slot).Value()*=(actual_events/should_be).val();
				}
				return output;
}
const ThresholdData TestOutput(const vector<hist<double>>&hists,const ThresholdData&initial){
	auto output=initial;
	auto reference_bin=hists[3][1];
	const vector<double> thr_coeff{300.0/180.0,280.0/180.0,230.0/180.0,1.0};
	const vector<double> layer_coeff{1,1.07,1.27};
	for(threshold_type thr=thr_a;thr<thr_d;inc(thr))
		for(size_t layer=1;layer<=3;layer++)
			for(JPET_side side=side_left;side<=side_right;inc(side))
				for(size_t slot=1;slot<=layer_size[layer-1];slot++){
					if(thr==thr_a)output.Get(thr,side,layer,slot).Value()=100.0;
					if(thr==thr_b)output.Get(thr,side,layer,slot).Value()=150.0;
					if(thr==thr_c)output.Get(thr,side,layer,slot).Value()=200.0;
				}
				return output;
}
int main(int argc, char **argv) {
	if(argc==4){
		string file_root(argv[1]),file_in(argv[2]),file_out(argv[3]);
		vector<hist<double>> hists;
		for(size_t i=1;i<5;i++){
			stringstream buffer;
			buffer<<"HitsLeadingEdgeThr"<<i;
			hists.push_back(ReadHist(file_root,{"UserObjects","SingleThresholdMultiplicities"},buffer.str()));
		}
		ifstream input_file;
		input_file.open(file_in);
		if(input_file){
			ThresholdData input_thr(input_file);
			input_file.close();
			ofstream output_file;
			output_file.open(file_out);
			if(output_file){
				TestOutput(hists,input_thr).Save(output_file);
				return 0;
			}else cout<<"output file could not be created"<<endl;
		}else cout<<"input file not found"<<endl;
	}else cout<<"wrong parameters"<<endl;
	return 1;
}
