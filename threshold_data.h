#ifndef _______________THR_DATA_H_____________
#	define _______________THR_DATA_H_____________
#include <fstream>
#include <vector>
enum JPET_side{side_left=0,side_right=1};
inline JPET_side&inc(JPET_side&a){a=JPET_side(int(a)+1);return a;}
enum threshold_type{thr_a=0,thr_b=1,thr_c=2,thr_d=3};
inline threshold_type&inc(threshold_type&a){a=threshold_type(int(a)+1);return a;}
class ThresholdSingleData{
public:
	ThresholdSingleData(std::string&line);
	ThresholdSingleData(const ThresholdSingleData&source);
	void Save(std::ofstream&stream)const;
	virtual ~ThresholdSingleData();
	const JPET_side side()const;
	const std::size_t layer()const;
	const std::size_t slot()const;
	const threshold_type threshold()const;
	const double value()const;
	double&Value();
private:
	JPET_side f_side;
	std::size_t f_layer,f_slot;
	double f_value;
	threshold_type f_threshold;
};
class ThresholdData{
public:
	ThresholdData(std::ifstream&stream);
	ThresholdData(const ThresholdData&source);
	void Save(std::ofstream&stream)const;
	virtual ~ThresholdData();
	const ThresholdSingleData& get(const threshold_type thr,const JPET_side side,const std::size_t layer,const size_t slot)const;
	ThresholdSingleData& Get(const threshold_type thr,const JPET_side side,const std::size_t layer,const size_t slot);
	ThresholdData& operator<<(const ThresholdSingleData&item);
private:
	std::vector<ThresholdSingleData> f_data;
};
#endif