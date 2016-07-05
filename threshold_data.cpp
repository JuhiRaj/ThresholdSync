#include <sstream>
#include <math_h/include/math_h/error.h>
#include <threshold_data.h>
using namespace std;
using namespace MathTemplates;
ThresholdSingleData::ThresholdSingleData(const ThresholdSingleData& source)
:f_side(source.f_side),f_layer(source.f_layer),f_slot(source.f_slot),f_value(source.f_value),f_threshold(source.f_threshold){}
ThresholdSingleData::ThresholdSingleData(ifstream& stream){
	string line;
	do{
		if(!getline(stream,line))break;
	}while((line=="")||(line[0]=='#'));
	if(line=="")throw Exception<ThresholdSingleData>("Error reading from stream");
	stringstream str(line);
	string side,thr;
	str>>side>>f_layer>>f_slot>>thr>>f_value;
	if(side=="A")f_side=side_left;
	else f_side=side_right;
	if(thr=="a")f_threshold=thr_a;
	if(thr=="b")f_threshold=thr_b;
	if(thr=="c")f_threshold=thr_c;
	if(thr=="d")f_threshold=thr_d;
}
ThresholdSingleData::~ThresholdSingleData(){}
const std::size_t ThresholdSingleData::layer() const{return f_layer;}
const JPET_side ThresholdSingleData::side() const{return f_side;}
const std::size_t ThresholdSingleData::slot() const{return f_slot;}
const threshold_type ThresholdSingleData::threshold() const{return f_threshold;}
const std::size_t ThresholdSingleData::value() const{return f_value;}
std::size_t& ThresholdSingleData::Value(){return f_value;}

ThresholdData::ThresholdData(const ThresholdData& source){
	for(auto&item:source.f_data)
		f_data.push_back(item);
}
ThresholdData::ThresholdData(ifstream& stream){
	while(stream)
		operator<<(ThresholdSingleData(stream));
}
ThresholdData::~ThresholdData(){}
ThresholdData& ThresholdData::operator<<(const ThresholdSingleData& item){
	f_data.push_back(item);
}
const ThresholdSingleData& ThresholdData::get(const threshold_type thr,const JPET_side side, const std::size_t layer,const size_t slot) const{
	for(const ThresholdSingleData&item:f_data)
		if((item.threshold()==thr)&&(item.side()==side)&&(item.layer()==layer)&&(item.slot()==slot))
			return item;
	throw Exception<ThresholdData>("Element not found[]");
}
ThresholdSingleData& ThresholdData::Get(const threshold_type thr,const JPET_side side, const std::size_t layer,const size_t slot){
	for(ThresholdSingleData&item:f_data)
		if((item.threshold()==thr)&&(item.side()==side)&&(item.layer()==layer)&&(item.slot()==slot))
			return item;
	throw Exception<ThresholdData>("Element not found()");
}


