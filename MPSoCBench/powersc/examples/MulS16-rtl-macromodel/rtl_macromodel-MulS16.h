#ifndef RTL_MACROMODEL_MulS16_H
#define RTL_MACROMODEL_MulS16_H

#include <iostream>
#include <string>
#include <vector>
#include <ext/hash_map>
#include <powersc.h>

using namespace std;
using namespace __gnu_cxx;

#ifdef POWER_SIM
#define PSC_MACROMODEL_MulS16\
	static const char *celltype;\
	static psc_macromodel_MulS16_EqTab power_model;\
	~MulS16()
#else
#define PSC_MACROMODEL_MulS16
#endif

#include "model_defines-MulS16.cpp"

class psc_macromodel_parms_MulS16_EqTab : public psc_macromodel_parms {
	public:

		psc_macromodel_parms_MulS16_EqTab(double pin, double din, vector<double> bw_dens)
			: m_d_pin( pin ), m_d_din( din ), m_bitwise_dens( bw_dens )
		{
		}

		inline double pin() const
		{ return( m_d_pin ); }

		inline double din() const
		{ return( m_d_din ); }

		inline vector<double> & bitwise_density()
		{ return( m_bitwise_dens ); }

		~psc_macromodel_parms_MulS16_EqTab()
		{
		}

	protected:

		double m_d_pin;
		double m_d_din;
		vector<double> m_bitwise_dens;
};

class psc_macromodel_MulS16_EqTab : public psc_macromodel {
	private:

		static const double model_coeffs[TOTAL_POINTS+1][64+1];

	public:

		psc_macromodel_MulS16_EqTab()
			: psc_macromodel()
		{
			init_power_map();
		}

		void init_power_map();
		double get_power(const psc_macromodel_parms & p);

	protected:

		typedef hash_map<string, int, hash<string>, eqstr> EqTab_index;

		EqTab_index model_index;

		double evaluate_equation(int eqid, const vector<double> & density);
		int find_closest_point(double pin, double din);

};
#endif
