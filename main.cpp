#include <iostream>
#include <sstream>
#include <gethist.h>
#include <threshold_data.h>
using namespace std;
using namespace MathTemplates;
const ThresholdData PerformCalc(const vector<hist<double>>&hists,const ThresholdData&initial){
	return initial;
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
				PerformCalc(hists,input_thr).Save(output_file);
				return 0;
			}else cout<<"output file could not be created"<<endl;
		}else cout<<"input file not found"<<endl;
	}else cout<<"wrong parameters"<<endl;
	return 1;
}
