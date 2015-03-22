#include "rtl_macromodel-MulS16.h"

const double psc_macromodel_MulS16_EqTab::model_coeffs[TOTAL_POINTS+1][64+1] = {
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, // dummy
#include "model_coefficients-MulS16.cpp"
};

void psc_macromodel_MulS16_EqTab::init_power_map()
{
	model_index.clear();
#include "points_index-MulS16.cpp"
}

int psc_macromodel_MulS16_EqTab::find_closest_point(double pin, double din)
{
	EqTab_index::const_iterator it;
	char key[64];
	int index;
	double pin_try, din_try, base_pin, base_din;

	index = 0; // initially, of course, not found

	// rounds down to the next discretized step
	base_pin = ((int)(pin * 100.0)) / 100.0;
	base_din = ((int)(din * 100.0)) / 100.0;

	// checks if whether pin or din is close to zero
	if ( base_pin == 0 || base_din == 0 ) {
		pin_try = din_try = 0;
		sprintf(key, "p%3.2lf-d%3.2lf", pin_try, din_try);
		index = model_index[key];
	} else {
		double dist, min_dist, diff_a, diff_b;
		int min_index;

		min_dist = 999999;
		min_index = 0;

		for ( pin_try = 0.05 ; pin_try <= 1.0 ; pin_try += 0.1 )
			for ( din_try = 0.05 ; din_try <= 1.0 ; din_try += 0.1 ) {
				sprintf(key, "p%3.2lf-d%3.2lf", pin_try, din_try);
				index = model_index[key];

				if ( index != 0 ) {
					diff_a = pin - pin_try;
					diff_b = din - din_try;
					dist =  sqrt(diff_a*diff_a + diff_b*diff_b);
					if ( dist < min_dist ) {
						min_index = index;
						min_dist = dist;
					}
				}
			}

		index = min_index;
	}

	return( index );
}

double psc_macromodel_MulS16_EqTab::evaluate_equation(int eqid, const vector<double> & density)
{
	double summation;

	summation = model_coeffs[eqid][0];

	for ( unsigned int ci = 1 ; ci <= density.size() ; ci++ ) {
		summation += (model_coeffs[eqid][ci] * density[ci-1]);
	}
	
	return(summation);
}

double psc_macromodel_MulS16_EqTab::get_power(const psc_macromodel_parms & p)
{
	int index;
	double power;
	psc_macromodel_parms_MulS16_EqTab & parms = (psc_macromodel_parms_MulS16_EqTab&)p;

	index = find_closest_point(parms.pin(), parms.din());

	if ( index > 0 ) {
		power = evaluate_equation(index, parms.bitwise_density());
	} else {
		power = -1;
		cerr << "ERROR: no point has been found to be close to (" << parms.pin()
			<< ", " << parms.din() << ")" << endl;
	}

	return( power );
}

#ifdef POWER_SIM
MulS16::~MulS16()
{
	unsigned int i;
	vector<double> bitwise_dens;
	double pin, din, dout, power;

	pin = din = dout = power = 0;

	sc_interface *_if_a = a.get_interface();
	sc_signal<sc_int<16> > *_p_a = dynamic_cast<sc_signal<sc_int<16> >*>(_if_a);
	vector<double> _bw_dens_a = _p_a->get_split_toggle_rate();

	pin += _p_a->get_sp1();
	din += _p_a->get_toggle_rate();

	sc_interface *_if_b = b.get_interface();
	sc_signal<sc_int<16> > *_p_b = dynamic_cast<sc_signal<sc_int<16> >*>(_if_b);
	vector<double> _bw_dens_b = _p_b->get_split_toggle_rate();

	pin += _p_b->get_sp1();
	din += _p_b->get_toggle_rate();

	sc_interface *_if_out1 = out1.get_interface();
	sc_signal<sc_int<32> > *_p_out1 = dynamic_cast<sc_signal<sc_int<32> >*>(_if_out1);
	vector<double> _bw_dens_out1 = _p_out1->get_split_toggle_rate();

	dout += _p_out1->get_toggle_rate();


	pin /= (double)2;
	din = (din/((double)2))*((double)10);
	dout *= (double)10;

	for (i = 0; i < _bw_dens_a.size(); i++)
		bitwise_dens.push_back(_bw_dens_a[i]*10.0);

	for (i = 0; i < _bw_dens_b.size(); i++)
		bitwise_dens.push_back(_bw_dens_b[i]*10.0);

	for (i = 0; i < _bw_dens_out1.size(); i++)
		bitwise_dens.push_back(_bw_dens_out1[i]*10.0);

	psc_macromodel_parms_MulS16_EqTab parms(pin, din, bitwise_dens);
	power = power_model.get_power(parms) * 1e-6;

	psc_cell_power_info info(name(), celltype);

	info.set_level(PSC_RT_LEVEL);
	info.set_power( power );

	psc_pin_power_info pwr_a(_p_a->get_id());
	psc_pin_power_info pwr_b(_p_b->get_id());
	psc_pin_power_info pwr_out1(_p_out1->get_id());

	info.add(pwr_a);
	info.add(pwr_b);
	info.add(pwr_out1);

	PSC_INSERT_CELL(info);
}

const char *MulS16::celltype = "MulS16";
psc_macromodel_MulS16_EqTab MulS16::power_model = psc_macromodel_MulS16_EqTab();
#endif

