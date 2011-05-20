

#ifndef LREADING_HPP_
#define LREADING_HPP_

#include "application/visual_servoing/Reading.h"

namespace Types {
namespace Mrrocpp_Proxy {


/**
 *
 */
class LReading: public Reading
{
public:
	LReading()
	{
	}

	LReading(const LReading& o)
	{
		path_exists = o.path_exists;

		for(int i=0;i<9;i++)
			for(int j=0;j<9;j++)
				path[i][j] = o.path[i][j];
	}

	virtual ~LReading()
	{
	}

	virtual LReading* clone()
	{
		return new LReading(*this);
	}

	bool path_exists;
	int path [9][9];

	virtual void send(boost::shared_ptr<xdr_oarchive<> > & ar){
		*ar<<*this;
	}

private:
	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object <Reading>(*this);

		ar & path_exists;
		ar & path;
	}
};

}//namespace Mrrocpp_Proxy
}//namespace Types

#endif /* LREADING_HPP_ */
