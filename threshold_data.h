#ifndef _______________THR_DATA_H_____________
#	define _______________THR_DATA_H_____________
#include <fstream>
#include <vector>
enum JPET_side{side_left,side_right};
enum threshold_type{thr_a,thr_b,thr_c,thr_d};
class ThresholdSingleData{
public:
	ThresholdSingleData(std::ifstream&stream);
	ThresholdSingleData(const ThresholdSingleData&source);
	virtual ~ThresholdSingleData();
	const JPET_side side()const;
	const std::size_t layer()const;
	const std::size_t slot()const;
	const threshold_type threshold()const;
	const std::size_t value()const;
	std::size_t&Value();
private:
	JPET_side f_side;
	std::size_t f_layer,f_slot,f_value;
	threshold_type f_threshold;
};
class ThresholdData{
public:
	ThresholdData(std::ifstream&stream);
	ThresholdData(const ThresholdData&source);
	virtual ~ThresholdData();
	const ThresholdSingleData& get(const threshold_type thr,const JPET_side side,const std::size_t layer,const size_t slot)const;
	ThresholdSingleData& Get(const threshold_type thr,const JPET_side side,const std::size_t layer,const size_t slot);
	ThresholdData& operator<<(const ThresholdSingleData&item);
private:
	std::vector<ThresholdSingleData> f_data;
};
#endif